#!/usr/bin/env bash
set -e

# Clean previous build artifacts
make clean

# Remove the generated headers so make regenerates them from .def.h
rm -f config.h patches.h

# Compile as a NORMAL user
echo "Compiling..."
make

# Install as ROOT
echo "Installing..."
sudo make install

# Notify
echo "Build complete. Press Super+Shift+R to reload."
