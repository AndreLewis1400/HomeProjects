#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10000
#define error(message, code) do{printf("%s\n", message); exit(code);}while(0)

typedef struct node {
    char* string;
    struct node* next;
} node;

typedef struct bucket {
    char* min_word;
    node* head;
} bucket;

// Insert new_value right after the current node
void insert_after(node* current, char* new_value) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->string = strdup(new_value);
    new_node->next = current->next;
    current->next = new_node;
}

// Insert word into bucket in sorted order
void insert_into_bucket(bucket* buckets, int bucket_count, char* word) {
    // Find the appropriate bucket
    int bucket_index = 0;
    for (int i = 0; i < bucket_count; i++) {
        if (strcasecmp(word, buckets[i].min_word) >= 0) {
            bucket_index = i;
        } else {
            break;
        }
    }
    
    // Insert the word in the right place of linked list stored in the bucket
    node* current = buckets[bucket_index].head;
    node* prev = NULL;
    
    // Find the correct position to insert (maintain alphabetical order)
    while (current != NULL && strcasecmp(current->string, word) < 0) {
        prev = current;
        current = current->next;
    }
    
    // Create new node
    node* new_node = (node*)malloc(sizeof(node));
    new_node->string = strdup(word);
    
    // Insert at head if bucket is empty or word should be first
    if (prev == NULL) {
        new_node->next = buckets[bucket_index].head;
        buckets[bucket_index].head = new_node;
    } else {
        // Insert after prev
        new_node->next = prev->next;
        prev->next = new_node;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        error("bucketsort: Fatal error! There must be at-least one CLA.", 1);
    }
    
    // Initialize buckets
    bucket* buckets = (bucket*)malloc(argc * sizeof(bucket));
    buckets[0].min_word = "";  // always empty string for the min_word of first bucket
    buckets[0].head = NULL;
    
    for (int i = 1; i < argc; i++) {
        buckets[i].head = NULL;  // initially, all buckets are empty
        buckets[i].min_word = strdup(argv[i]);
        
        // Check if CLAs are in alphabetical order
        if (strcasecmp(buckets[i-1].min_word, buckets[i].min_word) >= 0) {
            error("bucketsort: Fatal error! CLAs must be entered in alphabetical order", 1);
        }
    }
    
    // Read the keyboard (stdin)
    char* line = (char*)malloc(MAX_LEN);
    while (fgets(line, MAX_LEN, stdin)) {
        if (line[strlen(line)-1] == '\n') {  // removing new line
            line[strlen(line)-1] = '\0';
        }
        
        char* input_string = strtok(line, " ");
        do {
            printf("Next word is %s\n", input_string);
            
            // insert to appropriate bucket:
            // 1. Find the appropriate bucket
            // 2. Insert the word in the right place of linked list stored in the bucket
            insert_into_bucket(buckets, argc, input_string);
            
        } while ((input_string = strtok(NULL, " ")));
    }
    
    // print all non-empty buckets...
    for (int i = 0; i < argc; i++) {
        if (buckets[i].head != NULL) {  // not empty
            printf("bucket %d: ", i);
            
            // go through the linked list and print all the words one by one
            // separate the words by space
            node* current = buckets[i].head;
            while (current != NULL) {
                printf("%s", current->string);
                if (current->next != NULL) {
                    printf(" ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
    
    // Clean up memory
    for (int i = 0; i < argc; i++) {
        node* current = buckets[i].head;
        while (current != NULL) {
            node* temp = current;
            current = current->next;
            free(temp->string);
            free(temp);
        }
        if (i > 0) {
            free(buckets[i].min_word);
        }
    }
    free(buckets);
    free(line);
    
    return 0;
} 