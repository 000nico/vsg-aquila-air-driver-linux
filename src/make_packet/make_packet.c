#include "../global.h"
#include "make_packet.h"
#include "struct.h"

Cfg1Packet make_cfg1(uint8_t light, uint8_t speed, uint8_t led_mode, Color colors, DpiLevel dpi) {
    Cfg1Packet packet = {};
    packet.report_id = 0x04;
    packet.cmd[0] = 0xA0; packet.cmd[1] = 0x01; packet.cmd[2] = 0x02;
    packet.unk4 = 0x02;
    packet.pkt_num = 0x00;

    packet.body.magic0 = 0xA5;
    packet.body.magic1 = 0xA5;
    packet.body.active_idx = 0x00;
    packet.body.dpi_mask = 0x7F;
    packet.body.rate = 0x03;
    packet.body.angle_lod = 0x1A;
    packet.body.led_light = 100;
    packet.body.led_speed = 0x02;
    packet.body.led_mode = 0x01;
    packet.body.led_profile = 0x01;
    packet.body.flags = 0x14;
    packet.body.dpi[0] = (DpiLevel){0x00, 0x0C, 0x0C};
    packet.body.dpi[1] = (DpiLevel){0x00, 0x10, 0x10};
    packet.body.dpi[2] = (DpiLevel){0x00, 0x18, 0x18};
    packet.body.dpi[3] = (DpiLevel){0x00, 0x30, 0x30};
    packet.body.dpi[4] = (DpiLevel){0x00, 0x40, 0x40};
    packet.body.dpi[5] = (DpiLevel){0x00, 0x80, 0x80};
    packet.body.dpi[6] = (DpiLevel){0x11, 0x40, 0x40};

    packet.body.colors[0] = (Color){0xFF, 0x00, 0x00};
    packet.body.colors[1] = (Color){0x00, 0xFF, 0x00};
    packet.body.colors[2] = (Color){0x00, 0xFF, 0x00};
    packet.body.colors[3] = (Color){0xFF, 0xFF, 0x00};
    packet.body.colors[4] = (Color){0x00, 0xFF, 0xFF};
    packet.body.colors[5] = (Color){0xFF, 0xFF, 0x00};
    packet.body.colors[6] = (Color){0xFF, 0xFF, 0xFF};

    packet.body.color_flag = 0x7F;

    return packet;
}

DpiLevel makeDpiLevel(uint16_t x, uint16_t y, uint8_t color) {
    DpiLevel dpi;

    uint8_t x_high = (x >> 8) & 0x0F;
    uint8_t y_high = (y >> 8) & 0x01;

    dpi.hi = (x_high << 4) | (color << 1) | y_high;
    dpi.x_lo = x & 0xFF;
    dpi.y_lo = y & 0x0FF;
    return dpi;
}

Color makeColor(uint8_t r, uint8_t g, uint8_t b) {
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}
