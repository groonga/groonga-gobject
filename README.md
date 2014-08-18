# README

## Name

Groonga GObject

## Description

GObject wrapper of Groonga. TODO...

## Install

### Debian GNU/Linux

[Set up Groonga APT repository](http://groonga.org/docs/install/debian.html).

Run the following command:

    % sudo apt-get install -V -y gir1.2-groonga libgroonga-gobject0

### Ubuntu

[Set up Groonga APT repository](http://groonga.org/docs/install/ubuntu.html).

Run the following command:

    % sudo apt-get install -V -y gir1.2-groonga libgroonga-gobject0

### Fedora

[Set up Groonga YUM repository](http://groonga.org/docs/install/fedora.html).

Run the following command:

    % sudo yum install -y groonga-gobject

### From source

[Install Groonga](http://groonga.org/docs/install.html) and
[GObject Introspection](https://wiki.gnome.org/Projects/GObjectIntrospection).

Download `groonga-gobject-${VERSION}.tar.gz` from
http://packages.groonga.org/source/groonga-gobject/ like:

    % wget http://packages.groonga.org/source/groonga-gobject/groonga-gobject-1.0.1.tar.gz

Run the following commands:

    % tar xf groonga-gobject-1.0.1.tar.gz
    % cd groonga-gobject-1.0.1
    % ./configure
    % make
    % sudo make install

## Authors

* Kouhei Sutou `<kou@clear-code.com>`

## License

LGPL 3.0 or later. See COPYING for details.

(Kouhei Sutou has a right to change the license including contributed
patches.)
