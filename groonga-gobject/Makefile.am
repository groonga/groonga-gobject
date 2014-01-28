# Copyright (C) 2013-2014  Kouhei Sutou <kou@clear-code.com>
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

CLEANFILES =

AM_CPPFLAGS =			\
	 -I$(top_builddir)	\
	 -I$(top_srcdir)

AM_CFLAGS =					\
	$(GLIB_CFLAGS)				\
	$(GROONGA_CFLAGS)			\
	$(GGRN_CFLAGS)

lib_LTLIBRARIES =				\
	libgroonga-gobject.la

libgroonga_gobject_la_LDFLAGS =			\
	-version-info $(LT_VERSION_INFO)	\
	-no-undefined

libgroonga_gobject_la_LIBADD =			\
	$(GLIB_LIBS)				\
	$(GROONGA_LIBS)

libgroonga_gobject_la_SOURCES =			\
	ggrn.c					\
	ggrn.h					\
	ggrn-context.c				\
	ggrn-context.h				\
	ggrn-command.c				\
	ggrn-command.h				\
	ggrn-error.c				\
	ggrn-error.h				\
	ggrn-internal.c				\
	ggrn-internal.h

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir)
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(libgroonga_gobject_la_SOURCES)

Groonga-1.0.gir: libgroonga-gobject.la
Groonga_1_0_gir_PACKAGES = gobject-2.0 glib-2.0 groonga
Groonga_1_0_gir_EXPORT_PACKAGES = groonga-gobject
Groonga_1_0_gir_INCLUDES = GObject-2.0
Groonga_1_0_gir_CFLAGS = $(AM_CPPFLAGS) $(AM_CFLAGS)
Groonga_1_0_gir_LIBS = libgroonga-gobject.la
Groonga_1_0_gir_FILES = $(introspection_sources)
Groonga_1_0_gir_SCANNERFLAGS =			\
	--identifier-prefix=GGrn		\
	--symbol-prefix=ggrn
INTROSPECTION_GIRS += Groonga-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES +=					\
	$(gir_DATA)				\
	$(typelib_DATA)
endif
