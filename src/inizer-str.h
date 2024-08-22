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

#ifndef INIZER_UTILS_H
#define INIZER_UTILS_H

#include <stdbool.h>

#define STR_MAX_LENGTH 128
#define STR_EMPTY ""

bool str_is_null_or_empty(const char *value);

bool str_is_equal(const char *value, const char *expected);

char *str_new();

char *str_new_len(int length);

#endif //INIZER_UTILS_H
