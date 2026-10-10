#include "src/global.h"
#include "src/get_device/get_hid.h"
#include "src/make_packet/make_packet.h"
#include "src/make_packet/struct.h"
#include "src/send_packet/send_packet.h"
#include "src/config/config.h"
#include "src/imgui/gui.h"
#include <hidapi/hidapi.h>
#include <stdio.h>

int main() {
    if(hid_init() != 0) {
        fprintf(stderr, "error initializing HIDAPI\n");
        return 0;
    } else {
        fprintf(stdout, "HIDAPI initialized\n");
    }

    struct hid_device_info *devs = hid_enumerate(VID, PID);
    struct hid_device_info *cur = devs;

    while (cur) {
        printf("path: %s | interface: %d | usage page: 0x%04X | usage: 0x%04X\n", 
               cur->path, cur->interface_number, cur->usage_page, cur->usage);
          
        if ((cur->usage_page & 0xFF00) == 0xFF00) { 
            handle = hid_open_path(cur->path);
            printf("found\n");
            break;
        }
        cur = cur->next;
    }
    hid_free_enumeration(devs);
    if(handle == 0) {
        fprintf(stderr, "error getting HID handle\n");
        return 0;
    } else {
        fprintf(stdout, "HID handle: %#x\n", handle);
    }

    struct hid_device_info *info = hid_get_device_info(handle);
    if (info) {
        printf("Manufacturer: %ls\n", info->manufacturer_string);
        printf("Product: %ls\n", info->product_string);
        printf("Release: %d\n", info->release_number);
        printf("Interface Number: %d\n", info->interface_number);
        printf("Usage Page: 0x%04X, Usage: 0x%04X\n", info->usage_page, info->usage);
    }

    packet = make_cfg1(74, 5, 2, makeColor(255, 255, 255), (DpiLevel){0, 0, 0});
    load_config();

    apply_config();

    run_gui();
}
