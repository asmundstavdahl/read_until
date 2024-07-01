#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void shift_buffer_left(char *buf, size_t buffer_size);

/**
 * Reads input from stdin until a given sequence is found and prints the input up and including the sequence.
 *
 * @return 0 if the program succeeds, 1 if the sequence is not found or 2 if no sequence is provided.
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <sequence>\n", argv[0]);
        return 2;
    }

    char *sequence = argv[1];
    size_t sequence_len = strlen(sequence);
    char *buf = calloc(sequence_len + 1, sizeof(char));

    size_t buf_pos = 0;
    while (buf_pos < sequence_len)
    {
        if (buf[buf_pos] == '\0')
        {
            char next_char = getc(stdin);
            if (next_char == EOF)
            {
                return 1;
            }
            buf[buf_pos] = next_char;
            putc(next_char, stdout);
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
 * @param buffer_size The size of the buffer.
 *
 * @return None.
 */
void shift_buffer_left(char *buf, size_t buf_len)
{
    for (size_t i = 0; i < buf_len - 1; i++)
    {
        buf[i] = buf[i + 1];
    }
}