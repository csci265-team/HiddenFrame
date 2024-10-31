# HiddenFrame Backend

The HiddenFrame backend has a API server that gets exposed to localhost on port `8080` ([`http://localhost:8080`](http://localhost:8080))
This API server is build using [crow](https://crowcpp.org/master/) which relies on the [asio](https://think-async.com/Asio/) library

## Getting started

Before we build the backend executable you need to make sure [asio](https://think-async.com/Asio/) is installed and the make file is pointing to the right paths

### MacOS

- Install [asio](https://think-async.com/Asio/) using [homebrew](https://brew.sh/): `brew install asio`
- Ensure `$IncludePaths` in makefile includes both this project's `include/` subdirectory and homebrew's include directory `/opt/homebrew/include`
- Now the project can be built by running `make macos`
- The executable can be found at `build/HiddenFrame`

### Linux

- Install [asio](https://think-async.com/Asio/) using your preferred package manager
  - On debian based systems you can run: `apt install libasio-dev`
- Ensure `$IncludePaths` in makefile includes both this project's `include/` subdirectory and homebrew's include directory `/usr/local/include` or the correct include path
- Now the project can be built by running `make linux`
- The executable can be found at `build/HiddenFrame`

### Windows

- Install [asio](https://think-async.com/Asio/) 
- Ensure `$IncludePaths` in makefile includes both this project's `include/` subdirectory  directory `FIND CORRECT PATH` or the correct include path
- Now the project can be built by running `make windows`
- The executable can be found at `build/HiddenFrame.exe`
