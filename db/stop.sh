#!/bin/bash

# Exit immediately if any command fails
set -e

# Switch to the directory where this script is located
cd "$(dirname "$0")"

echo "=== Stopping containers ==="
docker compose down

echo "Done."
