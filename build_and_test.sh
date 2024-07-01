#!/bin/bash

set -e

CC=gcc
CFLAGS="-Wall -Wextra -g"

# Build
$CC $CFLAGS read_until.c -o read_until

# Test
bash test_read_until.sh
