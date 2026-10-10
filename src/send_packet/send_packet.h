#pragma once
#include "../global.h"
#include "../make_packet/struct.h"

int send_packet(hid_device* handle, Cfg1Packet* packet);