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

#include "inizer-str.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

bool str_is_null_or_empty(const char *value) { return value == NULL || strcmp(value, STR_EMPTY) == 0; }

bool str_is_equal(const char *value, const char* expected) { return strcmp(value, expected) == 0; }

char *str_new() { return str_new_len(STR_MAX_LENGTH); }

char *str_new_len(const int length) {
  char *str = malloc(length + 1);
  return str;
}
