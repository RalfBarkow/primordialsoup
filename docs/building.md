# Building

Primordial Soup has support for 32-bit and 64-bit architectures and has platform support for Android, [Emscripten](https://emscripten.org/), [Fuchsia](https://fuchsia.dev/), Linux, macOS and Windows.

## Dependencies

Building Primordial Soup requires a C++ compiler and [SCons](http://scons.org/).

On Debian/Ubuntu:

```
sudo apt-get install g++-multilib scons
```

On macOS, install XCode and SCons.

On Windows, install Visual Studio and SCons.

To target Android, download the [Android NDK](https://developer.android.com/ndk/downloads/index.html).

To target Fuchsia, [create a checkout](https://fuchsia.dev/fuchsia-src/get-started/get_fuchsia_source).

## Building

The VM and snapshots are built with

```
./build
```

To target Android, build with

```
./build ndk=/path/to/android-ndk-r19c
```

To target Fuchsia, clone this repository to `third_party/primordialsoup` in a Fuchsia checkout, and include `third_party/primordialsoup:packages` in the list of packages. E.g.,

```
git clone https://github.com/rmacnak/primordialsoup.git third_party/primordialsoup
fx set core.x64 --release --with-base bundles:tools,third_party/primordialsoup:packages
fx build
```

To target WebAssembly, build with

```
source /path/to/emsdk/emsdk_env.sh
./build os=emscripten arch=wasm
```

## Testing

After building, the test suite and some benchmarks can be run with

```
./test
```

On Fuchsia,

```
run fuchsia-pkg://fuchsia.com/hello-app#meta/hello-app.cmx
run fuchsia-pkg://fuchsia.com/test-runner#meta/test-runner.cmx
run fuchsia-pkg://fuchsia.com/benchmark-runner#meta/benchmark-runner.cmx
```
