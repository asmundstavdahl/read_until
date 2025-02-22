#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NULL_CHAR (0xFF + 1)

/**
 * Reads input from stdin until a given sequence is found and prints the input up and including the sequence.
 *
 * @return 0 if the program succeeds, 1 if the sequence is not found or 2 if no sequence is provided.
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <sequence>\nIf sequence is empty, exits immediately without reading or writing anything.\n", argv[0]);
        return 2;
    }

    size_t seq_len = strlen(argv[1]);

    if (strlen(argv[1]) == 0)
    {
        return 0;
    }

    size_t buf_len = 512;
    short stack_buf[512] = {0};
    short *buf = stack_buf;
    if (seq_len * sizeof(short) > sizeof(stack_buf) * sizeof(short))
    {
        // Sequence is too long. Using heap buffer.
        buf = (short *)calloc(seq_len, sizeof(short));
        buf_len = seq_len;
    }

    unsigned char *seq = (unsigned char *)argv[1];

    size_t offset = 0;
    size_t pos = 0;
    size_t ready_chars = 0;
#define IDX ((pos + offset) % buf_len)
    while (pos < seq_len)
    {
        if (ready_chars == 0)
        {
            int next_char = getc(stdin);
            short next_char_element = (short)next_char;
            if (next_char == EOF)
            {
                return 1;
            }
            if (next_char == '\0')
            {
                next_char_element = NULL_CHAR;
            }

            buf[IDX] = next_char_element;
            putc(next_char, stdout);
            ready_chars++;
        }

        if (buf[IDX] == seq[pos])
        {
            pos++;
            ready_chars--;
        }
        else
        {
            ready_chars += pos - 1;
            pos = 0;
            offset++;
        }
    }

    return 0;
}
