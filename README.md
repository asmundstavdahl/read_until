# read_until utility propram
This little program reads from STDIN and writes to STDOUT until the given sequence of 1 or more bytes is read.

All bytes read from STDIN will be output, including the given sequence of 1 or more bytes.

# Usage
```shell
echo "abcabcabc" | read_until "cabc"
# outputs "abcabc" (no trailing newline)

echo -en "test 1\ntest 2\n" | read_until "$(echo -en "\n")"
# outputs "test 1\n"
```
