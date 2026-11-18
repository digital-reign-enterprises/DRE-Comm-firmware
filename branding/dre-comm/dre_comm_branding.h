// DRE-Comm boot branding, shared by every DRE-Comm board with a screen.
// The stock Meshtastic splash shows first, then this DRE-Comm screen
// (antenna + "DRE-Comm" wordmark, both drawn in the logo bitmap).
// Regenerate the logo with: python branding/dre-comm/make_logo.py [--image your_logo.png]
#pragma once
#include "dre_comm_logo.h"
#define USERPREFS_OEM_TEXT "" // wordmark is in the bitmap; keep high-res screens from drawing it twice
#define USERPREFS_OEM_FONT_SIZE 1

// DRE-Comm network defaults (MQTT server, topic root, TLS) ride along with the branding,
// since every DRE-Comm variant.h already includes this file.
#include "dre_comm_defaults.h"
