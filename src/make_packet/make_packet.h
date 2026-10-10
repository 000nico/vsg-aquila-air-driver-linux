#pragma once
#include "struct.h"

Color makeColor(uint8_t r, uint8_t g, uint8_t b);
DpiLevel makeDpiLevel(uint16_t hi, uint16_t x_lo, uint8_t y_lo);
Cfg1Packet make_cfg1(uint8_t light, uint8_t speed, uint8_t led_mode, Color colors, DpiLevel dpi);