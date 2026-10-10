#pragma once

#include "make_packet/struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <hidapi/hidapi.h>

#define VID 0x2EA8
#define PID 0x2203

extern Cfg1Packet packet;
extern hid_device* handle;