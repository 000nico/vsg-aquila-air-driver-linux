#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$DIR"

cmake -B build
cmake --build build

echo "Build listo: $DIR/build/aquila-air-driver"
