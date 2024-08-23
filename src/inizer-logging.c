/*
 * Copyright (c) 2024 Mark Givens
 *
 * This file is part of inizer.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <glib.h>

#include "inizer-common.h"

#ifndef NDEBUG // Then no-op all logs
               // This will probably eventually be refactored to consume a config setting
    #define INFO(msg) {}
    #define WARN(msg) {}
    #define ERROR(msg) {}
#else
    #define INFO(msg) { g_info(msg); }
    #define WARN(msg) { g_warning(msg); }
    #define ERROR(msg) { g_critical(msg); }
#endif

void log_info(const char *msg) { INFO(msg); }
void log_warn(const char *msg) { WARN(msg); }
void log_error(const char *msg) { ERROR(msg); }
