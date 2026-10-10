#include "config.h"
#include "../send_packet/send_packet.h"

Cfg1Packet packet;
hid_device* handle;

void apply_config(void) {
    send_packet(handle, &packet);
    save_config();
}
