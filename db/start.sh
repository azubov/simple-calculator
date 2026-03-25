#!/bin/bash

# Exit immediately if any command fails
set -e

# Switch to the directory where this script is located
cd "$(dirname "$0")"

echo "=== Checking Docker installation ==="

if ! command -v docker >/dev/null 2>&1; then
    echo "Docker not found. Installing..."
    sudo apt update
    sudo apt install -y ca-certificates curl gnupg lsb-release

    # Add Docker’s official GPG key
    sudo install -m 0755 -d /etc/apt/keyrings
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg

    # Add Docker repository
    echo \
      "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] \
      https://download.docker.com/linux/ubuntu \
      $(lsb_release -cs) stable" | \
      sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

    sudo apt update

    # Install Docker Engine and Compose plugin
    sudo apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

    echo "Docker installed."
else
    echo "Docker is already installed."
fi

echo "=== Checking Docker Compose ==="

if ! docker compose version >/dev/null 2>&1; then
    echo "Docker Compose not found. Installing..."
    sudo apt install -y docker-compose-plugin
else
    echo "Docker Compose is already installed."
fi

echo "=== Starting docker compose up -d ==="
docker compose up -d

echo "Done."
