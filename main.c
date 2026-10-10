#include "src/global.h"
#include "src/get_device/get_hid.h"
#include "src/make_packet/make_packet.h"
#include "src/make_packet/struct.h"
#include "src/send_packet/send_packet.h"
#include <hidapi/hidapi.h>
#include <stdio.h>

int main() {
    if(hid_init() != 0) {
        fprintf(stderr, "error initializing HIDAPI\n");
        return 0;
    } else {
        fprintf(stdout, "HIDAPI initialized\n");
    }

    hid_device* handle = get_hid();
    if(handle == 0) {
        fprintf(stderr, "error getting HID handle\n");
        return 0;
    } else {
        fprintf(stdout, "HID handle: %#x\n", handle);
    }

    Color color = makeColor(255, 255, 255);
    DpiLevel dpi = makeDpiLevel(0x0C, 0x0C, 0);
    Cfg1Packet packet = make_cfg1(100, 5, 0, (Color){0,0,0}, (DpiLevel){0,0,0});

    int written_bytes = send_packet(handle, &packet);
    if(written_bytes < 0) {
        fprintf(stderr, "Error in hid_write: %ls\n", hid_error(handle));
        return 0;
    } else {
        fprintf(stdout, "wrote %i bytes\n", written_bytes);
    }
}
