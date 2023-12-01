#include <stdio.h>
#include <stdlib.h>
char * get_file_input(const char filename[]) {
    FILE * fileptr = fopen(filename, "r");
    if (!fileptr) {
        return NULL;
    }
    fseek(fileptr, 0, SEEK_END);
    size_t filelen = ftell(fileptr);
    fseek(fileptr, 0, SEEK_SET);

    char * content = malloc(filelen * sizeof(char));
    if (!content) {
        return NULL;
    }
    fread(content, 1, filelen, fileptr);
    fclose(fileptr);
    return content;
}
