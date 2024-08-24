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

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "inizer-api.h"

#include "inizer-logging.h"
#include "inizer-str.h"

static GKeyFile *parse_keyfile(const char *file_path) {
    GKeyFile *key_file = g_key_file_new();
    GError *error = NULL;

    if (!g_key_file_load_from_file(key_file, file_path, G_KEY_FILE_NONE, &error)) {
        log_warn(g_strdup_printf("Error loading config file: %s", error->message));
        g_error_free(error);
    }

    return key_file;
}

static const char *read_config_value(GKeyFile *config_data, const char *config_section, const char *key) {
    GError *error = NULL;

    const char *config_value = g_key_file_get_string(config_data, config_section, key, &error);

    if (error) {
        log_warn(g_strdup_printf("Error reading config value: %s", error->message));
        g_error_free(error);
        return STR_EMPTY;
    }

    return strdup(config_value);
}

static int save_config_file(GKeyFile *key_file, const char *file_path) {
    GError *error = NULL;

    if (!g_key_file_save_to_file(key_file, file_path, &error)) {
        log_warn(g_strdup_printf("Error saving config file: %s", error->message));
        g_error_free(error);
        return 1;
    }

    return 0;
}

const char *inizer_get_value(const char *file_path, const char *section_name, const char *key) {
    GKeyFile *config_data = parse_keyfile(file_path);

    const char *config_value = read_config_value(config_data, section_name, key);

    g_key_file_free(config_data);

    return config_value;
}

int inizer_set_value(const char *file_path, const char *section_name, const char *key, const char *value) {
    GKeyFile *config_data = parse_keyfile(file_path);

    g_key_file_set_value(config_data, section_name, key, value);

    int file_save_status = save_config_file(config_data, file_path);

    g_key_file_free(config_data);

    return file_save_status;
}
