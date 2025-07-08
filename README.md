# get_next_line

A project from the 42 curriculum that implements a function to read a file descriptor line by line, returning one line per call, including the newline character if present.

---

## 📌 Subject Summary

- Create a function `get_next_line` that reads from a file descriptor and returns the next line.
- Handle reading until a newline `\n` or end-of-file (EOF).
- Manage memory efficiently and handle multiple file descriptors.
- The function returns `NULL` when there is nothing more to read or an error occurs.

🧠 Learning Outcomes

    Managing file descriptors and buffered input in C.

    Handling dynamic memory allocation and freeing.

    Implementing efficient line-by-line reading.

    Understanding static variables for persistent state.

    Working with system calls such as read.

---

## 📦 How to Compile

Compile using the provided Makefile:

```bash
make
🚀 Usage

Include libftgnl.a in your project and use get_next_line like this:

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
