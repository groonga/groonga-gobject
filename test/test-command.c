/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * Copyright (C) 2014  Kouhei Sutou <kou@clear-code.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <groonga-gobject/ggrn.h>

#include <gcutter.h>

CUT_EXPORT void test_to_path(void);
CUT_EXPORT void test_to_command_line(void);

static GGrnContext *context;
static GGrnCommand *command;

void
cut_setup(void)
{
    context = ggrn_context_new();
    command = ggrn_command_new(context, "select");
}

void
cut_teardown(void)
{
    g_object_unref(command);
    g_object_unref(context);
}

void
test_to_path(void)
{
    cut_assert_equal_string_with_free("/d/select",
                                      ggrn_command_to_path(command));
}

void
test_to_command_line(void)
{
    cut_assert_equal_string_with_free("select",
                                      ggrn_command_to_command_line(command));
}
