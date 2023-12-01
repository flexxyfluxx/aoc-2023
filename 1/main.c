#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

void part_1() {
    char * input = get_file_input("input.txt");
    if (!input) {
        perror("Could not read input.txt");
        exit(1);
    }

    char curr_left_digit, curr_right_digit;
    bool left_digit_found = false;
    int callibration_sum = 0;
    int curr_num;
    
    char curr_char;
    size_t c;
    for (c = 0; (curr_char = input[c]); c++) {
        if (curr_char == '\n') {
            curr_num = curr_left_digit * 10 + curr_right_digit;
            callibration_sum += curr_num;
            left_digit_found = false;
            curr_left_digit = curr_right_digit = 0;
            printf(": %d\n", curr_num);
        } else {
            if ('1' <= curr_char && curr_char <= '9') {
                if (left_digit_found) {
                    curr_right_digit = curr_char - '0';
                } else {
                    curr_left_digit = curr_right_digit = curr_char - '0';
                    left_digit_found = true;
                }
            }
            putc(curr_char, stdout);
        }
    }

    printf("Final sum: %d\n", callibration_sum);
    printf("%zu\n", c);

    free(input);
}

#define NULLSWP(val, tmp) { \
    tmp = val;              \
    val = 0;                \
}
char try_to_read_digit(char * cursor) {
    if ('1' <= *cursor && *cursor <= '9') return *cursor - '0';

    for (int c = 0; c < 3; c++) {
        if (cursor[c] == '\0' || cursor[c] == '\n') return -1;
    }
    char tmp = 0, result = 0;
    NULLSWP(cursor[3], tmp)
    // try to cmp 3 letter num words
    if (!strcmp(cursor, "one")) result = 1;
    if (!strcmp(cursor, "two")) result = 2;
    if (!strcmp(cursor, "six")) result = 6;
    cursor[3] = tmp;
    if (result) return result;

    if (cursor[3] == '\0' || cursor[3] == '\n') return -1;
    NULLSWP(cursor[4], tmp)
    // try to cmp 4 letter num words
    if (!strcmp(cursor, "four")) result = 4;
    if (!strcmp(cursor, "five")) result = 5;
    if (!strcmp(cursor, "nine")) result = 9;
    cursor[4] = tmp;
    if (result) return result;

    if (cursor[4] == '\0' || cursor[4] == '\n') return -1;
    NULLSWP(cursor[5], tmp)
    // try to cmp 4 letter num words
    if (!strcmp(cursor, "three")) result = 3;
    if (!strcmp(cursor, "seven")) result = 7;
    if (!strcmp(cursor, "eight")) result = 8;
    cursor[5] = tmp;
    if (result) return result;
    return -1;
}

void part_2() {
    char * input = get_file_input("input.txt");
    char * cursor = input;

    char left_digit, right_digit;
    int calibration_sum = 0;
    int curr_sum;
    while (*cursor) {
        if (*cursor == '\n') {
            curr_sum = left_digit * 10 + right_digit;
            calibration_sum += curr_sum;
            printf(": %d\n", curr_sum);
            cursor++;
            left_digit = right_digit = 0;
        } else {
            while ((left_digit = try_to_read_digit(cursor)) == -1) {
                putc(*cursor, stdout);
                cursor++;
            }

            // advance to next termination
            while (*cursor != '\n' && *cursor != '\0') {
                putc(*cursor, stdout);
                cursor++;
            }
            
            // iter backwards in search of a match
            while ((right_digit = try_to_read_digit(cursor)) == -1) cursor--;

            // iter to next termination again
            while (*cursor != '\n' && *cursor != '\0') cursor++;
        }
    }
    printf("Final sum (pt2): %d\n", calibration_sum);

    free(input);
}

int main() {
    //part_1();
    printf("\n\n\n\n");
    part_2();
}
