#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "confused.h"

#define NUM_CONFUSABLES (sizeof(confusable) / sizeof(confusable[0]))

/**
 * * utf8_char_len - determines the length of a character.
 * 
 * This function returns the length of the character in bytes.
 * Sizes can be between 1 and 4 bytes in length.
 *
 * @param str A pointer to the character string
 * @return The length in bytes of the first character in the string
 *
 * The function assumes it is a valid UTF-8 encoded string. If an invalid
 * byte is encountered, it defaults to 1 byte length.
 * 
 */
int utf8_char_len(const char *str) {
    unsigned char c = str[0];
    if (c < 0x80)           return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;
    return 1;
}

/**
 * find_replacement - finds a replacement alphanumeric character for a given confusable character.
 * 
 * This function searches through an array of known confusable characters to find a match.
 * If a match was found, it returns the associated alphanumeric character otherwise it returns NULL.
 * 
 * @param utf8_char A pointer to the character to check for confusables.
 * @return A pointer to the replacement alphanumeric string for the matched confusable.
 */
const char* find_replacement(const char *utf8_char) {
    for (size_t j = 0; j < NUM_CONFUSABLES; j++) {
        // Loop through each character in confusable[j].confusable to match UTF-8 characters
        const char *conf_char = confusable[j].confusable;
        while (*conf_char) {
            int char_len = utf8_char_len(conf_char);
            if (strncmp(utf8_char, conf_char, char_len) == 0) {
                return confusable[j].alphanumeric;
            }
            conf_char += char_len;
        }
    }
    return NULL;
}

/**
 * replace_confusables - Replaces confusable character in a string with specified alphanumeric characters.
 * 
 * This function iterates through each character of the input string and checks if it has a confusable replacement.
 * If the replacement was found, it is added to the output string, otherwise the original character is copied.
 * 
 * @param input A pointer to the input string
 * @return A output string with confusables replaced, or NULL.
 */
char* replace_confusables(const char *input) {
    size_t output_size = strlen(input) * 2;
    char *output = malloc(output_size);
    if (!output) return NULL;

    size_t out_idx = 0;
    const char *p = input;
    
    while (*p) {
        int char_len = utf8_char_len(p);
        const char *replacement = find_replacement(p);

        if (replacement) {
            size_t repl_len = strlen(replacement);
            strcpy(&output[out_idx], replacement);
            out_idx += repl_len;
        } else {
            strncpy(&output[out_idx], p, char_len);
            out_idx += char_len;
        }
        p += char_len;
    }

    output[out_idx] = '\0';
    return output;
}

int main() {
    const char *test_str = "𝐓𝐡𝖎𝑠 𝙞𝘴 𝒂 𝕥𝔢𝔰𝓽 𝓼𝕥𝕣𝓲𝓷𝓰 𝖜𝖎𝘁𝖍 𝓶𝓪𝓷𝔂 𝕔𝔬𝖓𝖋𝕦𝓼𝓪𝖇𝔩𝓮𝕤.";
    char *result = replace_confusables(test_str);

    if (result) {
        printf("Original: %s\n", test_str);
        printf("Processed: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
