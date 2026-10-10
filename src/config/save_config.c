#include "config.h"

#include <stdio.h>
#include <stdlib.h>

const char* config_file(void) {
    static char path[512];
    const char* home = getenv("HOME");
    snprintf(path, sizeof(path), "%s/.aquila-air.conf", home ? home : ".");
    return path;
}

void save_config(void) {
    FILE* f = fopen(config_file(), "w");
    if (!f)
        return;

    fprintf(f, "color %u %u %u\n",
            packet.body.colors[0].r, packet.body.colors[0].g, packet.body.colors[0].b);
    fprintf(f, "effect %u\n", packet.body.led_mode);
    fprintf(f, "light %u\n", packet.body.led_light);
    fprintf(f, "speed %u\n", packet.body.led_speed);

    fclose(f);
}
