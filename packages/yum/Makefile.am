REPOSITORIES_PATH = repositories
DISTRIBUTIONS = fedora
CHROOT_BASE = /var/lib/chroot
BASE_URL_PREFIX = http://packages.groonga.org
HAVE_DEVELOPMENT_BRANCH = no
USE_RPMFORGE = no
USE_ATRPMS = no

release: download build sign-packages update-repository upload

ensure-rsync-path:
	@if test -z "$(RSYNC_PATH)"; then				\
	  echo "--with-rsync-path configure option must be specified.";	\
	  false;							\
	fi

sign-packages:
	./sign-rpm.sh '$(GPG_UID)' '$(REPOSITORIES_PATH)/' \
	  '$(DISTRIBUTIONS)'

update-repository: RPM-GPG-KEY-$(PACKAGE)
	./update-repository.sh '$(PACKAGE)' '$(REPOSITORIES_PATH)/' \
	  '$(DISTRIBUTIONS)'

upload: ensure-rsync-path
	for distribution in $(DISTRIBUTIONS); do		\
	  rsync -avz --progress --delete --exclude .gitignore	\
	    $(REPOSITORIES_PATH)/$${distribution}/		\
	      $(RSYNC_PATH)/$${distribution};			\
	done

download: ensure-rsync-path
	mkdir -p $(REPOSITORIES_PATH)
	for distribution in $(DISTRIBUTIONS); do	\
	   rsync -avz --progress --delete		\
	     $(RSYNC_PATH)/$${distribution}/		\
	     $(REPOSITORIES_PATH)/$${distribution};	\
	done

build: source specs
	vagrant up
	vagrant destroy --force

ensure-public-key:
	gpg --list-keys '$(GPG_UID)' > /dev/null ||			\
	  gpg --keyserver keyserver.ubuntu.com --recv-key '$(GPG_UID)'

RPM-GPG-KEY-$(PACKAGE): ensure-public-key
	gpg --armor --export '$(GPG_UID)' > $@

source: tmp/$(PACKAGE)-$(VERSION).tar.gz

tmp/$(PACKAGE)-$(VERSION).tar.gz: $(abs_top_builddir)/$(PACKAGE)-$(VERSION).tar.gz
	cp $(abs_top_builddir)/$(PACKAGE)-$(VERSION).tar.gz tmp/

$(abs_top_builddir)/$(PACKAGE)-$(VERSION).tar.gz:
	cd $(abs_top_builddir) && $(MAKE) dist

specs: tmp/fedora/$(PACKAGE).spec

tmp/fedora/$(PACKAGE).spec: $(builddir)/../rpm/fedora/$(PACKAGE).spec
	mkdir -p tmp/fedora
	cp $(builddir)/../rpm/fedora/$(PACKAGE).spec tmp/fedora/

