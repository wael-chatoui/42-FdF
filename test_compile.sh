#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}=== FdF Compilation Test ===${NC}"
echo ""

# Check if minilibx is compiled
if [ ! -f "minilibx-linux/libmlx.a" ]; then
    echo -e "${RED}Error: minilibx not compiled yet!${NC}"
    echo "Please wait for 'make' to complete in minilibx-linux directory"
    exit 1
fi

echo -e "${GREEN}✓ MinilibX library found${NC}"

# Check if libft is compiled
if [ ! -f "include/42-libft/libft.a" ]; then
    echo -e "${YELLOW}Compiling libft...${NC}"
    make -C include/42-libft
fi

echo -e "${GREEN}✓ Libft library ready${NC}"

# Clean and compile the project
echo -e "${YELLOW}Compiling FdF project...${NC}"
make re

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Compilation successful!${NC}"
    echo ""
    echo -e "${YELLOW}Testing with basic map:${NC}"
    if [ -f "fdf" ]; then
        echo "./fdf test_maps/basictest.fdf"
        echo ""
        echo -e "${GREEN}You can now run: ./fdf test_maps/basictest.fdf${NC}"
    fi
else
    echo -e "${RED}✗ Compilation failed!${NC}"
    echo "Please check the error messages above."
    exit 1
fi
