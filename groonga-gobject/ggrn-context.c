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

#include <groonga.h>

#include "ggrn-context.h"

/**
* SECTION: ggrn-context
* @short_description: A greeter.
*
* The #GGrnContext is a class to keep display friendly greetings.
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
