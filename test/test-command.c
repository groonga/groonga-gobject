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

CUT_EXPORT void data_to_path(void);
CUT_EXPORT void test_to_path(gconstpointer data);
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

static void
add_argument(gpointer key, gpointer value, gpointer user_data)
{
    ggrn_command_add_argument(command, key, value);
}

static void
add_arguments(GHashTable *arguments)
{
    if (!arguments) {
        return;
    }

    g_hash_table_foreach(arguments, add_argument, NULL);
}

void
data_to_path(void)
{
#define ADD_DATA(label, expected, arguments)                            \
    gcut_add_datum(label,                                               \
                   "expected", G_TYPE_STRING, expected,                 \
                   "arguments", G_TYPE_HASH_TABLE, arguments,           \
                   NULL);

#define ARGUMENTS(argument, ...)                                \
    gcut_hash_table_string_string_new(argument, __VA_ARGS__)

    ADD_DATA("no arguments",
             "/d/select",
             NULL);
    ADD_DATA("one argument",
             "/d/select?table=Users",
             ARGUMENTS("table", "Users",
                       NULL));
    ADD_DATA("two or more arguments",
             "/d/select?table=Users&output_columns=_key&limit=10",
             ARGUMENTS("table", "Users",
                       "output_columns", "_key",
                       "limit", "10",
                       NULL));
    ADD_DATA("escape",
             "/d/select?filter=%281%20%2B%202%20%26%26%20%22string%22%29",
             ARGUMENTS("filter", "(1 + 2 && \"string\")",
                       NULL));

#undef ARGUMENTS

#undef ADD_DATA
}

void
test_to_path(gconstpointer data)
{
    const gchar *expected;

    expected = gcut_data_get_string(data, "expected");
    add_arguments((GHashTable *)(gcut_data_get_pointer(data, "arguments")));
    cut_assert_equal_string_with_free(expected,
                                      ggrn_command_to_path(command));
}

void
test_to_command_line(void)
{
    cut_assert_equal_string_with_free("select",
                                      ggrn_command_to_command_line(command));
}
