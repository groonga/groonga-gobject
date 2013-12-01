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

#ifndef GGRN_CONTEXT_H
#define GGRN_CONTEXT_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GGRN_TYPE_CONTEXT \
  (ggrn_context_get_type())
#define GGRN_CONTEXT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GGRN_TYPE_CONTEXT, GGrnContext))
#define GGRN_CONTEXT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), GGRN_TYPE_CONTEXT, GGrnContextClass))
#define GGRN_IS_CONTEXT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GGRN_TYPE_CONTEXT))
#define GGRN_IS_CONTEXT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), GGRN_TYPE_CONTEXT))
#define GGRN_CONTEXT_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS((obj), GGRN_TYPE_CONTEXT, GGrnContextClass))

typedef struct _GGrnContext         GGrnContext;
typedef struct _GGrnContextClass    GGrnContextClass;

/**
 * GGrnContext:
 *
 * A GGrnContext is the operation context for a database.
 */
struct _GGrnContext
{
    /*< private >*/
    GObject parent_instance;
};

struct _GGrnContextClass
{
    GObjectClass parent_class;
};

GType                ggrn_context_get_type          (void) G_GNUC_CONST;
GGrnContext         *ggrn_context_new               (void);

G_END_DECLS

#endif
