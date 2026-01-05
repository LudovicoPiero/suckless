#!/usr/bin/env bash
set -e

# Clean previous build artifacts
make clean

# Remove the generated headers so make regenerates them from .def.h
rm -f config.h

# Compile as a NORMAL user
echo "Compiling..."
make

# Install as ROOT
echo "Installing..."
sudo make install

# Notify
notify-send "DWM Build" "Build Complete!"
