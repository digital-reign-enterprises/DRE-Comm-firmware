# DRE-Comm roadmap

DRE-Comm is Digital Reign Enterprises' Meshtastic product line: DRE's own MQTT network, DRE-Comm firmware
(Meshtastic stable + DRE defaults and branding), preloaded radios in weather-tight 3D-printed cases, and later
DRE's own boards.

Started 2026-11-17. Nothing here is a legal conclusion. Items under "Open questions" must be confirmed with
Meshtastic, a lawyer, or a test lab, as noted.

Status key: [x] done, [~] started, [ ] not started.

---

## Phase 1: DRE-Comm MQTT network

Goal: every DRE-Comm board ships pointed at a working, secured DRE broker, and the public can join.

| # | Task | Depends on | Status |
|---|---|---|---|
| 1.1 | Rebase DRE-Comm onto Meshtastic 2.7.26 stable (off the 2.8 alpha) | | [x] |
| 1.2 | Broker config, ACL, Compose, scripts, local tests (`dre-mqtt` folder) | | [x] |
| 1.3 | DRE network defaults in firmware via `USERPREFS_*` hooks (`branding/dre-comm/dre_comm_defaults.h`) | | [x] |
| 1.4 | Decide hostname, topic root, DRE-Comm channel name/PSK, host (VPS or office VM) | | [ ] |
| 1.5 | Create GitHub repo `digital-reign-enterprises/dre-mqtt` and push | owner OK | [ ] |
| 1.6 | Provision server, deploy broker, firewall, DNS (grey cloud), TLS | 1.4, 1.5 | [ ] |
| 1.7 | Set GitHub secret `DRE_MQTT_PUBLIC_PASSWORD`; update firmware defaults with final values | 1.4, 1.6 | [ ] |
| 1.8 | Build all DRE boards in CI; tag `dre-v2.7.26-1` | 1.7 | [ ] |
| 1.9 | Hardware test: Heltec V3 on Wi-Fi uplinks to DRE broker; second node receives DRE-Comm channel downlink; phone-proxy node works | 1.6, 1.8 | [ ] |
| 1.10 | Add broker to DRE Monitor (ports, cert expiry, health) | 1.6 | [ ] |
| 1.11 | Public "join the DRE-Comm network" page on digitalreignenterprises.com (server, root, public login, rules) | 1.6 | [ ] |
| 1.12 | DRE web flasher (like flasher.meshtastic.org) reading DRE GitHub Releases | 1.8 | [ ] |
| 1.13 | Per-customer broker accounts (revocable), set over serial during flash-and-test | 1.6 | [ ] |
| 1.14 | Per-client message rate limiting (EMQX or a filter service) when public traffic grows | 1.6 | [ ] |

Done checkpoint for phase 1: a DRE-Comm Heltec V3 flashed from a CI release, factory fresh, connects to
the production broker over TLS with no manual MQTT settings; a second DRE node on another mesh receives its
DRE-Comm channel message through the broker; DRE Monitor shows the broker green; the join page is live.

## Phase 2: preloaded devices and cases

Goal: sell finished DRE-Comm radios (Heltec V3, V4, Wireless Tracker, Wireless Stick V3.1, LILYGO T-Deck)
in DRE's 3D-printed weather-tight cases, each one flashed and tested before it ships.

| # | Task | Depends on | Status |
|---|---|---|---|
| 2.1 | Hardware-test every DRE build on its real board (V4, Tracker, Stick V3.1, T-Deck, T-Deck TFT) | phase 1 builds | [ ] |
| 2.2 | Case design per board: antenna feed-through, USB-C access or sealed port, button access, screen window, battery bay, mounting | | [ ] |
| 2.3 | Weather-tightness: gasket/O-ring design, cable glands, vent membrane for pressure/condensation, filament choice for UV and heat, print settings for watertight walls | 2.2 | [ ] |
| 2.4 | Weather test procedure (e.g. spray/soak/temperature cycle) and pass criteria; decide whether to claim any IP rating (see open questions) | 2.3 | [ ] |
| 2.5 | Bill of materials per SKU: board, antenna, battery, gasket, glands, fasteners (real part numbers from suppliers; none chosen yet) | 2.2 | [ ] |
| 2.6 | Flash-and-test station: script that, per unit, full-erases and flashes the CI release, sets per-unit MQTT account, checks boot screens, GPS (Tracker), screen, button, battery reading, radio TX/RX against a reference node, MQTT login, and writes a test record (serial number, node id, firmware version, results) | 1.13, 2.1 | [ ] |
| 2.7 | Labelling and paperwork per unit: serial, any required regulatory labels (see FCC questions), quick-start card, GPL source offer | open questions | [ ] |
| 2.8 | Battery shipping rules for units shipped with Li-ion cells | | [ ] |
| 2.9 | Returns and RMA process; firmware update instructions for customers | 1.12 | [ ] |
| 2.10 | Store listing on digitalreignenterprises.com | 2.6, 2.7 | [ ] |

Done checkpoint for phase 2: 10 units of at least one SKU have passed the flash-and-test script and the
weather test procedure, each with a stored test record, and the regulatory and GPL questions for that SKU
are answered in writing.

## Phase 3: DRE's own boards and Meshtastic approval

Goal: DRE-designed LoRa boards that Meshtastic officially supports.

| # | Task | Depends on | Status |
|---|---|---|---|
| 3.1 | Requirements: radio module, MCU (ESP32-S3 or nRF52), power, GPS, screen, sensors, case fit | phase 2 lessons | [ ] |
| 3.2 | Choose a pre-certified LoRa module vs a discrete radio design (big effect on FCC work) | 3.1, open questions | [ ] |
| 3.3 | Schematic, PCB, prototypes, bring-up | 3.2 | [ ] |
| 3.4 | Upstream variant: new `variants/` folder and hardware model id, following Meshtastic's contribution rules | 3.3 | [ ] |
| 3.5 | Contact Meshtastic about the Backer/Partner programmes (the route to "Officially Supported") | 3.3 | [ ] |
| 3.6 | Regulatory testing and certification for the board | 3.3 | [ ] |
| 3.7 | Production run, using the phase 2 flash-and-test station | 3.6 | [ ] |

Done checkpoint for phase 3: the DRE board's variant is merged in Meshtastic's firmware repo, the board is
listed by Meshtastic at the support level DRE agreed with them, and the board has the radio authorisation
needed for each country DRE sells into.

---

## Open questions (confirm, don't assume)

### GPL (ask a lawyer)
- DRE-Comm firmware is a fork of GPLv3 code. When DRE sells a device with it preinstalled, what exactly
  must DRE provide (source for the exact build shipped, build scripts, a written offer, how long to keep it)?
- Is the public GitHub repo plus a tag per shipped build enough, or is a written offer in the box also needed?
- Do the DRE logo bitmap and DRE config fall under the GPL in the binary, and can DRE keep any brand assets
  under separate terms?
- Does a per-unit MQTT credential written at flash time (not in the source) raise any "installation
  information" issue under GPLv3 for consumer devices?
- The broker password is compiled in from a secret. Is that acceptable under GPLv3, given users can rebuild
  with their own?

### Meshtastic trademark and branding (ask Meshtastic: trademark@meshtastic.org, and a lawyer)
What their policy page says (meshtastic.org/docs/legal/licensing-and-trademark/, read 2026-11-17) and what
still needs confirming:
- Product names may not contain Meshtastic marks. Confirm "DRE-Comm" product names and listings are fine,
  and how DRE may say compatibility (e.g. "runs Meshtastic®-based firmware").
- Logos on hardware or cases need written permission. Do we want a grant, or only the "M-Powered" mark
  (which the page says needs no grant)?
- The boot sequence shows the stock Meshtastic splash and then DRE-Comm. Is showing their logo in
  DRE-sold firmware OK, or does it need a grant?
- The trademark grant is described as two years but also "revocable at any time". Which is it?
- Is the README disclaimer ("not affiliated with or endorsed by Meshtastic LLC") the wording they want?

### Running a public broker (ask Meshtastic)
- Any rules or expectations for third-party public brokers? Should DRE ever bridge to mqtt.meshtastic.org?
- Should DRE devices ship with "OK to MQTT" on? (Privacy decision for DRE too; needs a small firmware change.)

### Meshtastic hardware approval (ask Meshtastic)
- What are the Backer and Partner programmes: cost, criteria, contact, timeline? (Named in their
  2025-08-02 blog post; not described.)
- What is needed for a DRE board to be "Officially Supported" vs "Community Supported" and to appear in
  their web flasher?
- Is a hardware model id assigned by them, and when in the process?

### FCC and radio rules (ask a regulatory lawyer or an accredited test lab)
- DRE sells finished devices built from Heltec/LILYGO boards. Does each board's existing FCC authorisation
  (if it has one) cover DRE's product, or does DRE need its own? Check each board's FCC ID, and whether a
  DRE case and antenna change that.
- Antenna rules: may DRE ship a different antenna than the one the module was certified with?
- Labelling: what must be on the case/packaging/manual (FCC ID, Part 15 statements)?
- Unintentional radiator rules for the rest of the device (ESP32, screen, charger): is Part 15B testing
  (verification or SDoC) needed for the finished product?
- Region presets: is shipping US units with the US region preset fine, and is leaving it unset (owner picks)
  a problem for sales outside the US?
- Other markets (Canada ISED, EU RED/CE, UK UKCA) if DRE sells abroad.
- For DRE's own board: modular approval for a pre-certified module vs full certification, costs and timelines.
- Battery transport rules and any product-safety marks for Li-ion devices.
- Can DRE claim an IP rating for the cases without formal IP testing?
