#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "include/gnl.h"


int main(void) {

    int fd = open("src/gnl.c", O_RDONLY);

    char *line = get_next_line(fd);
    while (line != NULL) {
        /*printf("%s", line);*/
        free(line);
        line = get_next_line(fd);
    }
}
