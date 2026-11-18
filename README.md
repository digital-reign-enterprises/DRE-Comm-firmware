# DRE-Comm Firmware

DRE-Comm is Digital Reign Enterprises' build of [Meshtastic®](https://meshtastic.org) firmware for DRE-Comm radios.
It stays mesh-compatible with stock Meshtastic nodes. Source is provided under the GPLv3, the same license as upstream.

- DRE-Comm builds (one per supported board):
  `dre-comm-heltec-v3`, `dre-comm-heltec-v4`, `dre-comm-heltec-wireless-tracker` (V1.1), `dre-comm-heltec-wireless-tracker-v2`,
  `dre-comm-heltec-wsl-v3` (Wireless Stick Lite V3), `dre-comm-heltec-wireless-stick-v3` (Wireless Stick V3/V3.1 with OLED), `dre-comm-t-deck` (classic screens), `dre-comm-t-deck-tft` (touchscreen UI)
- Build one: `pio run -e dre-comm-heltec-v3`
- Change the boot logo: `python branding/dre-comm/make_logo.py --image your_logo.png`
- Every DRE-Comm build ships pointed at the DRE-Comm MQTT network (settings in `branding/dre-comm/dre_comm_defaults.h`).
  MQTT uplink and map reporting stay off until the owner turns them on, as in stock Meshtastic.
- Based on Meshtastic **stable** releases only. Plan: [ROADMAP.md](ROADMAP.md). Syncing with upstream: [dre/SYNC.md](dre/SYNC.md).

Meshtastic® is a registered trademark of Meshtastic LLC. DRE-Comm is not affiliated with or endorsed by Meshtastic LLC.

---

<div align="center" markdown="1">

<img src=".github/meshtastic_logo.png" alt="Meshtastic Logo" width="80"/>
<h1>Meshtastic Firmware</h1>

![GitHub release downloads](https://img.shields.io/github/downloads/meshtastic/firmware/total)
[![CI](https://img.shields.io/github/actions/workflow/status/meshtastic/firmware/main_matrix.yml?branch=master&label=actions&logo=github&color=yellow)](https://github.com/meshtastic/firmware/actions/workflows/ci.yml)
[![CLA assistant](https://cla-assistant.io/readme/badge/meshtastic/firmware)](https://cla-assistant.io/meshtastic/firmware)
[![Fiscal Contributors](https://opencollective.com/meshtastic/tiers/badge.svg?label=Fiscal%20Contributors&color=deeppink)](https://opencollective.com/meshtastic/)
[![Vercel](https://img.shields.io/static/v1?label=Powered%20by&message=Vercel&style=flat&logo=vercel&color=000000)](https://vercel.com?utm_source=meshtastic&utm_campaign=oss)

<a href="https://trendshift.io/repositories/5524" target="_blank"><img src="https://trendshift.io/api/badge/repositories/5524" alt="meshtastic%2Ffirmware | Trendshift" style="width: 250px; height: 55px;" width="250" height="55"/></a>

</div>

</div>

<div align="center">
	<a href="https://meshtastic.org">Website</a>
	-
	<a href="https://meshtastic.org/docs/">Documentation</a>
</div>

## Overview

This repository contains the official device firmware for Meshtastic, an open-source LoRa mesh networking project designed for long-range, low-power communication without relying on internet or cellular infrastructure. The firmware supports various hardware platforms, including ESP32, nRF52, RP2040/RP2350, and Linux-based devices.

Meshtastic enables text messaging, location sharing, and telemetry over a decentralized mesh network, making it ideal for outdoor adventures, emergency preparedness, and remote operations.

### Get Started

- 🔧 **[Building Instructions](https://meshtastic.org/docs/development/firmware/build)** – Learn how to compile the firmware from source.
- ⚡ **[Flashing Instructions](https://meshtastic.org/docs/getting-started/flashing-firmware/)** – Install or update the firmware on your device.

Join our community and help improve Meshtastic! 🚀

## Stats

![Alt](https://repobeats.axiom.co/api/embed/8025e56c482ec63541593cc5bd322c19d5c0bdcf.svg "Repobeats analytics image")
