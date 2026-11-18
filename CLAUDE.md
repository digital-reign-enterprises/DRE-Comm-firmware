# DRE-Comm firmware: notes for Claude Code (and people)

Digital Reign Enterprises' fork of Meshtastic firmware. Upstream's own agent notes are in `AGENTS.md` and
`.github/copilot-instructions.md`; read those for how the Meshtastic code works. This file is the DRE part.

## What and where
- GitHub: https://github.com/digital-reign-enterprises/DRE-Comm-firmware (public fork of meshtastic/firmware).
- Default branch: `dre-stable` = Meshtastic **v2.7.26.54e0d8d** (stable, "Latest" on GitHub) + DRE commits.
- Old branches `develop`, `dre-comm-branding`, `dre-comm-more-boards`, `dre-comm-wireless-stick-v3` are the
  earlier work on the 2.8 **alpha** (abandoned: alpha nodes couldn't talk to LongFast). Kept until the owner
  decides to delete them.
- Local clone: `C:\Users\Gamer\Desktop\DRE\DRE-Comm\DRE-Comm-firmware`. Remotes: `origin` (DRE), `upstream` (Meshtastic).
- Broker side: `C:\Users\Gamer\Desktop\DRE\dre-mqtt` (Mosquitto config, not yet on GitHub or deployed).
- Plan: `ROADMAP.md`. Upstream sync steps: `dre/SYNC.md`.

## Stack (from the repo, 2026-11-17)
- C++17, Arduino framework, PlatformIO. ESP32-S3 boards use `framework-arduinoespressif32` and esptool v4.11.0.
- Build helper scripts in `bin/` (Python). Protobufs in the `protobufs` submodule (also `meshtestic` submodule).
- Version from `version.properties` (2.7.26).

## DRE changes (keep them small, see dre/SYNC.md)
- `branding/dre-comm/`: boot logo (`dre_comm_logo.h`, generator `make_logo.py`), `dre_comm_branding.h`,
  and `dre_comm_defaults.h` (MQTT server, user, root `msh/US/DRE`, TLS on, via `USERPREFS_*` hooks).
  `dre_comm_secrets.h` (git-ignored) holds the public broker password; CI writes it from secret
  `DRE_MQTT_PUBLIC_PASSWORD`. Without it the password is the placeholder `NOT-SET`.
- `variants/esp32s3/dre_comm_*`: one folder per board; each extends the stock env and includes the stock variant.h.
- `src/graphics/draw/UIRenderer.cpp`: the only upstream source edit (logo-only OEM screen on `OLED_TINY`).
- `.github/workflows/dre_comm_build.yml`: builds all DRE envs on `dre-stable`; tag `dre-v*` publishes a Release.

## Builds (env names)
`dre-comm-heltec-v3`, `dre-comm-heltec-v4` (untested on hardware), `dre-comm-heltec-wireless-tracker`,
`dre-comm-heltec-wireless-tracker-v2`, `dre-comm-heltec-wsl-v3`, `dre-comm-heltec-wireless-stick-v3`,
`dre-comm-t-deck`, `dre-comm-t-deck-tft`.

On this Windows PC PlatformIO is in a venv at `C:\Users\Gamer\.platformio\penv` (Python 3.12):
```powershell
cd C:\Users\Gamer\Desktop\DRE\DRE-Comm\DRE-Comm-firmware
C:\Users\Gamer\.platformio\penv\Scripts\pio.exe run -e dre-comm-heltec-v3
```
Output: `.pio\build\<env>\firmware-<env>-<version>.factory.bin` (full flash at 0x0) and `.bin` (update).
Known: on Windows, `dre-comm-heltec-v4` and `dre-comm-heltec-wsl-v3` fail with
`xtensa-esp32s3-elf-g++: error: CreateProcess: No such file or directory` (Windows command-line limit).
Build those in Linux/CI or in Docker (see the 2026-11-17 entry below).

## Important behaviour
- `USERPREFS_*` defaults apply only on a fresh install / factory reset. Ship new units with a full erase + factory.bin.
- ESP32 MQTT TLS does not verify the server certificate (`setInsecure()` in `src/mqtt/MQTT.cpp`).
- On a non-private broker, packets from other nodes are only uplinked if the sender has "OK to MQTT" on
  (firmware default off).

## Rules
- Ask before pushing, force-pushing, creating repos or deleting branches. Commit locally in small commits.
- Never commit secrets. Never base DRE-Comm on a Meshtastic alpha.

## Log
- 2026-11-17: Added `dre_comm_defaults.h` (DRE MQTT defaults), `dre-comm-heltec-v4` env, CI secret step,
  WSL V3 now gets the defaults, ROADMAP.md, dre/SYNC.md, this file. Branch `dre-mqtt-defaults` (local only,
  not pushed). Heltec V3 built OK on Windows.
