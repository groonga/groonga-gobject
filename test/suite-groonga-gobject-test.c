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

#include <groonga-gobject/ggrn.h>

void groonga_gobject_test_warmup(void);
void groonga_gobject_test_cooldown(void);

void
groonga_gobject_test_warmup(void)
{
    ggrn_init(NULL);
}

void
groonga_gobject_test_cooldown(void)
{
    ggrn_fin(NULL);
}
