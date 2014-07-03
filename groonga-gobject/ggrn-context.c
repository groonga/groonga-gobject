/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * Copyright (C) 2013-2014  Kouhei Sutou <kou@clear-code.com>
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
    gboolean own_database;
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
    priv->own_database = FALSE;
}

static void
dispose_database(GGrnContextPrivate *priv)
{
    grn_obj *using_database;

    if (!priv->own_database) {
        return;
    }

    using_database = grn_ctx_db(priv->ctx);
    if (using_database) {
        grn_obj_unlink(priv->ctx, using_database);
    }
    priv->own_database = FALSE;
}

static void
dispose(GObject *object)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(object);

    if (priv->ctx) {
        dispose_database(priv);
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
 *
 * Since: 1.0.0
 */
GGrnContext *
ggrn_context_new(void)
{
    GGrnContext *context;
    context = g_object_new(GGRN_TYPE_CONTEXT, NULL);
    return context;
}

grn_ctx *
_ggrn_context_get_ctx(GGrnContext *context)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    return priv->ctx;
}

gboolean
_ggrn_context_check(GGrnContext *context, GError **error)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    return _ggrn_rc_check(priv->ctx->rc, priv->ctx->errbuf, error);
}

/**
 * ggrn_context_open_database:
 * @context: A #GGrnContext.
 * @path: The path of the database to be opened.
 * @error: Return location for a GError, or %NULL.
 *
 * Opens a database.
 *
 * Returns: TRUE on success, FALSE if an error occurred.
 *
 * Since: 1.0.0
 */
gboolean
ggrn_context_open_database(GGrnContext *context,
                           const gchar *path, GError **error)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    gboolean success;

    dispose_database(priv);

    grn_db_open(priv->ctx, path);
    success = _ggrn_context_check(context, error);
    if (success) {
        priv->own_database = TRUE;
    }
    return success;
}

/**
 * ggrn_context_create_database:
 * @context: A #GGrnContext.
 * @path: (allow-none): The path of the database to be created, or %NULL
 *   for temporary database.
 * @error: Return location for a GError, or %NULL.
 *
 * Creates a new database.
 *
 * Returns: TRUE on success, FALSE if an error is occurred.
 *
 * Since: 1.0.0
 */
gboolean
ggrn_context_create_database(GGrnContext *context,
                             const gchar *path, GError **error)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    gboolean success;

    dispose_database(priv);

    grn_db_create(priv->ctx, path, NULL);
    success = _ggrn_context_check(context, error);
    if (success) {
        priv->own_database = TRUE;
    }
    return success;
}

/**
 * ggrn_context_execute_command:
 * @context: A #GGrnContext.
 * @command:
 *   The Groonga command to be executed. See
 *   http://groonga.org/docs/reference/command.html about Groonga command.
 *
 * Executes a Groonga command and returns the executed result.
 *
 * Returns: The executed result of @command. It must be freed with
 *   g_free() when no longer needed.
 *
 * Since: 1.0.0
 */
gchar *
ggrn_context_execute_command(GGrnContext *context,
                             const gchar *command)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    gsize command_length;
    gint flags = 0;
    gchar *received_result;
    guint received_result_length;
    gint received_flags;

    command_length = strlen(command);
    grn_ctx_send(priv->ctx, command, command_length, flags);
    grn_ctx_recv(priv->ctx,
                 &received_result, &received_result_length, &received_flags);
    return g_strndup(received_result, received_result_length);
}

/**
 * ggrn_context_send_command:
 * @context: A #GGrnContext.
 * @command:
 *   The Groonga command to be sent. See
 *   http://groonga.org/docs/reference/command.html about Groonga command.
 * @error: Return location for a GError, or %NULL.
 *
 * Sends a Groonga command. Use ggrn_context_receive_result() to
 * receive the result of the sent command.
 *
 * Normally, you should use high-level API
 * ggrn_context_execute_command(). If you want to get error details of
 * the executed command, use this API.
 *
 * Returns: TRUE on success, FALSE if an error is occurred.
 *
 * Since: 1.0.0
 */
gboolean
ggrn_context_send_command(GGrnContext  *context,
                          const gchar  *command,
                          GError      **error)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    gsize command_length;
    gint flags = 0;

    command_length = strlen(command);
    grn_ctx_send(priv->ctx, command, command_length, flags);
    return _ggrn_context_check(context, error);
}

/**
 * ggrn_context_receive_result:
 * @context: A #GGrnContext.
 *
 * Receives the result of the sent command by ggrn_context_send_command().
 *
 * Returns: The result of the sent command. It must be freed with
 *   g_free() when no longer needed.
 *
 * Since: 1.0.0
 */
gchar *
ggrn_context_receive_result(GGrnContext *context)
{
    GGrnContextPrivate *priv = GGRN_CONTEXT_GET_PRIVATE(context);
    gchar *received_result;
    guint received_result_length;
    gint received_flags;

    grn_ctx_recv(priv->ctx,
                 &received_result, &received_result_length, &received_flags);
    return g_strndup(received_result, received_result_length);
}
