#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>


#include <stdio.h>

#define GNL_FOUND_LINEBREAK 1
#define GNL_FOUND_EOF 0
#define GNL_ERROR -1

int get_next_line(int fd, char **line);

#endif