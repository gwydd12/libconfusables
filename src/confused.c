#include <stdio.h>
#include <string.h>
#include "confused.h"

char* convert(char* c) {
    for (int i = 0; i < sizeof(confusable) / sizeof(confusable[0]); i++) {
        if(strstr(confusable[i].confusable, c) != NULL) {
            return confusable[i].alphanumeric;
        }
    }
}

int main(void) {
    printf("%s", convert("⓭"));
}
