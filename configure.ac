# Copyright (C) 2013-2014  Kouhei Sutou <kou@clear-code.com>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_PREREQ(2.59)

AC_INIT(groonga-gobject, [1.0.0],
        groonga-talk@lists.sourceforge.net)
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([groonga-gobject/ggrn.h])
AM_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE(tar-pax foreign)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_LIBTOOL

LT_CURRENT=1
LT_REVISION=0
LT_AGE=1
LT_VERSION_INFO="$LT_CURRENT:$LT_REVISION:$LT_AGE"
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
AC_SUBST(LT_VERSION_INFO)

LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^[[^_]].*"'
AC_SUBST(LIBTOOL_EXPORT_OPTIONS)

AC_DEFUN([CHECK_CFLAG], [
  AC_MSG_CHECKING([if gcc supports $1])
  old_CFLAGS=$CFLAGS
  flag=`echo '$1' | sed -e 's,^-Wno-,-W,'`
  CFLAGS="$CFLAGS $flag -Werror"
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
    [check_cflag=yes],
    [check_cflag=no])
  CFLAGS="$old_CFLAGS"
  if test "x$check_cflag" = "xyes"; then
    CFLAGS="$CFLAGS $1"
  fi
  AC_MSG_RESULT([$check_cflag])
])

if test "$GCC" = "yes"; then
  CHECK_CFLAG([-Wall])
  CHECK_CFLAG([-Wextra])
  CHECK_CFLAG([-Wmissing-prototypes])
fi

GGRN_CFLAGS=""
AC_ARG_ENABLE(debug,
  [AS_HELP_STRING([--enable-debug],
                  [use debug flags (default=no)])],
  [ggrn_debug="$enableval"],
  [ggrn_debug="no"])
if test "x$ggrn_debug" != "xno"; then
  if test "$CLANG" = "yes"; then
    CFLAGS="$GGRN_CFLAGS -O0 -g"
  elif test "$GCC" = "yes"; then
    CFLAGS="$GGRN_CFLAGS -O0 -g3"
  fi
fi
AC_SUBST(GGRN_CFLAGS)

GROONGA_REQUIRED=3.1.0
AC_SUBST(GROONGA_REQUIRED)
PKG_CHECK_MODULES(GROONGA, [groonga >= ${GROONGA_REQUIRED}])

GLIB_REQUIRED=2.32.4
AC_SUBST(GLIB_REQUIRED)
AM_PATH_GLIB_2_0([${GLIB_REQUIRED}], [], [], [gobject])
GLIB_VERSION="${glib_config_major_version}.${glib_config_minor_version}.${glib_config_micro_version}"

GOBJECT_INTROSPECTION_REQUIRE([1.32.1])
GTK_DOC_CHECK([1.18])

m4_ifdef([AC_CHECK_GCUTTER],
         [AC_CHECK_GCUTTER(>= 1.1.6)],
         [cutter_use_cutter="no"])
AM_CONDITIONAL([WITH_CUTTER], [test "$cutter_use_cutter" = "yes"])
if test "$cutter_use_cutter" = "yes"; then
  AC_DEFINE(WITH_CUTTER, 1, [Define to 1 if you use Cutter])
fi

m4_ifdef([AC_CHECK_COVERAGE], [AC_CHECK_COVERAGE])
GENHTML_OPTIONS="--title 'Groonga GObject Code Coverage'"

AC_ARG_WITH(rsync-path,
            [AS_HELP_STRING([--with-rsync-path=PATH],
            [specify rsync path to upload groonga gobject packages.])],
            [RSYNC_PATH="$withval"],
            [RSYNC_PATH="packages@packages.groonga.org:public"])
AC_SUBST(RSYNC_PATH)

AC_ARG_WITH(launchpad-uploader-pgp-key,
            [AS_HELP_STRING([--with-launchpad-uploader-pgp-key=KEY],
            [specify PGP key UID to upload Groonga packages to Launchpad.])],
            [LAUNCHPAD_UPLOADER_PGP_KEY="$withval"],
            [LAUNCHPAD_UPLOADER_PGP_KEY=""])
AC_SUBST(LAUNCHPAD_UPLOADER_PGP_KEY)

AC_ARG_WITH([groonga-source-path],
            AS_HELP_STRING([--with-groonga-source-path=PATH],
                           [Specify Groonga source path for
			    groonga-normalizer-mysql's release manager.]),
			   [GROONGA_SOURCE_PATH="$withval"])
case "$GROONGA_SOURCE_PATH" in
  ""|/*)
    : # do nothing
    ;;
  *)
    GROONGA_SOURCE_PATH="\$(top_builddir)/${GROONGA_SOURCE_PATH}"
    ;;
esac
AC_SUBST(GROONGA_SOURCE_PATH)


AC_CONFIG_FILES([
  groonga-gobject.pc
  Makefile
  groonga-gobject/Makefile
  test/Makefile
  doc/Makefile
  doc/reference/Makefile
  doc/reference/version.xml
  sample/Makefile
  packages/Makefile
  packages/apt/Makefile
  packages/ubuntu/Makefile
  packages/yum/Makefile
  packages/rpm/Makefile
  packages/rpm/fedora/Makefile
  packages/rpm/fedora/groonga-gobject.spec
  packages/source/Makefile
])

AC_OUTPUT

echo
echo "Configure Result:"
echo
echo "  GLib                    : $GLIB_VERSION"
echo
echo "  GTK-Doc                 : $enable_gtk_doc"
echo
echo "  Cutter                  : $CUTTER"
echo "  LCOV                    : $LCOV"
