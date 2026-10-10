#pragma once
#include "../global.h"
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t r, g, b;
} Color;

typedef struct {
    uint8_t hi;
    uint8_t x_lo;
    uint8_t y_lo;
} DpiLevel;

typedef struct {
    uint8_t magic0; // v125 A5
    uint8_t active_idx; // v126[0] hipotesis
    uint8_t dpi_mask; // v126[1] 7F
    DpiLevel dpi[8]; // v126[2..25]
    uint8_t rate; // v126[26]
    uint8_t angle_lod; // v126[27]
    uint8_t flags; // v126[28]
    uint8_t magic1; // v126[29] = A5
    uint8_t led_mode; // v126[30]
    uint8_t led_speed; // v126[31]
    uint8_t led_light; // v126[32]
    uint8_t led_profile; // v126[33]
    uint8_t color_flag; // v126[34]
    Color colors[7]; // v126[35.55]
    uint8_t unknown; // v126[56..64] = 0
} CfgBody;

typedef struct {
    uint8_t report_id; // 04
    uint8_t cmd[3];
    uint8_t pkt_num;
    uint8_t unk4;
    CfgBody body;
} Cfg1Packet;
#pragma pack(pop)
_Static_assert(sizeof(CfgBody) == 58, "bad count");