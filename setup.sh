#!/bin/bash

set -e

# Define variables
PROJECT_NAME="hikio"
INSTALL_DIR="/usr/local/bin"

# Colors
GREEN="\033[1;32m"
RED="\033[1;31m"
NC="\033[0m"

echo -e "${GREEN}🔧 Setting up $PROJECT_NAME shell...${NC}"

# Optional dev mode
if [[ "$1" == "--dev" ]]; then
    echo -e "${GREEN}🧠 Developer mode enabled: installing 'bear' if needed...${NC}"
    if ! command -v bear &> /dev/null; then
        echo -e "${RED}❌ 'bear' is not installed. Please install it and rerun the script.${NC}"
        exit 1
    fi
    bear -- make clean && make
else
    make clean && make
fi

# Move the binary
echo -e "${GREEN}📦 Installing $PROJECT_NAME to $INSTALL_DIR...${NC}"
sudo cp "$PROJECT_NAME" "$INSTALL_DIR"

echo -e "${GREEN}✅ $PROJECT_NAME is ready to use. Run it with: ${NC}${PROJECT_NAME}"
