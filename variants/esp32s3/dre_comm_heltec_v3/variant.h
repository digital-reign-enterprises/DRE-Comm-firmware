// DRE-Comm on Heltec WiFi LoRa 32 V3 hardware.
// Pins come from the stock Heltec V3 variant; this file only adds DRE-Comm branding.
#include "../heltec_v3/variant.h"

// Boot screen: the stock Meshtastic splash shows first, then this DRE-Comm screen
// (antenna + "DRE-Comm" wordmark, both drawn in the logo bitmap).
// Regenerate the logo with: python branding/dre-comm/make_logo.py [--image your_logo.png]
#include "dre_comm_logo.h"
#define USERPREFS_OEM_TEXT "" // wordmark is in the bitmap; keep high-res screens from drawing it twice
#define USERPREFS_OEM_FONT_SIZE 1
