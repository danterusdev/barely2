#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"
#include "string_util.h"

Dynamic_Array_Impl(char*, Array_String, array_string_)
Dynamic_Array_Impl(char, String_Buffer, stringbuffer_)

char* copy_string(char* string) {
    size_t length = strlen(string);
    return copy_string_length(string, length);
}

char* copy_string_length(char* string, size_t length) {
    char* result = malloc(length + 1);
    memcpy(result, string, length + 1);
    result[length] = 0;
    return result;
}

bool string_contains(char* string, char character) {
    for (size_t i = 0; i < strlen(string); i++) {
        if (string[i] == character) return true;
    }
    return false;
}

int string_index(char* string, char character) {
    for (size_t i = 0; i < strlen(string); i++) {
        if (string[i] == character) return i;
    }
    return -1;
}

char* string_substring(char* string, size_t start, size_t end) {
    size_t length = end - start;
    char* result = malloc(length + 1);
    memcpy(result, string + start, length);
    memset(result + length, 0, 1);
    return result;
}

void stringbuffer_appendstring(String_Buffer* buffer, char* string) {
    // seems quite inefficient, adding one at a time
    for (size_t i = 0; i < strlen(string); i++) {
        stringbuffer_append(buffer, string[i]);
    }
}
