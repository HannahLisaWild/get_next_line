# get_next_line

A project for reading lines from a file descriptor, one at a time, in C.

## Subject Goals

- Handle buffered reading with a static variable
- Return one line per call
- Manage memory cleanly
- Handle edge cases (empty lines, EOF, etc.)

## Usage

Compile with:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42
