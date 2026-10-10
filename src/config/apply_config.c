#include "config.h"
#include "../send_packet/send_packet.h"

Cfg1Packet packet;
hid_device* handle;

void apply_config(void) {
    packet.body.color_flag = (packet.body.led_mode == 2 || packet.body.led_mode == 8) ? 0x01 : 0x7F;

    if (send_packet(handle, &packet) < 0)
        fprintf(stderr, "Error in hid_write: %ls\n", hid_error(handle));

    save_config();
}
