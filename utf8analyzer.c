#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// Whether the string is valid ASCII
bool is_ascii_string(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if ((unsigned char)str[i] > 127) {
            return false;
        }
    }
    return true;
}


// The same input string, but any ASCII lowercase characters a-z are changed to their uppercase versions. Leaves all other characters unchanged.
void uppercase_ascii(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

// Length of the whole string in bytes.
// Function to count UTF-8 codepoints in string
int utf8_strlen(const char *str) {
    int count = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        unsigned char byte = (unsigned char)str[i];
        
        if ((byte & 0x80) == 0) {
            i += 1;  // 1 byte
        } else if ((byte & 0xE0) == 0xC0) {
            i += 2;  // 2 bytes
        } else if ((byte & 0xF0) == 0xE0) {
            i += 3;  // 3 bytes
        } else if ((byte & 0xF8) == 0xF0) {
            i += 4;  // 4 bytes
        } else {
            i += 1;  // Invalid, skip
        }
        count++;
    }
    
    return count;
}

// Function to extract codepoint at specific byte position
int32_t get_codepoint_at_byte(const char *str, int byte_index) {
    unsigned char byte = (unsigned char)str[byte_index];
    
    if ((byte & 0x80) == 0) {
        return byte;
    } else if ((byte & 0xE0) == 0xC0) {
        unsigned char byte2 = (unsigned char)str[byte_index + 1];
        if ((byte2 & 0xC0) != 0x80) return -1;
        return ((byte & 0x1F) << 6) | (byte2 & 0x3F);
    } else if ((byte & 0xF0) == 0xE0) {
        unsigned char byte2 = (unsigned char)str[byte_index + 1];
        unsigned char byte3 = (unsigned char)str[byte_index + 2];
        if ((byte2 & 0xC0) != 0x80 || (byte3 & 0xC0) != 0x80) return -1;
        return ((byte & 0x0F) << 12) | ((byte2 & 0x3F) << 6) | (byte3 & 0x3F);
    } else if ((byte & 0xF8) == 0xF0) {
        unsigned char byte2 = (unsigned char)str[byte_index + 1];
        unsigned char byte3 = (unsigned char)str[byte_index + 2];
        unsigned char byte4 = (unsigned char)str[byte_index + 3];
        if ((byte2 & 0xC0) != 0x80 || (byte3 & 0xC0) != 0x80 || (byte4 & 0xC0) != 0x80) return -1;
        return ((byte & 0x07) << 18) | ((byte2 & 0x3F) << 12) | ((byte3 & 0x3F) << 6) | (byte4 & 0x3F);
    }
    
    return -1;
}

// Function to get size of UTF-8 character at byte position
int get_char_size(const char *str, int byte_index) {
    unsigned char byte = (unsigned char)str[byte_index];
    
    if ((byte & 0x80) == 0) return 1;
    else if ((byte & 0xE0) == 0xC0) return 2;
    else if ((byte & 0xF0) == 0xE0) return 3;
    else if ((byte & 0xF8) == 0xF0) return 4;
    else return 1;  // Invalid
}

// Function to encode UTF-8 codepoint to string
int encode_utf8_codepoint(uint32_t codepoint, char *output) {
    if (codepoint <= 127) {
        output[0] = (char)codepoint;
        output[1] = '\0';
        return 1;
    } else if (codepoint <= 2047) {
        output[0] = 0xC0 | (codepoint >> 6);
        output[1] = 0x80 | (codepoint & 0x3F);
        output[2] = '\0';
        return 2;
    } else if (codepoint <= 65535) {
        output[0] = 0xE0 | (codepoint >> 12);
        output[1] = 0x80 | ((codepoint >> 6) & 0x3F);
        output[2] = 0x80 | (codepoint & 0x3F);
        output[3] = '\0';
        return 3;
    } else if (codepoint <= 1114111) {
        output[0] = 0xF0 | (codepoint >> 18);
        output[1] = 0x80 | ((codepoint >> 12) & 0x3F);
        output[2] = 0x80 | ((codepoint >> 6) & 0x3F);
        output[3] = 0x80 | (codepoint & 0x3F);
        output[4] = '\0';
        return 4;
    }
    output[0] = '\0';
    return 0;
}

// Function to check if codepoint is an animal emoji
bool is_animal_emoji(int32_t codepoint) {
    return (codepoint >= 0x1F400 && codepoint <= 0x1F43F) ||
           (codepoint >= 0x1F980 && codepoint <= 0x1F9AE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }
}
    // implement the UTF-8 analyzer here
<<<<<<< HEAD
    void is_ASCII(char word[]) {
	    for(int i = 0; i != 0; i++) {
		    if(word[i] >= 0 && word[i] <= 127) {
			    printf("%c", true);
		    }
	    }
	    printf("%c", false);
=======
     const char *input = argv[1];
    int byte_length = strlen(input);
    int codepoint_count = utf8_strlen(input);
    
    // 1. Check if valid ASCII
    printf("Valid ASCII: %s\n", is_ascii_string(input) ? "true" : "false");
    
    // 2. Uppercase ASCII characters
    char *uppercased = malloc(byte_length + 1);
    strcpy(uppercased, input);
    uppercase_ascii(uppercased);
    printf("Uppercased ASCII: %s\n", uppercased);
    
    // 3. Length in bytes
    printf("Length in bytes: %d\n", byte_length);
    
    // 4. Number of UTF-8 codepoints
    printf("Number of code points: %d\n", codepoint_count);
    
    // 5 & 6. Extract codepoints and count bytes per codepoint
    int byte_index = 0;
    int codepoint_index = 0;
    int32_t codepoints[1000];
    int bytes_per_cp[1000];
    
    // Collect all codepoints and their byte counts
    while (byte_index < byte_length && codepoint_index < codepoint_count) {
        int32_t cp = get_codepoint_at_byte(input, byte_index);
        int char_size = get_char_size(input, byte_index);
        
        codepoints[codepoint_index] = cp;
        bytes_per_cp[codepoint_index] = char_size;
        
        byte_index += char_size;
        codepoint_index++;
    }
    
    // Print codepoints
    printf("Code points as decimal numbers:");
    for (int i = 0; i < codepoint_count; i++) {
        printf(" %d", codepoints[i]);
    }
    printf("\n");
    
    // Print bytes per codepoint
    printf("Bytes per code point:");
    for (int i = 0; i < codepoint_count; i++) {
        printf(" %d", bytes_per_cp[i]);
    }
    printf("\n");
    
    // 7. Substring of first 6 codepoints
    printf("Substring of the first 6 code points: \"");
    byte_index = 0;
    int printed_codepoints = 0;
    while (byte_index < byte_length && printed_codepoints < 6) {
        int char_size = get_char_size(input, byte_index);
        for (int i = 0; i < char_size; i++) {
            printf("%c", input[byte_index + i]);
        }
        byte_index += char_size;
        printed_codepoints++;
    }
    printf("\"\n");
    
    // 8. Find animal emojis
    printf("Animal emojis:");
    for (int i = 0; i < codepoint_count; i++) {
        if (is_animal_emoji(codepoints[i])) {
            char emoji_str[5];
            encode_utf8_codepoint(codepoints[i], emoji_str);
            printf(" %s", emoji_str);
        }
    }
    printf("\n");
    
    // 9. Next character of codepoint at index 3
    if (codepoint_count > 3) {
        int32_t cp_at_3 = codepoints[3];
        char next_char[5];
        encode_utf8_codepoint(cp_at_3 + 1, next_char);
        printf("Next character of Codepoint at index 3: %s\n", next_char);
    } else {
        printf("Next character of Codepoint at index 3: (index out of range)\n");
    }
    
    free(uppercased);
    return 0;   
>>>>>>> b461cde21bfdead62e73c27cc3b119a03571d8db
}
