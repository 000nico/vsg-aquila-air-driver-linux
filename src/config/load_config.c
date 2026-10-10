#include "config.h"

#include <stdio.h>

void load_config(void) {
    FILE* f = fopen(config_file(), "r");
    if (!f)
        return;

    unsigned r = 255, g = 255, b = 255, effect = 0, light = 74, speed = 5;
    char key[32];
    while (fscanf(f, "%31s", key) == 1) {
        if (strcmp(key, "color") == 0)
            fscanf(f, "%u %u %u", &r, &g, &b);
        else if (strcmp(key, "effect") == 0)
            fscanf(f, "%u", &effect);
        else if (strcmp(key, "light") == 0)
            fscanf(f, "%u", &light);
        else if (strcmp(key, "speed") == 0)
            fscanf(f, "%u", &speed);
    }
    fclose(f);

    Color c = { (uint8_t)r, (uint8_t)g, (uint8_t)b };
    for (int i = 0; i < 7; i++)
        packet.body.colors[i] = c;
    packet.body.led_mode = (uint8_t)effect;
    packet.body.led_light = (uint8_t)light;
    packet.body.led_speed = (uint8_t)speed;
}
