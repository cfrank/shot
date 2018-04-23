#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "shot.h"

// Version macros
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

static struct option const long_options[9] = {
        {"custom", optional_argument, NULL, 'c'},
        {"flush", no_argument, NULL, 'h'},
        {"full", no_argument, NULL, 'f'},
        {"output", required_argument, NULL, 'o'},
        {"screen", optional_argument, NULL, 's'},
        {"timeout", required_argument, NULL, 't'},
        {"window", no_argument, NULL, 'w'},
        {"version", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0},
};

int main(int argc, char **argv)
{
        int option;

        /* Set initial settings values */
        struct setting *shot_settings = init_settings();

        while ((option = getopt_long(argc, argv, "c::hfo:s::t:wv", long_options, NULL)) != -1) {
                switch (option) {
                case 'c':
                        shot_settings->type = CUSTOM;
                        return EXIT_SUCCESS;
                case 'h':
                        shot_settings->flush = true;
                        break;
                case 'f':
                        // shot_settings uses FULL as the default value already
                        return EXIT_SUCCESS;
                case 'o':
                        if (optarg != NULL) {
                                shot_settings->custom_out = optarg;
                        }

                        break;
                case 's':
                        shot_settings->type = SCREEN;

                        if (optarg != NULL) {
                                shot_settings->screen_num = (int8_t)atoi(optarg);
                        }

                        return EXIT_SUCCESS;
                case 'v':
                        printf("%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

                        return EXIT_SUCCESS;
                case '?':
                        printf("%s", "Error!");
                        return EXIT_FAILURE;
                default:
                        printf("%s", "Not found?");
                        return EXIT_FAILURE;
                }
        }

        // Default
        printf("%s", "Nothing happened here");

        return EXIT_SUCCESS;
}

static struct setting *init_settings(void)
{
        struct setting *settings = malloc(sizeof(struct setting));

        if (settings == NULL) {
                return NULL;
        }

        settings->type = FULL;
        settings->timeout = 0;
        // use default screen
        settings->screen_num = -1;
        settings->custom_out = NULL;
        settings->flush = false;

        return settings;
}
