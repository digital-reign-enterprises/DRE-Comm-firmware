# Keeping DRE-Comm in sync with Meshtastic stable

DRE-Comm = Meshtastic **stable** release + a small stack of DRE commits. Never base DRE-Comm on an alpha.
(2.8 alpha nodes could not talk to the rest of the mesh on LongFast, which is why DRE moved back to 2.7.26.)

## How upstream labels releases

On https://github.com/meshtastic/firmware/releases the stable one is the release GitHub marks **Latest**
(Meshtastic titles it "Beta"). Releases marked **Pre-release** ("Alpha") are not for DRE.
Check from a terminal:

```sh
gh release list -R meshtastic/firmware --limit 10
```

## Where DRE's changes live (keep it this way)

| DRE change                                | Files                                                                  | Touches upstream code?                     |
| ----------------------------------------- | ---------------------------------------------------------------------- | ------------------------------------------ |
| Boot logo                                 | `branding/dre-comm/`                                                   | no                                         |
| Network defaults (MQTT server, root, TLS) | `branding/dre-comm/dre_comm_defaults.h`                                | no (uses Meshtastic's `USERPREFS_*` hooks) |
| Board builds                              | `variants/esp32s3/dre_comm_*/`                                         | no (each extends the stock env)            |
| CI                                        | `.github/workflows/dre_comm_build.yml`                                 | no (new file)                              |
| Docs                                      | `README.md` (top section), `ROADMAP.md`, `CLAUDE.md`, `dre/`           | README only (top section)                  |
| Tiny-OLED boot screen                     | `src/graphics/draw/UIRenderer.cpp` (8 lines, `#if defined(OLED_TINY)`) | **yes, the only one**                      |

Rule: if a change can be made with a new file, a `USERPREFS_*` define, or a variant, do that instead of
editing `src/`. If `src/` must change, keep it small, wrap it in `#if`, and consider sending it upstream.

## One-time setup on a new machine

```sh
git clone --recurse-submodules https://github.com/digital-reign-enterprises/DRE-Comm-firmware.git
cd DRE-Comm-firmware
git remote add upstream https://github.com/meshtastic/firmware.git
git fetch upstream --tags
```

## Moving to a new Meshtastic stable (rebase, recommended)

Example: moving from v2.7.26.54e0d8d to a newer stable tag. Replace `NEWTAG` with the real tag name,
for example `v2.7.27.abcdef0` (that one is made up).

1. Start clean and up to date:
   ```sh
   git switch dre-stable
   git pull
   git fetch upstream --tags
   ```
2. Keep a backup branch of where you are (local only):
   ```sh
   git branch backup/dre-stable-before-NEWTAG
   ```
3. Find the old base (the upstream tag DRE is on now):
   ```sh
   git describe --tags --abbrev=0 dre-stable
   ```
   Call that `OLDTAG` (today: `v2.7.26.54e0d8d`).
4. Replay DRE's commits onto the new tag:
   ```sh
   git rebase --onto NEWTAG OLDTAG dre-stable
   ```
   If git stops on a conflict: open the files it lists, keep both upstream's change and DRE's, then
   ```sh
   git add <the files>
   git rebase --continue
   ```
   To give up and go back: `git rebase --abort`.
5. Update submodules to what the new tag expects:
   ```sh
   git submodule update --init --recursive
   ```
6. Build every DRE board (see CLAUDE.md for the exact commands) and flash-test at least one Heltec V3.
7. Publishing: a rebase rewrites `dre-stable`, so pushing it needs a **force-push**. Ask first, then:
   ```sh
   git push --force-with-lease origin dre-stable
   ```
   (`--force-with-lease` refuses if someone else pushed in the meantime.)
8. Tag a DRE release so CI publishes binaries for the web flasher:
   ```sh
   git tag dre-v2.7.27-1
   git push origin dre-v2.7.27-1
   ```
   Tag format: `dre-v<meshtastic version>-<DRE build number>`.

## Alternative: merge (no force-push)

If force-pushing `dre-stable` is not allowed, merge instead. History gets messier but nothing is rewritten:

```sh
git switch dre-stable
git fetch upstream --tags
git merge NEWTAG
```

Resolve conflicts the same way, then build, test, push normally.

## Checks after every sync

- `git diff NEWTAG dre-stable --stat` lists only the files in the table above.
- `git diff NEWTAG dre-stable -- src/` shows only the `OLED_TINY` block in `UIRenderer.cpp`.
- Upstream still has the `USERPREFS_MQTT_*` hooks in `src/mesh/NodeDB.cpp`:
  `git grep -n USERPREFS_MQTT_ADDRESS NEWTAG -- src/mesh/NodeDB.cpp`
- Every DRE env still extends an upstream env that exists (`git grep -n "\[env:heltec-v3\]" NEWTAG`, etc.).
