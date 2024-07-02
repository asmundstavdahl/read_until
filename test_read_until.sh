#!/bin/bash

set -e

echo -n "Test 1: Short Sequence "
./read_until "abc" <<<"abcdef" | diff -a - <(echo -n "abc") && echo "PASS" || echo "FAIL"

echo -n "Test 2: Multiline Input "
./read_until "def" <<<"abcdef\n" | diff -a - <(echo -n "abcdef") && echo "PASS" || echo "FAIL"

echo -n "Test 3: Large Input With Search Sequence In Middle "
./read_until "xyz" <<<"abcdefxyz123456" | diff -a - <(echo -n "abcdefxyz") && echo "PASS" || echo "FAIL"

echo -n "Test 4: Newline Sequence "
./read_until $'\n' <<<$'line1\nline2\n' | diff -a - <(echo -en "line1\n") && echo "PASS" || echo "FAIL"

echo -n "Test 5: Null Termination "
echo "SKIP (main function's arg strings cannot contain NULL)"
#./read_until $'\0' <<<$'abc\0def' | diff -a - <(echo -en "abc\0") && echo "PASS" || echo "FAIL"

echo -n "Test 6: Whitespace Sequence "
./read_until "  " <<<"a b c  d" | diff -a - <(echo -n "a b c  ") && echo "PASS" || echo "FAIL"

echo -n "Test 7: Special Character Sequence "
./read_until "🌟" <<<$'hello🌟world' | diff -a - <(echo -n "hello🌟") && echo "PASS" || echo "FAIL"

echo -n "Test 8: Random Data (fails randomly when a NULL byte is read) "
test_8() {
    local f_in=$(mktemp)
    local f_out=$(mktemp)
    (
        dd if=/dev/urandom bs=100000 count=1 2>/dev/null
        echo "11111111"
    ) >"$f_in"

    ./read_until '11111111' <"$f_in" >"$f_out"
    output_len=$(wc -c <"$f_out")
    if [ "$output_len" -eq 100008 ]; then
        return 0
    else
        echo "Output length is $output_len, expected 100008" >&2
        which byte-insight >/dev/null && byte-insight <"$f_out" | tail -n16
        return 1
    fi
}
test_8 && echo "PASS" || echo "FAIL"

echo -n "Test 9: Empty Sequence "
./read_until "" <<<"empty" | diff -a - <(echo -n "") && echo "PASS" || echo "FAIL"

echo -n "Test 10: Long Sequence "
./read_until "long sequence" <<<"this is a long sequence test" | diff -a - <(echo -n "this is a long sequence") && echo "PASS" || echo "FAIL"
