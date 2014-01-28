#!/bin/bash
#
# Copyright (C) 2014  Kouhei Sutou <kou@clear-code.com>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.

unset MAKELEVEL
unset MAKEFLAGS

BASE_DIR="$(dirname $0)"

if gmake --version > /dev/null 2>&1; then
    MAKE=${MAKE:-"gmake"}
else
    MAKE=${MAKE:-"make"}
fi

if test -z "$abs_top_builddir"; then
    abs_top_builddir="$(${MAKE} -C "${BASE_DIR}" -s echo-abs-top-builddir)"
fi

if test "$NO_MAKE" != "yes"; then
    MAKE_ARGS=
    case "$(uname)" in
        Linux)
            MAKE_ARGS="-j$(grep '^processor' /proc/cpuinfo | wc -l)"
            ;;
        Darwin)
            MAKE_ARGS="-j$(/usr/sbin/sysctl -n hw.ncpu)"
            ;;
        *)
            :
            ;;
    esac
    $MAKE $MAKE_ARGS -C "$abs_top_builddir" > /dev/null || exit 1
fi

if test -z "$CUTTER"; then
    CUTTER="$(${MAKE} -s -C "$abs_top_builddir" echo-cutter)"
fi

CUTTER_ARGS=
CUTTER_WRAPPER=
if test "$CUTTER_DEBUG" = "yes"; then
    CUTTER_WRAPPER="$abs_top_builddir/libtool --mode=execute gdb --args"
    CUTTER_ARGS="--keep-opening-modules"
elif test "$CUTTER_CHECK_LEAK" = "yes"; then
    CUTTER_WRAPPER="$abs_top_builddir/libtool --mode=execute valgrind "
    CUTTER_WRAPPER="$CUTTER_WRAPPER --leak-check=full --show-reachable=yes -v"
    CUTTER_ARGS="--keep-opening-modules"
fi

export CUTTER

CUTTER_ARGS="$CUTTER_ARGS -s $BASE_DIR --exclude-directory fixtures"

$CUTTER_WRAPPER $CUTTER $CUTTER_ARGS "$@" $BASE_DIR
