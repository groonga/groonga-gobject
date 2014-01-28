#!/usr/bin/env python
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

from __future__ import print_function
import argparse
import os
import sys
import readline
import atexit

from gi.repository import Groonga
import gi

try:
    import __builtin__
    if hasattr(__builtin__, "raw_input"):
        input_function = raw_input
    else:
        input_function = input
except ImportError:
    input_function = input

parser = argparse.ArgumentParser(description="Groonga command line interface")
parser.add_argument("database", metavar="DATABASE", type=str, nargs="?",
                    help="Groonga database path")
args = parser.parse_args()

def setup_database(context):
    if args.database:
        if os.path.exists(args.database):
            context.open_database(args.database)
        else:
            os.makedirs(os.path.dirname(args.database))
            context.create_database(args.database)
    else:
        context.create_database(None)

def setup_history():
    history_file = os.path.expanduser("~/.groonga")
    try:
        readline.read_history_file(history_file)
    except IOError:
        pass
    atexit.register(readline.write_history_file, history_file)

def eval_print(context, line):
    try:
        context.send_command(line)
    except:
        print(sys.exc_info()[1])
    result = context.receive_result()
    if len(result) > 0:
        print(result)

def run(context):
    while True:
        try:
            line = input_function("> ")
            eval_print(context, line)
        except EOFError:
            break

def main():
    context = Groonga.Context.new()
    try:
        setup_database(context)
        setup_history()
        run(context)
    finally:
        del context

Groonga.init()
main()
Groonga.fin()
