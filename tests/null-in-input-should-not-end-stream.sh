#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")/.."

echo -en "a\0bc" |
./read_until "b" |
diff -a - <(echo -en "a\0b") \
|| exit 1
