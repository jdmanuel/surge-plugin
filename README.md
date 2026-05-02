# Surge JUCE Plugin

If you are using a Mac (ARM or or Intel), try downloading the built/binary plugin from the releases page. You can use your DAWs plugin installer or copy it to your plugin directory. It's very likely -- especially if you do the latter -- that when your DAW tries to load the plugin, it will be blocked by Mac's quarantine process. This is because I haven't signed it as an official Apple Developer (will be doing that soon). You can get usually get around this by pulling it out of quarantine with:

xattr -dr com.apple.quarantine ~/Library/Audio/Plug-Ins/VST3/Surge.vst3
xattr -dr com.apple.quarantine ~/Library/Audio/Plug-Ins/Components/Surge.component

You'll need to close and reopen your DAW. You might also need to clear the AU cache if using Logic:

killall -9 AudioComponentRegistrar
rm -f ~/Library/Caches/AudioUnitCache/com.apple.audiounits.cache
rm -f ~/Library/Caches/AudioUnitCache/com.apple.audiounits.sandboxed.cache

You can also just build this yourself. That will avoid the signing issue since binaries built locally don't need to be signed.

This repository contains the JUCE wrapper, custom editor, and committed RNBO C++ export needed to build the `Surge` plugin.

You do not need Max or RNBO just to build the plugin from this repository.

## Repository Layout

- `src/` : JUCE plugin code and custom editor UI
- `export/` : committed RNBO export used by the build
- `thirdparty/juce/` : JUCE submodule
- `build/` : local build output, ignored by git

The `export/` directory is intentionally part of the source tree so other people can build the plugin without needing Max.

## Prerequisites

### macOS

Install:

- `git`
- `CMake` 3.22 or newer
- Xcode Command Line Tools

Install the Xcode tools with:

```sh
xcode-select --install
```

If you use Homebrew, you can install CMake with:

```sh
brew install cmake
```

### Windows

Install:

- `git`
- `CMake` 3.22 or newer
- Visual Studio 2022 with the Desktop C++ workload

## Build From Source

### 1. Clone the repository

Clone with submodules so JUCE is included:

```sh
git clone --recurse-submodules https://github.com/jdmanuel/surge-plugin
cd surge-juce
```

If you already cloned without submodules:

```sh
git submodule update --init --recursive
```

### 2. Configure the build

#### macOS

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

To build a universal macOS binary for both Apple Silicon and Intel:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64"
```

If you prefer Ninja:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

#### Windows

Run from PowerShell or a Developer Command Prompt:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
```

Or with Ninja:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

### 3. Build the plugin

#### macOS

Build both plugin formats:

```sh
cmake --build build --config Release --target RNBOAudioPlugin_AU RNBOAudioPlugin_VST3
```

#### Windows

Build the VST3 target:

```powershell
cmake --build build --config Release --target RNBOAudioPlugin_VST3
```

### 4. Find the build products

After a successful build, the plugins will be in:

- AU:
  `build/RNBOAudioPlugin_artefacts/Release/AU/Surge.component`
- VST3:
  `build/RNBOAudioPlugin_artefacts/Release/VST3/Surge.vst3`

Depending on generator and platform, the exact folder names under `build/` may vary slightly, but those are the standard output locations for this project.

### 5. Install the plugin manually

#### macOS

Copy the built bundles to:

- AU:
  `~/Library/Audio/Plug-Ins/Components/`
- VST3:
  `~/Library/Audio/Plug-Ins/VST3/`

#### Windows

Copy the built VST3 bundle to:

- `%COMMONPROGRAMFILES%\VST3\`

### Option A: environment variables

#### macOS / Linux

```sh
export RNBO_EXPORT_DIR=/absolute/path/to/export
export RNBO_CPP_DIR="$RNBO_EXPORT_DIR/rnbo"
export RNBO_CLASS_FILE_NAME=Surge.rnbopat.cpp
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

#### Windows PowerShell

```powershell
$env:RNBO_EXPORT_DIR = "C:/absolute/path/to/export"
$env:RNBO_CPP_DIR = "$env:RNBO_EXPORT_DIR/rnbo"
$env:RNBO_CLASS_FILE_NAME = "Surge.rnbopat.cpp"
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
```

### Option B: CMake `-D` variables

```sh
cmake -S . -B build \
  -DRNBO_EXPORT_DIR=/absolute/path/to/export \
  -DRNBO_CPP_DIR=/absolute/path/to/export/rnbo \
  -DRNBO_CLASS_FILE_NAME=Surge.rnbopat.cpp
```

`RNBO_CPP_DIR` defaults to `${RNBO_EXPORT_DIR}/rnbo`, so in many cases you only need to override `RNBO_EXPORT_DIR`.

## Signing Notes

### macOS local builds

If your DAW refuses to load the plugin, you can usually satisfy it with an ad-hoc signing:

```sh
codesign --force --deep -s - build/RNBOAudioPlugin_artefacts/Release/VST3/Surge.vst3
codesign --force --deep -s - build/RNBOAudioPlugin_artefacts/Release/AU/Surge.component
```

You can inspect the signature with:

```sh
codesign -dv --verbose=2 build/RNBOAudioPlugin_artefacts/Release/VST3/Surge.vst3
```

### Windows

When you build a plugin locally for your own machine, Windows code signing is usually not required.

## Troubleshooting

- If CMake says it cannot find `RNBO.h` or `Surge.rnbopat.cpp`, make sure the `export/` directory exists and contains the committed RNBO export.
- If you cloned without submodules, run `git submodule update --init --recursive`.
- If you change RNBO export paths or filenames after the first CMake configure, delete `build/` or at least `build/CMakeCache.txt` before reconfiguring.
- If macOS reports signature problems with the VST3, try the ad-hoc `codesign` command shown above.
