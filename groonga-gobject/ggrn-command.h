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

#ifndef GGRN_COMMAND_H
#define GGRN_COMMAND_H

#include <groonga-gobject/ggrn-context.h>

G_BEGIN_DECLS

#define GGRN_TYPE_COMMAND \
  (ggrn_command_get_type())
#define GGRN_COMMAND(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GGRN_TYPE_COMMAND, GGrnCommand))
#define GGRN_COMMAND_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), GGRN_TYPE_COMMAND, GGrnCommandClass))
#define GGRN_IS_COMMAND(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GGRN_TYPE_COMMAND))
#define GGRN_IS_COMMAND_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), GGRN_TYPE_COMMAND))
#define GGRN_COMMAND_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS((obj), GGRN_TYPE_COMMAND, GGrnCommandClass))

typedef struct _GGrnCommand         GGrnCommand;
typedef struct _GGrnCommandClass    GGrnCommandClass;

/**
 * GGrnCommand:
 *
 * A GGrnCommand is an object to create a Groonga command string. It
 * is executable by ggrn_context_execute_command().
 */
struct _GGrnCommand
{
    /*< private >*/
    GObject parent_instance;
};

struct _GGrnCommandClass
{
    GObjectClass parent_class;
};

GType                ggrn_command_get_type          (void) G_GNUC_CONST;
GGrnCommand         *ggrn_command_new               (GGrnContext *context,
                                                     const gchar *name);
void                 ggrn_command_add_argument      (GGrnCommand *command,
                                                     const gchar *name,
                                                     const gchar *value);
gchar               *ggrn_command_escape            (GGrnCommand *command,
                                                     const gchar *value,
                                                     const gchar *target_characters,
                                                     char         escape_character);
gchar               *ggrn_command_escape_query      (GGrnCommand *command,
                                                     const gchar *query);
gchar               *ggrn_command_execute           (GGrnCommand *command);
gchar               *ggrn_command_to_path           (GGrnCommand *command);
gchar               *ggrn_command_to_command_line   (GGrnCommand *command);

G_END_DECLS

#endif
