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

//region Utility functions

static GKeyFile *parse_keyfile(const char *file_path) {
    GKeyFile *key_file = g_key_file_new();
    GError *error = NULL;

    if (!g_key_file_load_from_file(key_file, file_path, G_KEY_FILE_NONE, &error)) {
        log_warn(g_strdup_printf("Error loading config file: %s", error->message));
        g_error_free(error);
    }

    return key_file;
}

static int count_keys_in_config_section(GKeyFile *config_data, const gchar *config_section) {
    GError *error = NULL;
    gsize key_count = -1;

    g_key_file_get_keys(config_data, config_section, &key_count, &error);

    if (error) {
        log_error(g_strdup_printf("Error reading config section: %s", error->message));
        g_error_free(error);
    }

    return key_count;
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

static int delete_config_section(GKeyFile *config_data, const char *config_section) {
    GError *error = NULL;

    if (!g_key_file_remove_group(config_data, config_section, &error)) {
        log_warn(g_strdup_printf("Error deleting config section: %s", error->message));
        g_error_free(error);
        return 1;
    }

    return 0;
}

static int delete_config_value(GKeyFile *config_data, const char *config_section, const char *key) {
    GError *error = NULL;

    if (!g_key_file_remove_key(config_data, config_section, key, &error)) {
        log_warn(g_strdup_printf("Error deleting config value: %s", config_section, error->message));
        g_error_free(error);
        return 1;
    }

    return 0;
}

//endregion

//region Utility functions

const char *inizer_get_value(const char *file_path, const char *section_name, const char *key) {
    GKeyFile *config_data = parse_keyfile(file_path);

    const char *config_value = read_config_value(config_data, section_name, key);

    g_key_file_free(config_data);

    return config_value;
}

int inizer_set_value(const char *file_path, const char *section_name, const char *key, const char *value) {
    GKeyFile *config_data = parse_keyfile(file_path);

    g_key_file_set_value(config_data, section_name, key, value);

    const int file_save_status = save_config_file(config_data, file_path);

    g_key_file_free(config_data);

    return file_save_status;
}

int inizer_unset_value(const char *file_path, const char *section_name, const char *key) {
    GKeyFile *config_data = parse_keyfile(file_path);

    const int delete_value_status = delete_config_value(config_data, section_name, key);

    if (delete_value_status != 0) {
        g_key_file_free(config_data);
        return delete_value_status;
    }

    const int remaining_section_key_count = count_keys_in_config_section(config_data, (gchar *) section_name);

    // Don't delete the config section if it still houses other keys
    if (remaining_section_key_count > 0) {
        goto save_file;
    }

    const int delete_section_status = delete_config_section(config_data, section_name);

    if (delete_section_status != 0) {
        g_key_file_free(config_data);
        return delete_section_status;
    }

save_file:

    const int file_save_status = save_config_file(config_data, file_path);

    g_key_file_free(config_data);

    return file_save_status;
}

//endregion
