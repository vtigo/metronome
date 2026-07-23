# metronome

A small metronome built with [raylib](https://www.raylib.com/).

![metronome running at 120 BPM](docs/screenshot.png)

## Controls

| Key | Action |
| --- | --- |
| ↑ / ↓ | ±1 BPM |
| → / ← | ±10 BPM |
| Esc | quit |

BPM range is 30–300.

## Build

Prerequisites: **CMake 3.16+**, **git**, and a C compiler.

- **Windows** — [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) (or MSYS2 mingw-w64)
- **macOS** — `xcode-select --install`
- **Linux** — `sudo apt install build-essential libasound2-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev`

```sh
git clone https://github.com/vtigo/metronome
cd metronome
cmake -B build
cmake --build build
```

Then run it:

```sh
./build/metronome          # Windows: build\metronome.exe
```

The first `cmake -B build` downloads and compiles raylib (~1–2 minutes). Later builds are fast.

## License

MIT — see [LICENSE](LICENSE).
