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

#ifndef INIZER_API_H
#define INIZER_API_H

const char *inizer_get_value(const char *file_path, const char *section_name, const char *key);

int inizer_set_value(const char *file_path, const char *section_name, const char *key, const char *value);

#endif // INIZER_API_H
