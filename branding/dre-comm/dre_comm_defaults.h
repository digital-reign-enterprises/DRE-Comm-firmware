// DRE-Comm network defaults, shared by every DRE-Comm board.
// Points each board at the DRE-Comm MQTT network using Meshtastic's own USERPREFS_* hooks,
// so no upstream source file has to change. These only take effect on a fresh install or factory reset
// (installDefaultModuleConfig); a device updated over an old config keeps its old MQTT settings.
//
// Anything set with -D (build flags, PLATFORMIO_BUILD_FLAGS) or in userPrefs.jsonc wins over these,
// because every value below is wrapped in #ifndef.
#pragma once

// The public broker password is not committed. CI writes dre_comm_secrets.h from a GitHub secret;
// locally, copy dre_comm_secrets.h.example to dre_comm_secrets.h. It is git-ignored.
#if __has_include("dre_comm_secrets.h")
#include "dre_comm_secrets.h"
#endif

// ---- DRE-Comm network values (PROPOSED: confirm before shipping units) ----
#ifndef DRE_COMM_MQTT_ADDRESS
#define DRE_COMM_MQTT_ADDRESS "mqtt.digitalreignenterprises.com" // EXAMPLE hostname, not created yet
#endif
#ifndef DRE_COMM_MQTT_USERNAME
#define DRE_COMM_MQTT_USERNAME "dre-public" // shared public account, like Meshtastic's meshdev
#endif
#ifndef DRE_COMM_MQTT_PASSWORD
#define DRE_COMM_MQTT_PASSWORD "NOT-SET" // placeholder: devices will fail to log in until a real build sets it
#endif
#ifndef DRE_COMM_MQTT_ROOT
#define DRE_COMM_MQTT_ROOT "msh/US/DRE" // must match the broker ACL in dre-mqtt/mosquitto/config/acl
#endif

// ---- Map onto Meshtastic's userPrefs hooks (src/mesh/NodeDB.cpp) ----
// MQTT module on, so the device is ready; nothing is sent until the owner turns on uplink for a channel
// or map reporting (both stay off by default, as in stock Meshtastic).
#ifndef USERPREFS_MQTT_ENABLED
#define USERPREFS_MQTT_ENABLED 1
#endif
#ifndef USERPREFS_MQTT_ADDRESS
#define USERPREFS_MQTT_ADDRESS DRE_COMM_MQTT_ADDRESS
#endif
#ifndef USERPREFS_MQTT_USERNAME
#define USERPREFS_MQTT_USERNAME DRE_COMM_MQTT_USERNAME
#endif
#ifndef USERPREFS_MQTT_PASSWORD
#define USERPREFS_MQTT_PASSWORD DRE_COMM_MQTT_PASSWORD
#endif
#ifndef USERPREFS_MQTT_ROOT_TOPIC
#define USERPREFS_MQTT_ROOT_TOPIC DRE_COMM_MQTT_ROOT
#endif
// Keep channel packets encrypted on the broker (same as Meshtastic's 2.7.26 default)
#ifndef USERPREFS_MQTT_ENCRYPTION_ENABLED
#define USERPREFS_MQTT_ENCRYPTION_ENABLED true
#endif
// TLS on port 8883. Note: the ESP32 firmware encrypts but does not verify the broker certificate.
#ifndef USERPREFS_MQTT_TLS_ENABLED
#define USERPREFS_MQTT_TLS_ENABLED true
#endif

// Region is deliberately NOT preset: a new device asks its owner to choose one, as stock Meshtastic does.
// To ship US units preset, add  -D USERPREFS_CONFIG_LORA_REGION=meshtastic_Config_LoRaConfig_RegionCode_US
// to that build (decision pending, see ROADMAP.md open questions).
