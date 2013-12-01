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

#include "ggrn.h"

/**
 * ggrn_init:
 * @error: return location for a GError, or %NULL.
 *
 * Initialize Groonga GObject. You must call this function before
 * you use any Groonga GObject functions.
 *
 * Returns: TRUE on success, FALSE if an error occurred.
 */
gboolean
ggrn_init(GError **error)
{
    grn_init();
    return TRUE;
}

/**
 * ggrn_fin:
 * @error: return location for a GError, or %NULL.
 *
 * Finalize Groonga GObject. You must call this function after you
 * finish to use Groonga GObject.
 *
 * Returns: TRUE on success, FALSE if an error occurred.
 */
gboolean
ggrn_fin(GError **error)
{
    grn_fin();
    return TRUE;
}
