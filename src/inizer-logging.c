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

#include "inizer-common.h"

#ifndef NDEBUG
    #define LOG(lvl, msg) \
        { printf("%s-%-6s %s:%d: %s\n", COMMAND_NAME, lvl, __FILE_NAME__, __LINE__, msg); }
#else
    #define LOG(lvl, msg) \
        { printf("%s-%-6s %s\n", COMMAND_NAME, lvl, msg); }
#endif

#define INFO(msg) \
    { LOG("INFO:", msg); }

#define WARN(msg) \
    { LOG("WARN:", msg); }

#define ERROR(msg) \
    { LOG("ERROR:", msg); }

void log_info(const char *msg) { INFO(msg); }
void log_warn(const char *msg) { WARN(msg); }
void log_error(const char *msg) { ERROR(msg); }
