#include "../global.h"
#include "get_hid.h"

hid_device* get_hid() {
    hid_device* handle = hid_open(VID, PID, NULL);
    if(!handle)
        return 0;

    else 
        return handle;
}