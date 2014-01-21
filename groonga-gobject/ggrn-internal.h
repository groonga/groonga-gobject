/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * Copyright (C) 2013-2014  Kouhei Sutou <kou@clear-code.com>
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

#ifndef GGRN_INTERNAL_H
#define GGRN_INTERNAL_H

#include <glib.h>
#include <groonga.h>

#include "ggrn-context.h"

G_BEGIN_DECLS

G_GNUC_INTERNAL gboolean _ggrn_rc_check (grn_rc rc, GError **error);

G_GNUC_INTERNAL grn_ctx *_ggrn_context_get_ctx (GGrnContext *context);

G_END_DECLS

#endif
