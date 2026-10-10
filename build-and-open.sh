#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$DIR"

if [ "$(id -u)" -eq 0 ]; then
    echo "No corras esto como root: la GUI necesita tu sesion grafica." >&2
    echo "Usa tu usuario normal, sin sudo: ./build-and-open.sh" >&2
    exit 1
fi

./build.sh

RULE=/etc/udev/rules.d/99-aquila-air.rules
if ! cmp -s "$DIR/99-aquila-air.rules" "$RULE"; then
    echo "Instalando/actualizando regla udev del mouse (requiere sudo, solo esta vez)..."
    sudo cp "$DIR/99-aquila-air.rules" "$RULE"
    sudo udevadm control --reload-rules
    sudo udevadm trigger --subsystem-match=hidraw
fi

exec "$DIR/build/aquila-air-driver"
