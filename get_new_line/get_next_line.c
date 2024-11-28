#include "get_next_line.h"

static char *extract_line(char **buffer) {
    size_t i = 0;
    while ((*buffer)[i] && (*buffer)[i] != '\n')
        i++;
    
    char *line = gnl_strdup(*buffer, i + ((*buffer)[i] == '\n' ? 1 : 0));
    char *temp = gnl_strdup((*buffer) + i + ((*buffer)[i] == '\n' ? 1 : 0), gnl_strlen(*buffer) - i);
    
    free(*buffer);
    *buffer = temp;

    return line;
}

char *get_next_line(int fd) {
    static char *buffer;
    char *line;
    char temp[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (!gnl_has_newline(buffer) && (bytes_read = read(fd, temp, BUFFER_SIZE)) > 0) {
        temp[bytes_read] = '\0';
        buffer = gnl_strjoin(buffer, temp);
    }

    if (bytes_read == -1 || (bytes_read == 0 && (!buffer || !buffer[0]))) {
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    line = extract_line(&buffer);
    return line;
}
