#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")/.."

time {
    head -c10M /dev/urandom
    echo "11111111"
} | ./read_until '11111111' >/dev/null || exit 1
