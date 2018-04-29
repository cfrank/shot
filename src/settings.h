#pragma once

#include <stdbool.h>
#include <stdint.h>

enum scrot_type {
        CUSTOM,
        FULL,
        SCREEN,
        WINDOW,
};

struct settings {
        enum scrot_type type;
        const char *dimensions;
        uint32_t timeout;
        int8_t screen_num;
        const char *custom_out;
        bool flush;
};

static struct settings *init_settings(void);
static void destroy_settings(struct settings *shot_settings);
