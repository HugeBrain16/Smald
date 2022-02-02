# Smald

A library I made for learning C++.
This one started closed source because mostly just implementation of [cmdtools](https://github.com/HugeBrain16/cmdtools) and [iniparser](https://github.com/HugeBrain16/iniparser) in C++.

Old binary releases can be found here: [Google Drive](https://drive.google.com/drive/folders/1pMPsnOeZvkKf_2VZzGCMxlKJZ-BVWbXs?usp=sharing)

# Building

You need [**cmake**](https://cmake.org/) installed to build this library.
To build the library type:

```sh
cmake -B build && cd build
```

And build with whatever the generator you're using,
for example with [**GNU Make**](https://www.gnu.org/software/make/)

```sh
# in build directory
make && make test
```

or just type `cmake --build .` in build directory.

The static library is usually located in `<build-directory>/src/libsmald.a` or `<build-directory>/src/smald.lib` for [**MSVC**](https://en.wikipedia.org/wiki/Microsoft_Visual_C%2B%2B) build.
(for Visual Studio generator the static library is located in `<build-directory>/src/{Debug|Release}/smald.lib`)

