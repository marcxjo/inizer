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

#include <libgen.h>
#include <stdio.h>
#include <glib.h>

#include "inizer-api.h"
#include "inizer-common.h"
#include "inizer-logging.h"
#include "inizer-str.h"

void usage() {
    printf("Usage:\n"
           "    %1$s get FILE_PATH CONFIG_SECTION KEY\n"
           "    %1$s set FILE_PATH CONFIG_SECTION KEY VALUE\n",
           COMMAND_NAME
    );
}

int main(int argc, char *argv[]) {
    const char *verb, *file_path, *config_section, *key, *value;
    const char *cmd = basename(argv[0]);
    // Enable logs to display the program name in logs
    g_set_prgname(cmd);

    if (argc < 2) {
        usage();
        return 1;
    }

    verb = argv[1];

    if (str_is_equal(verb, "get")) {
        if (argc < 5) {
            log_error("no key specified");
            usage();
            return 1;
        }

        file_path = argv[2];
        config_section = argv[3];
        key = argv[4];

        value = inizer_get_value(file_path, config_section, key);
        printf("%s\n", value);

        return 0;
    }

    if (str_is_equal(verb, "set")) {
        if (argc < 6) {
            log_error("no value specified");
            usage();
            return 1;
        }

        file_path = argv[2];
        config_section = argv[3];
        key = argv[4];
        value = argv[5];

        int write_status = inizer_set_value(file_path, config_section, key, value);

        if (write_status != 0) {
            printf("failed to write config section key value\n");
            usage();
            return 1;
        }

        return 0;
    }

    if (str_is_equal(verb, "unset")) {
        if (argc < 5) {
            log_error("no key specified");
            usage();
            return 1;
        }

        file_path = argv[2];
        config_section = argv[3];
        key = argv[4];

        const int delete_status = inizer_unset_value(file_path, config_section, key);

        return delete_status;
    }

    usage();
    return 1;
}
