# Copyright (C) 2013  Kouhei Sutou <kou@clear-code.com>
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

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

DISTCHECK_CONFIGURE_FLAGS =			\
	--enable-introspection

SUBDIRS =					\
	groonga-gobject				\
	test					\
	doc					\
	sample					\
	packages

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = groonga-gobject.pc

tag:
	cd $(top_srcdir) && git tag v$(VERSION) -a -m 'Groonga GObject $(VERSION)!!!'

echo-cutter:
	@echo $(CUTTER)

update-latest-release:
	@if test -z "$(CUTTER_SOURCE_PATH)"; then			\
	  echo "\$$(CUTTER_SOURCE_PATH) is missing.";			\
	  echo "Pass --cutter-source-path option to configure.";	\
	  exit 1;							\
	fi
	@if test -z "$(OLD_RELEASE)"; then	\
	  echo "\$$(OLD_RELEASE) is missing";	\
	  exit 1;				\
	fi
	@if test -z "$(OLD_RELEASE_DATE)"; then		\
	  echo "\$$(OLD_RELEASE_DATE) is missing";	\
	  exit 1;					\
	fi
	@if test -z "$(NEW_RELEASE_DATE)"; then		\
	  echo "\$$(NEW_RELEASE_DATE) is missing";	\
	  exit 1;					\
	fi
	cd $(top_srcdir) &&					\
	  $(CUTTER_SOURCE_PATH)/misc/update-latest-release.rb	\
	  $(PACKAGE) $(OLD_RELEASE) $(OLD_RELEASE_DATE)		\
	  $(VERSION) $(NEW_RELEASE_DATE)			\
	  packages/rpm/fedora/groonga-gobject.spec.in		\
	  packages/debian/changelog
