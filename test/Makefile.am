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

AM_CPPFLAGS =					\
	-I$(top_builddir)			\
	-I$(top_srcdir)

AM_CFLAGS =					\
	$(GCUTTER_CFLAGS)

AM_LDFLAGS =					\
	-module					\
	-rpath "`pwd`/.libs"			\
	-avoid-version				\
	-no-undefined

LIBS =								\
	$(top_builddir)/groonga-gobject/libgroonga-gobject.la	\
	$(GCUTTER_LIBS)

if WITH_CUTTER
noinst_LTLIBRARIES =				\
	suite-groonga-gobject-test.la		\
	test-command.la
endif

suite_groonga_gobject_test_la_SOURCES = suite-groonga-gobject-test.c

test_command_la_SOURCES = test-command.c

echo-abs-top-builddir:
	@echo $(abs_top_builddir)
