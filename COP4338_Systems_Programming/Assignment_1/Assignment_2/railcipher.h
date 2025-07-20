#ifndef RAILCIPHER_H
#define RAILCIPHER_H

#define MAX_LEN 26
#define MAX_COMMAND_LEN 5000
#define TRUE 1
#define FALSE 0
#define INVALID_KEY_LENGTH 1
#define INVALID_KEY_SEQ 2
#define NO_ERROR 0
#define error(m, k) do { fprintf(stderr, m "\n"); exit(k); } while(0)

extern int key[MAX_LEN];
extern int m;

int parse_key(int argc, char *argv[]);
void encrypt(char* plaintext);
void decrypt(char* ciphertext);

#endif // RAILCIPHER_H 