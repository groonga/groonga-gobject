# Copyright (C) 2013  Kouhei Sutou <kou@clear-code.com>
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

DOC_MODULE = groonga-gobject

DOC_MAIN_SGML_FILE = groonga-gobject-docs.sgml

DOC_SOURCE_DIR =				\
	$(top_srcdir)/groonga-gobject

SCAN_OPTIONS =						\
	--deprecated-guards="GGRN_DISABLE_DEPRECATED"

MKDB_OPTIONS =						\
	--name-space=ggrn

HFILE_GLOB =					\
	$(top_srcdir)/groonga-gobject/*.h

CFILE_GLOB =					\
	$(top_srcdir)/groonga-gobject/*.c

AM_CPPFLAGS =					\
	-I$(top_srcdir)				\
	-I$(top_srcdir)/groonga-gobject		\
	$(GLIB_CFLAGS)				\
	$(GROONGA_CFLAGS)

GTKDOC_LIBS =							\
	$(top_builddir)/groonga-gobject/libgroonga-gobject.la	\
	$(GLIB_LIBS)						\
	$(GROONGA_LIBS)

include $(srcdir)/gtk-doc.make

CLEANFILES +=					\
	$(DOC_MODULE)-sections.txt		\
	$(DOC_MODULE).types
