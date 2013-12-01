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

#include "ggrn-internal.h"
#include "ggrn-error.h"

gboolean
_ggrn_rc_check(grn_rc rc, GError **error)
{
    GGrnError ggrn_error = (GGrnError)rc;

    if (rc == GRN_SUCCESS) {
        return TRUE;
    }

    g_set_error(error, GGRN_ERROR,
                ggrn_error,
                "%s (%d)",
                ggrn_error_to_string(ggrn_error),
                rc);
    return FALSE;
}
