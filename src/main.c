#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "settings.h"

/* Version macros */
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

/* One off command function prototypes */
static void print_usage(void);
static void print_help(void);
static void print_version(void);

static struct option const long_options[9] = {
        {"custom", optional_argument, NULL, 'c'},
        {"flush", no_argument, NULL, 'f'},
        {"full", no_argument, NULL, 'e'},
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
        struct settings *shot_settings = init_settings();

        if (shot_settings == NULL) {
                return EXIT_FAILURE;
        }

        while ((option = getopt_long(argc, argv, "c::hfo:s::t:wv", long_options, NULL)) != -1) {
                switch (option) {
                case 'c':
                        shot_settings->type = CUSTOM;

                        if (optarg != NULL) {
                                shot_settings->dimensions = optarg;
                        }

                        return EXIT_SUCCESS;
                case 'f':
                        shot_settings->flush = true;
                        break;
                case 'e':
                        /* shot_settings uses FULL as the default value already */
                        break;
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

                        break;
                case 't':
                        shot_settings->timeout = (uint32_t)atoi(optarg);
                        break;
                case 'v':
                        print_version();
                        goto success;
                case 'h':
                        print_help();
                        goto success;
                case '?':
                default:
                        print_help();
                        goto error;
                }
        }

        /* No arguments were supplied */
        puts("Nothing happened here!");

        goto success;

error:
        destroy_settings(shot_settings);
        return EXIT_FAILURE;
success:
        destroy_settings(shot_settings);
        return EXIT_SUCCESS;
}

/* Some helper functions for dealing with settings */
static struct settings *init_settings(void)
{
        struct settings *shot_settings = malloc(sizeof(struct settings));

        if (shot_settings == NULL) {
                return NULL;
        }

        shot_settings->type = FULL;
        shot_settings->timeout = 0;
        /* use default screen */
        shot_settings->screen_num = -1;
        shot_settings->custom_out = NULL;
        shot_settings->flush = false;

        return shot_settings;
}

static void destroy_settings(struct settings *shot_settings)
{
        if (shot_settings != NULL) {
                free(shot_settings);
        }
}

/* Some functions to handle one off commands */
static void print_usage(void)
{
        fprintf(stderr, "usage: shot [-chfostwv]\n");
}

/* TODO: This needs to be cleaned up */
static void print_help(void)
{
        print_usage();
        puts("\
  -c, --custom=?DIMENSIONS    Take a variable sized screenshot of \
either DIMENSIONS or a user selected portion of the screen\n\
  -h, --flush                 Clear the terminal before taking the \
screenshot\n\
  -f, --full                  Take a screenshot of the full display\n\
  -o, --output=OUTPUT         Choose the ouput file/location\n\
  -s, --screen=?SCREEN        Take a screenshot of a particular screen \
if SCREEN is omitted the first screen will be used\n\
  -t, --timeout=TIMEOUT       Wait TIMEOUT seconds before taking a \
screenhot\n\
  -w, --window                Take a screenshot of a particular window\n\
  -v, --version               Print version information");
}

static void print_version(void)
{
        printf("Shot - Version: %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
        print_usage();
}
