/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * Copyright (C) 2014  Kouhei Sutou <kou@clear-code.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string.h>

#include <groonga.h>

#include "ggrn-command.h"
#include "ggrn-internal.h"

/**
 * SECTION: ggrn-command
 * @short_description: An object to create a Groonga command.
 *
 * The #GGrnCommand is a class to create a Groonga command string.
 */
G_DEFINE_TYPE(GGrnCommand, ggrn_command, G_TYPE_OBJECT)

#define GGRN_COMMAND_GET_PRIVATE(obj)                          \
    (G_TYPE_INSTANCE_GET_PRIVATE((obj),                        \
                                 GGRN_TYPE_COMMAND,            \
                                 GGrnCommandPrivate))

typedef struct _GGrnCommandPrivate	GGrnCommandPrivate;
struct _GGrnCommandPrivate
{
    GGrnContext *context;
    gchar *name;
    GHashTable *arguments;
};

enum
{
    PROP_0,
    PROP_CONTEXT,
    PROP_NAME,
    N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES] = {NULL,};

static void
ggrn_command_init(GGrnCommand *object)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(object);

    priv->context = NULL;
    priv->name = NULL;
    priv->arguments = g_hash_table_new_full(g_str_hash, g_str_equal,
                                            g_free, g_free);
}

static void
dispose(GObject *object)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(object);

    if (priv->context) {
        g_object_unref(priv->context);
        priv->context = NULL;
    }

    if (priv->name) {
        g_free(priv->name);
        priv->name = NULL;
    }

    if (priv->arguments) {
        g_hash_table_unref(priv->arguments);
        priv->arguments = NULL;
    }

    G_OBJECT_CLASS(ggrn_command_parent_class)->dispose(object);
}

static void
set_property(GObject      *object,
             guint         prop_id,
             const GValue *value,
             GParamSpec   *pspec)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(object);

    switch (prop_id) {
    case PROP_CONTEXT:
        {
            GGrnContext *context = priv->context;
            priv->context = g_value_get_object(value);
            if (priv->context != context) {
                if (priv->context) {
                    g_object_ref(priv->context);
                }
                if (context) {
                    g_object_unref(context);
                }
            }
        }
        break;
    case PROP_NAME:
        g_free(priv->name);
        priv->name = g_value_dup_string(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void
get_property(GObject    *object,
             guint       prop_id,
             GValue     *value,
             GParamSpec *pspec)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(object);

    switch (prop_id) {
    case PROP_CONTEXT:
        g_value_set_object(value, priv->context);
        break;
    case PROP_NAME:
        g_value_set_string(value, priv->name);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void
ggrn_command_class_init(GGrnCommandClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    GParamSpec *spec;

    object_class->dispose      = dispose;
    object_class->set_property = set_property;
    object_class->get_property = get_property;

    spec = g_param_spec_object("context",
                               "Context",
                               "The context for the command",
                               GGRN_TYPE_CONTEXT,
                               G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);
    g_object_class_install_property(object_class, PROP_CONTEXT, spec);

    spec = g_param_spec_string("name",
                               "Command name",
                               "The name of the command",
                               NULL,
                               G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);
    g_object_class_install_property(object_class, PROP_NAME, spec);

    g_type_class_add_private(object_class, sizeof(GGrnCommandPrivate));
}

/**
 * ggrn_command_new:
 * @context: A #GGrnContext.
 * @name: The command name.
 *
 * Allocates a new #GGrnCommand.
 *
 * Returns: a new #GGrnCommand.
 *
 * Since: 1.0.0
 */
GGrnCommand *
ggrn_command_new(GGrnContext *context, const gchar *name)
{
    return g_object_new(GGRN_TYPE_COMMAND,
                        "context", context,
                        "name", name,
                        NULL);
}

/**
 * ggrn_command_add_argument:
 * @command: A #GGrnCommand.
 * @name: The name of the argument.
 * @value: The value of the argument.
 *
 * Adds an argument of the command.
 *
 * If you add the same name argument twice, the old argument value is
 * overrode.
 *
 * Since: 1.0.0
 */
void
ggrn_command_add_argument(GGrnCommand *command,
                          const gchar *name, const gchar *value)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(command);

    g_hash_table_insert(priv->arguments, g_strdup(name), g_strdup(value));
}

/**
 * ggrn_command_execute:
 * @command: A #GGrnCommand.
 *
 * Executes the command and returns the executed result.
 *
 * Returns: The executed result of @command. It must be freed with
 *   g_free() when no longer needed.
 *
 * Since: 1.0.0
 */
gchar *
ggrn_command_execute(GGrnCommand *command)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(command);
    gchar *command_line;
    gchar *result;

    command_line = ggrn_command_to_command_line(command);
    result = ggrn_context_execute_command(priv->context, command_line);
    g_free(command_line);

    return result;
}

static void
to_path_append_argument(gpointer key, gpointer value, gpointer user_data)
{
    GString *path = user_data;

    if (path->str[path->len - 1] != '?') {
        g_string_append_c(path, '&');
    }
    g_string_append_uri_escaped(path, key, NULL, FALSE);
    g_string_append_c(path, '=');
    g_string_append_uri_escaped(path, value, NULL, FALSE);
}

/**
 * ggrn_command_to_path:
 * @command: A #GGrnCommand.
 *
 * Formats the command as path format like the following:
 *
 * |[
 * /d/table_create?name=Logs&flags=TABLE_NO_KEY
 * ]|
 *
 * Returns: The path format command. It must be freed with
 *   g_free() when no longer needed.
 *
 * Since: 1.0.0
 */
gchar *
ggrn_command_to_path(GGrnCommand *command)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(command);
    GString *path;

    path = g_string_new("/d/");
    g_string_append(path, priv->name);
    if (g_hash_table_size(priv->arguments) > 0) {
        g_string_append_c(path, '?');
        g_hash_table_foreach(priv->arguments,
                             to_path_append_argument,
                             path);
    }

    return g_string_free(path, FALSE);
}

static void
to_command_line_append_value(GString *command_line, const gchar *value)
{
    const gchar *value_current, *value_next;

    g_string_append_c(command_line, '"');
    value_current = value;
    while (*value_current) {
        gsize char_length;
        value_next = g_utf8_next_char(value_current);
        if (value_next) {
            char_length = value_next - value_current;
        } else {
            char_length = strlen(value_current);
        }
        if (char_length == 1) {
            switch (*value_current) {
            case '"':
            case '\\':
                g_string_append_c(command_line, '\\');
                break;
            default:
                break;
            }
        }
        g_string_append_len(command_line, value_current, char_length);
        value_current = value_next;
    }
    g_string_append_c(command_line, '"');
}

static void
to_command_line_append_argument(gpointer key, gpointer value, gpointer user_data)
{
    const gchar *name = key;
    GString *command_line = user_data;

    g_string_append_printf(command_line, " --%s ", name);
    to_command_line_append_value(command_line, value);
}

/**
 * ggrn_command_to_command_line:
 * @command: A #GGrnCommand.
 *
 * Formats the command as command line format like the following:
 *
 * |[
 * table_create --name Logs --flags TABLE_NO_KEY
 * ]|
 *
 * Returns: The command line format command. It must be freed with
 *   g_free() when no longer needed.
 *
 * Since: 1.0.0
 */
gchar *
ggrn_command_to_command_line(GGrnCommand *command)
{
    GGrnCommandPrivate *priv = GGRN_COMMAND_GET_PRIVATE(command);
    GString *command_line;

    command_line = g_string_new(NULL);
    g_string_append(command_line, priv->name);
    g_hash_table_foreach(priv->arguments,
                         to_command_line_append_argument,
                         command_line);

    return g_string_free(command_line, FALSE);
}
