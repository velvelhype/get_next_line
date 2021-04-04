#include "get_next_line.h"

int calloc_and_read(char *main_line, int fd, int global_count)
{
    char *cpy_line;

    cpy_line = strdup(main_line);
    // printf("cpy is %s\n",cpy_line);
    free(main_line);
    global_count += BUFFER_SIZE;
    main_line = (char*)calloc(global_count + 1, sizeof(char));
    main_line[global_count] = '\0';
    strcpy(main_line, cpy_line);
    free(cpy_line);
    if(BUFFER_SIZE > read(fd, main_line + global_count - BUFFER_SIZE, BUFFER_SIZE))
        return -1;
    return global_count;
}

int check(char *string, int global_count)
{
    int count = 0;
    while(count <= global_count)
    {
        if(*(string + count) == '\n')
            return 1;
        if(*(string + count) == EOF)
            return 0;
        count++;
    }

    return 2;
}

int get_next_line(int fd, char **line)
{
    int global_count = 0;
    static char *save;
    char *main_line;
    main_line = NULL;

    if(save != NULL)
    {
        main_line = strdup(save);
        global_count  = strlen(save);
        free(save);
        save = NULL;
    }
    else
    {
        main_line = (char*)calloc(global_count + BUFFER_SIZE + 1, sizeof(char));
        if(read(fd, main_line + global_count, BUFFER_SIZE) < BUFFER_SIZE)
        {
            *line = strdup(main_line);
            free(main_line);
            return 0;
        }
        global_count += BUFFER_SIZE;
    }

    while(check(main_line, global_count) == 2)
    {
        global_count = calloc_and_read(main_line, fd, global_count);
        if(global_count == -1)
        {
            //printf("its EOF");
            *line = strdup(main_line);
            free(main_line);
            return 0;  
        }
    };

    if((strchr(main_line, '\n') - main_line) < global_count - 1)
        {
            save = strdup(main_line + (strchr(main_line, '\n') - main_line + 1));
            *line = (char*)calloc(global_count + 1, sizeof(char));
            strncpy(*line, main_line, (strchr(main_line, '\n') - main_line));
        }
    else
        {
            *line = (char*)calloc(global_count + 1, sizeof(char));
            strncpy(*line, main_line, (strchr(main_line, '\n') - main_line));
        }
    free(main_line);
    return 1;
}