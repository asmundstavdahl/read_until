#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NULL_CHAR (0xFF + 1)

void shift_buffer_left(short *buf, size_t buffer_size);

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
    if (strlen(argv[1]) == 0)
    {
        return 0;
    }

    unsigned char *sequence = (unsigned char *)argv[1];
    size_t sequence_len = strlen((char *)sequence);
    short *buf = (short *)calloc(sequence_len + 1, sizeof(short));

    size_t buf_pos = 0;
    while (buf_pos < sequence_len)
    {
        if (buf[buf_pos] == '\0')
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

            buf[buf_pos] = next_char_element;
            putc((unsigned char)next_char, stdout);
        }

        if (buf[buf_pos] == sequence[buf_pos])
        {
            buf_pos++;
        }
        else
        {
            shift_buffer_left(buf, sequence_len + 1);
            buf_pos = 0;
        }
    }

    return 0;
}

/**
 * Shifts the elements of the buffer to the left by one position.
 *
 * @param buf Pointer to the buffer.
 * @param buf_len The number of elements in the buffer.
 */
void shift_buffer_left(short *buf, size_t buf_len)
{
    for (size_t i = 0; i < buf_len - 1; i++)
    {
        buf[i] = buf[i + 1];
    }
}
