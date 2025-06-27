#include "railcipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h> // for strcasecmp/strncasecmp

// --- Constants and Macros ---
#define MAX_LEN 26
#define MAX_COMMAND_LEN 5000
#define TRUE 1
#define FALSE 0
#define INVALID_KEY_LENGTH 1
#define INVALID_KEY_SEQ 2
#define NO_ERROR 0
#define error(m, k) do { fprintf(stderr, m "\n"); exit(k); } while(0)

// --- Global Variables ---
int key[MAX_LEN]; // Key array (max 26 columns)
int m;            // Key length (number of columns)

// --- Function Prototypes ---
int parse_key(int argc, char *argv[]);
void encrypt(char* plaintext);
void decrypt(char* ciphertext);
static int is_legal_key(void);
static int check_integer(char* input);
static int handle_args(int argc, char* argv[]);
static int is_integer(const char* s);

// --- Parse the key from command-line arguments ---
int parse_key(int argc, char *argv[]) {
    if (argc < 3) error("Invalid key length.", INVALID_KEY_LENGTH);
    m = atoi(argv[1]);
    if (m < 2 || m > MAX_LEN) error("Invalid key length.", INVALID_KEY_LENGTH);
    if (argc != m + 2) error("Invalid key length.", INVALID_KEY_LENGTH);
    int used[MAX_LEN+1] = {0};
    for (int i = 0; i < m; i++) {
        key[i] = atoi(argv[i+2]);
        if (key[i] < 1 || key[i] > m) error("Invalid key sequence.", INVALID_KEY_SEQ);
        if (used[key[i]]) error("Invalid key sequence.", INVALID_KEY_SEQ);
        used[key[i]] = 1;
    }
    return TRUE;
}

// Helper to print a string in uppercase
void print_upper(const char* s) {
    while (*s) {
        putchar(toupper((unsigned char)*s));
        s++;
    }
}

// encrypt function
typedef void (*crypt_fn)(char*);

void encrypt(char* plaintext) {
    int read = 0, write = 0;
    while (plaintext[read] != '\0') {
        if (isalpha((unsigned char)plaintext[read]))
            plaintext[write++] = tolower((unsigned char)plaintext[read]);
        read++;
    }
    plaintext[write] = '\0';
    int l = write;
    int n = (l + m - 1) / m;
    char rectangle[n][m];
    int counter = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (counter < l)
                rectangle[row][col] = plaintext[counter++];
            else
                rectangle[row][col] = 'z' + col - m + 1;
        }
    }
    int key_inverse[MAX_LEN];
    for (int i = 0; i < m; i++)
        key_inverse[key[i] - 1] = i;
    char output[n * m + 1];
    int out_idx = 0;
    for (int col = 0; col < m; col++) {
        for (int row = 0; row < n; row++)
            output[out_idx++] = rectangle[row][key_inverse[col]];
    }
    output[out_idx] = '\0';
    print_upper(output);
    putchar('\n');
}

// decrypt function
void decrypt(char* ciphertext) {
    char buffer[MAX_COMMAND_LEN];
    strncpy(buffer, ciphertext, MAX_COMMAND_LEN-1);
    buffer[MAX_COMMAND_LEN-1] = '\0';
    char clean[MAX_COMMAND_LEN];
    int l = 0;
    for (int i = 0; buffer[i]; i++) {
        if (isalpha((unsigned char)buffer[i]))
            clean[l++] = tolower((unsigned char)buffer[i]);
    }
    clean[l] = '\0';
    int n = (l + m - 1) / m;
    char rectangle[n][m];
    int idx = 0;
    int key_inverse[MAX_LEN];
    for (int i = 0; i < m; i++)
        key_inverse[key[i] - 1] = i;
    for (int col = 0; col < m; col++) {
        int real_col = key_inverse[col];
        for (int row = 0; row < n; row++) {
            if (idx < l)
                rectangle[row][real_col] = clean[idx++];
            else
                rectangle[row][real_col] = 'z';
        }
    }
    char output[n * m + 1];
    int out_idx = 0;
    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            output[out_idx++] = rectangle[row][col];
    output[out_idx] = '\0';
    print_upper(output);
    putchar('\n');
}

// Checks if key[] is a valid permutation of 1..m
static int is_legal_key(void) {
    char* seen = (char*)calloc(m+1, 1); // all initialized to 0/false
    for (int i = 0; i < m; i++) {
        if (key[i] < 1 || key[i] > m) { // out of range
            free(seen);
            return FALSE;
        }
        if (!seen[key[i]]) {
            seen[key[i]] = TRUE;
        } else { // duplicate
            free(seen);
            return FALSE;
        }
    }
    free(seen);
    return TRUE;
}

// Returns TRUE if input is a valid integer, FALSE otherwise
static int check_integer(char* input) {
    (void)input; // Silence unused parameter warning
    return TRUE;
}

// Handles argument parsing and key setup
static int handle_args(int argc, char* argv[]) {
    if (argc < 3 || !is_integer(argv[1])) {
        printf("railcipher: Fatal error! First CLA must be a valid integer.\n");
        return INVALID_KEY_SEQ;
    }
    m = atoi(argv[1]);
    if (m < 2 || m > MAX_LEN) {
        printf("railcipher: Fatal error! The encryption key length cannot exceed 26.\n");
        return INVALID_KEY_LENGTH;
    }
    for (int i = 0; i < m; i++) {
        if (!is_integer(argv[i+2])) {
            printf("railcipher: Fatal error! First CLA must be a valid integer.\n");
            return INVALID_KEY_SEQ;
        }
        key[i] = atoi(argv[i+2]);
    }
    if (!is_legal_key()) {
        printf("railcipher: Fatal error! The encryption key passed as CLAs is not valid.\n");
        return INVALID_KEY_SEQ;
    }
    return NO_ERROR;
}

static int is_integer(const char* s) {
    if (!s || *s == '\0') return 0;
    if (*s == '-' || *s == '+') s++;
    int found_digit = 0;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        found_digit = 1;
        s++;
    }
    return found_digit;
}

int main(int argc, char *argv[]) {
    int error_code = handle_args(argc, argv);
    if (error_code) {
        printf("Usage: %s <key length> <key permutation>\n", argv[0]);
        return NO_ERROR;
    }
    char command[MAX_COMMAND_LEN];
    while (fgets(command, MAX_COMMAND_LEN, stdin)) {
        int len = strlen(command);
        if (command[len-1] == '\n') {
            command[len-1] = '\0';
            len--;
        }
        if (!strcasecmp(command, "quit")) {
            break;
        }
        if (!strncasecmp(command, "encrypt ", 8)) {
            encrypt(command + 8);
        } else if (!strncasecmp(command, "decrypt ", 8)) {
            decrypt(command + 8);
        } else {
            printf("invalid command! try again!\n");
        }
    }
    return NO_ERROR;
}
