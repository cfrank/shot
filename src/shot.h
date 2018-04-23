#pragma once

#include <stdbool.h>
#include <stdint.h>

enum scrot_type {
        CUSTOM,
        FULL,
        SCREEN,
        WINDOW,
};

struct setting {
        enum scrot_type type;
        uint32_t timeout;
        int8_t screen_num;
        bool use_custom_out;
        char *custom_out;
        bool flush;
};

static struct setting *init_settings(void);
