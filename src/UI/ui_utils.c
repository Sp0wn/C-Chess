//File guard
#include "../../include/UI/ui_utils.h"

void tokenize_config(char *key, char *value, char* buffer) {
    int i, j;
    i = j = 0;

    //Parses the key
    while(buffer[i] != '=') {
        key[i] = buffer[i];
        i++;
    }
    key[i] = '\0';

    //Parses the value
    while(buffer[i + 1 + j] != '\n') {
        value[j] = buffer[i + 1 + j];
        j++;
    }
    value[j] = '\0';
}
