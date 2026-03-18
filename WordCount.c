#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

int count_characters(FILE *file) {
    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

int count_words(FILE *file) {
    int count = 0;
    int ch;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == ',' || ch == '\t' || ch == '\n' || ch == '\r') {
            if (in_word) {
                count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        count++;
    }

    return count;
}

int main(int argc, char *argv[]) {
    // 设置控制台输出为 UTF-8 编码
    SetConsoleOutputCP(CP_UTF8);

    if (argc != 3) {
        printf("Usage: WordCount.exe [-c|-w] <input_file_name>\n");
        printf("  -c: Count characters\n");
        printf("  -w: Count words\n");
        return 1;
    }

    char *param = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return 1;
    }

    if (strcmp(param, "-c") == 0) {
        int char_count = count_characters(file);
        printf("字符数: %d\n", char_count);
    } else if (strcmp(param, "-w") == 0) {
        int word_count = count_words(file);
        printf("词数: %d\n", word_count);
    } else {
        printf("Error: Unknown parameter '%s'\n", param);
        printf("Use -c for character count or -w for word count\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
