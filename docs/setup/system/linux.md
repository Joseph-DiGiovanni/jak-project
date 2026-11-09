# Linux Environment Setup

- [Linux Environment Setup](#linux-environment-setup)
  - [Packages](#packages)
    - [Ubuntu (20.04)](#ubuntu-2004)
  - [Arch](#arch)
  - [Fedora](#fedora)
  - [Compiling and Building](#compiling-and-building)
  - [ARM64 (aarch64)](#arm64-aarch64)


## Packages

### Ubuntu (20.04)

```sh
sudo apt install gcc make cmake ninja-build build-essential g++ nasm clang-format libxrandr-dev libxinerama-dev libxcursor-dev libpulse-dev libxi-dev python libgl1-mesa-dev libssl-dev
sudo sh -c "$(curl --location https://taskfile.dev/install.sh)" -- -d -b /usr/local/bin
```

## Arch

```sh
sudo pacman -S cmake libpulse base-devel nasm python libx11 libxrandr libxinerama libxcursor libxi
yay -S go-task
```

> Note: Any later documentation that shows a `task ...` command, would instead be a `go-task ...` command.

## Fedora

```sh
sudo dnf install cmake python lld clang nasm libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel pulseaudio-libs-devel mesa-libGL-devel
sudo sh -c "$(curl --location https://taskfile.dev/install.sh)" -- -d -b /usr/local/bin
```

## Compiling and Building

Compile:

```sh
cmake -B build && cmake --build build -j 8
```

Run tests:

```sh
./test.sh
```

Note: we have found that `clang` and `lld` are significantly faster to compile and link than `gcc`, generate faster code, and have better warning messages. To install these:

```sh
sudo apt install lld clang
```

and run `cmake` (in a fresh build directory) with:

```sh
cmake -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld" -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
```

## ARM64 (aarch64)

OpenGOAL builds natively on ARM64 Linux with the same packages and presets. `nasm` is only used by x86-64 builds and can be skipped.

```sh
cmake -B build --preset=Release-linux-clang
cmake --build build --parallel $(nproc)
./test.sh
```

`goalc` and the `extractor` generate code for the CPU they were built for, so an ARM64 build compiles the game to ARM64 code. Both accept `--instruction-set x86` or `--instruction-set arm64` to override this.

ARM64 builds require a CPU with the ARMv8 CRC32 instructions, which almost every ARM64 core implements. The renderer requires OpenGL 4.3, which some ARM64 GPU drivers (for example on most Raspberry Pi and Mali devices) do not provide.

The `goalc` debugger cannot read or write registers or disassemble code on ARM64 yet.
