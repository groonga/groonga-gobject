/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * Copyright (C) 2013  Kouhei Sutou <kou@clear-code.com>
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

#include <string.h>

#include <groonga.h>

#include "ggrn-context.h"
#include "ggrn-internal.h"

/**
* SECTION: ggrn-context
* @short_description: A context for operating a database.
*
* The #GGrnContext is a class to keep all information about database
* operations.
*/
G_DEFINE_TYPE(GGrnContext, ggrn_context, G_TYPE_OBJECT)

#define GGRN_CONTEXT_GET_PRIVATE(obj)                          \
    (G_TYPE_INSTANCE_GET_PRIVATE((obj),                        \
                                 GGRN_TYPE_CONTEXT,            \
                                 GGrnContextPrivate))

typedef struct _GGrnContextPrivate	GGrnContextPrivate;
struct _GGrnContextPrivate
{
  grn_ctx *ctx;
};

enum
{
    PROP_0,
    N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES] = {NULL,};

static void
ggrn_context_init(GGrnContext *object)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(object);

    priv->ctx = grn_ctx_open(0);
}

static void
dispose(GObject *object)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(object);

    if (priv->ctx) {
        grn_obj *using_database;

        using_database = grn_ctx_db(priv->ctx);
        if (using_database) {
            grn_db_close(priv->ctx, using_database);
        }
        grn_ctx_close(priv->ctx);
        priv->ctx = NULL;
    }
    G_OBJECT_CLASS(ggrn_context_parent_class)->dispose(object);
}

static void
ggrn_context_class_init(GGrnContextClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    object_class->dispose = dispose;

    g_type_class_add_private(object_class, sizeof(GGrnContextPrivate));
}

/**
 * ggrn_context_new:
 *
 * Allocates a new #GGrnContext.
 *
 * Returns: a new #GGrnContext.
 */
GGrnContext *
ggrn_context_new(void)
{
    GGrnContext *context;
    context = g_object_new(GGRN_TYPE_CONTEXT, NULL);
    return context;
}

/**
 * ggrn_context_open_database:
 * @context: A #GGrnContext.
 * @path: The path of the database to be opened.
 * @error: return location for a GError, or %NULL.
 *
 * Opens a database.
 *
 * Returns: TRUE on success, FALSE if an error occurred.
 */
gboolean
ggrn_context_open_database(GGrnContext *context,
                           const gchar *path, GError **error)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    grn_obj *using_database;

    using_database = grn_ctx_db(priv->ctx);
    if (using_database) {
        grn_db_close(priv->ctx, using_database);
    }

    grn_db_open(priv->ctx, path);
    return _ggrn_rc_check(priv->ctx->rc, error);
}

/**
 * ggrn_context_execute_command:
 * @context: A #GGrnContext.
 * @command: (array length=command_length) (element-type gchar):
 *   The Groonga command to be executed. See
 *   http://groonga.org/docs/reference/command.html about Groonga command.
 * @command_length: The length of @command, or -1 if @command is a
 *   NULL-terminated string.
 * @result: (out) (allow-none) (array length=result_length) (element-type gint8):
 *   The return location for the executed result of @command.
 *   It must be freed with g_free() when no longer needed.
 * @result_length: (out) (allow-none):
 *   The return location for the length of @result.
 *
 * Executes a Groonga command and returns the executed result.
 */
void
ggrn_context_execute_command(GGrnContext *context,
                             const gchar *command, gssize command_length,
                             gchar **result, gsize *result_length)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    gint flags = 0;
    gchar *received_result;
    guint received_result_length;
    gint received_flags;

    if (command_length == -1) {
        command_length = strlen(command);
    }
    grn_ctx_send(priv->ctx, command, command_length, flags);
    grn_ctx_recv(priv->ctx,
                 &received_result, &received_result_length, &received_flags);
    if (result) {
        *result = g_strndup(received_result, received_result_length);
    }
    if (result_length) {
        *result_length = received_result_length;
    }
}
