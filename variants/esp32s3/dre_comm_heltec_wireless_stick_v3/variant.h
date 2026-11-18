// DRE-Comm on Heltec Wireless Stick V3 / V3.1 (the one with the 0.49" 64x32 OLED; not the screenless Stick Lite).
// Its pins (LoRa, OLED I2C 17/18, OLED reset 21, Vext 36, LED 35, button 0) match the WiFi LoRa 32 V3 exactly,
// so it reuses the stock Heltec V3 variant and only changes the screen size.
#include "../heltec_v3/variant.h"

// Tiny 64x32 panel: Meshtastic's compact tiny-screen UI and the matching display geometry
#define OLED_TINY
#define OLED_GEOMETRY_OVERRIDE GEOMETRY_64_32

#include "../../../branding/dre-comm/dre_comm_branding.h"
