#!/bin/sh

run()
{
    "$@"
    if test $? -ne 0; then
	echo "Failed $@"
	exit 1
    fi
}

rpmbuild_options=

. /vagrant/env.sh

run yum groupinstall -y "Development Tools"
run yum install -y rpm-build rpmdevtools tar ${DEPENDED_PACKAGES}

distribution=$(cut -d " " -f 1 /etc/redhat-release | tr "A-Z" "a-z")
if grep -q Linux /etc/redhat-release; then
    distribution_version=$(cut -d " " -f 4 /etc/redhat-release)
else
    distribution_version=$(cut -d " " -f 3 /etc/redhat-release)
fi

# for debug
# rpmbuild_options="$rpmbuild_options --define 'optflags -O0 -ggdb3'"

cd

run rm -rf .rpmmacros
run rpmdev-setuptree

run cp /vagrant/tmp/${PACKAGE}-${VERSION}.* rpmbuild/SOURCES/
run cp /vagrant/tmp/${distribution}/${PACKAGE}.spec rpmbuild/SPECS/

run rpmbuild -ba ${rpmbuild_options} rpmbuild/SPECS/${PACKAGE}.spec

repository="/vagrant/repositories/${distribution}/${distribution_version}"
run cp rpmbuild/RPMS/$(arch)/* ${repository}/$(arch)/Packages/
run cp rpmbuild/SRPMS/* ${repository}/source/SRPMS/
