#include "../global.h"
#include "../make_packet/struct.h"

// return written bytes
int send_packet(hid_device* handle, Cfg1Packet* packet) {
    return hid_write(handle, (unsigned char*)&packet, sizeof(packet));
}