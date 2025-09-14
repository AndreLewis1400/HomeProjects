#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

// Constants
#define MAX_WORD_LENGTH 100
#define MAX_LINE_LENGTH 1000
#define MAX_DICT_SIZE 100000
#define BUFFER_SIZE 2000000L

// Global variables
char* dictionary[MAX_DICT_SIZE];
int dictionary_size = 0;
char* buffer = NULL;
int buffer_size = 0;
long total_binary_search_time = 0;
pthread_mutex_t time_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;

// Command line options
int nthreads = 1;
int verbose = 0;
int time_option = 0;
int sorted = 0;
int distinct = 0;
int word_lengths[10];
int num_lengths = 0;

// Thread arguments structure
typedef struct {
    int thread_id;
    int start_pos;
    int end_pos;
} thread_args_t;

// Function prototypes
static long get_nanos(void);
int binsearch(char* dictionary_words[], int list_size, char* keyword);
void* word_puzzle_solver(void* arg);
void load_dictionary_from_json(const char* filename);
void parse_command_line(int argc, char* argv[]);
void print_usage(const char* program_name);
void sort_words(char** words, int count);
void remove_duplicates(char** words, int* count);
void print_results(char** found_words, int count);

int main(int argc, char* argv[]) {
    long startTime = get_nanos();
    
    // Parse command line arguments
    parse_command_line(argc, argv);
    
    if (verbose) {
        fprintf(stderr, "Note: Program started with %d threads\n", nthreads);
    }
    
    // Load dictionary from JSON file
    load_dictionary_from_json("/Users/andrelewis/Downloads/dictionary.json");
    
    if (verbose) {
        fprintf(stderr, "Note: Dictionary loaded with %d words\n", dictionary_size);
    }
    
    // Read input buffer from stdin
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed for buffer\n");
        return 1;
    }
    
    buffer_size = fread(buffer, 1, BUFFER_SIZE, stdin);
    buffer[buffer_size] = '\0';
    
    if (verbose) {
        fprintf(stderr, "Note: Read %d characters from input\n", buffer_size);
    }
    
    // Create threads
    pthread_t* threads = malloc(nthreads * sizeof(pthread_t));
    thread_args_t* thread_args = malloc(nthreads * sizeof(thread_args_t));
    
    if (!threads || !thread_args) {
        fprintf(stderr, "Error: Memory allocation failed for threads\n");
        return 1;
    }
    
    // Calculate work distribution
    int chunk_size = buffer_size / nthreads;
    
    for (int i = 0; i < nthreads; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].start_pos = i * chunk_size;
        thread_args[i].end_pos = (i == nthreads - 1) ? buffer_size : (i + 1) * chunk_size;
        
        if (verbose) {
            fprintf(stderr, "Note: Thread %d created (positions %d to %d)\n", 
                    i, thread_args[i].start_pos, thread_args[i].end_pos);
        }
        
        if (pthread_create(&threads[i], NULL, word_puzzle_solver, &thread_args[i]) != 0) {
            fprintf(stderr, "Error: Failed to create thread %d\n", i);
            return 1;
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
        if (verbose) {
            fprintf(stderr, "Note: Thread %d joined\n", i);
        }
    }
    
    // Print timing information
    long total_time = get_nanos() - startTime;
    
    if (time_option) {
        fprintf(stderr, "Total binary search time: %ld nanoseconds\n", total_binary_search_time);
    }
    
    if (verbose) {
        fprintf(stderr, "Note: Total time: %ld nanoseconds using %d threads\n", total_time, nthreads);
    }
    
    // Cleanup
    free(threads);
    free(thread_args);
    free(buffer);
    for (int i = 0; i < dictionary_size; i++) {
        free(dictionary[i]);
    }
    
    return 0;
}

static long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + (long)ts.tv_nsec;
}

int binsearch(char* dictionary_words[], int list_size, char* keyword) {
    int mid, low = 0, high = list_size - 1;
    while (high >= low) {
        mid = low + (high - low) / 2;
        if (strcmp(dictionary_words[mid], keyword) < 0)
            low = mid + 1;
        else if (strcmp(dictionary_words[mid], keyword) > 0)
            high = mid - 1;
        else
            return mid;
    }
    return -1; // not found
}

void* word_puzzle_solver(void* arg) {
    thread_args_t* args = (thread_args_t*)arg;
    int thread_id = args->thread_id;
    int start_pos = args->start_pos;
    int end_pos = args->end_pos;
    
    char** found_words = malloc(1000 * sizeof(char*));
    int found_count = 0;
    
    if (verbose) {
        pthread_mutex_lock(&output_mutex);
        fprintf(stderr, "Note: Thread #%d: started!\n", thread_id);
        pthread_mutex_unlock(&output_mutex);
    }
    
    // Check each word length
    for (int len_idx = 0; len_idx < num_lengths; len_idx++) {
        int target_length = word_lengths[len_idx];
        
        // Slide window through the buffer segment
        for (int i = start_pos; i <= end_pos - target_length; i++) {
            // Extract word of target length
            char word[MAX_WORD_LENGTH];
            strncpy(word, &buffer[i], target_length);
            word[target_length] = '\0';
            
            // Check if word contains only letters
            int valid_word = 1;
            for (int j = 0; j < target_length; j++) {
                if (!isalpha(word[j])) {
                    valid_word = 0;
                    break;
                }
            }
            
            if (!valid_word) continue;
            
            // Convert to lowercase for dictionary lookup
            for (int j = 0; j < target_length; j++) {
                word[j] = tolower(word[j]);
            }
            
            // Binary search in dictionary
            long search_start = get_nanos();
            int found = binsearch(dictionary, dictionary_size, word);
            long search_end = get_nanos();
            
            // Update total binary search time
            pthread_mutex_lock(&time_mutex);
            total_binary_search_time += (search_end - search_start);
            pthread_mutex_unlock(&time_mutex);
            
            if (found != -1) {
                // Word found in dictionary
                pthread_mutex_lock(&output_mutex);
                printf("Thread #%d: %s\n", thread_id, word);
                pthread_mutex_unlock(&output_mutex);
                
                // Store word for sorting/removing duplicates if needed
                if (sorted || distinct) {
                    found_words[found_count] = strdup(word);
                    found_count++;
                }
            }
        }
    }
    
    // Handle sorting and duplicate removal if requested
    if (sorted || distinct) {
        if (sorted) {
            sort_words(found_words, found_count);
        }
        if (distinct) {
            remove_duplicates(found_words, &found_count);
        }
        
        // Print sorted/distinct results
        pthread_mutex_lock(&output_mutex);
        for (int i = 0; i < found_count; i++) {
            printf("%s\n", found_words[i]);
            free(found_words[i]);
        }
        pthread_mutex_unlock(&output_mutex);
    }
    
    free(found_words);
    
    return NULL;
}

void load_dictionary_from_json(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open dictionary file %s\n", filename);
        exit(1);
    }
    
    char line[MAX_LINE_LENGTH];
    int in_dictionary_array = 0;
    dictionary_size = 0;
    
    while (fgets(line, sizeof(line), file)) {
        // Skip until we find the "dictionary" array
        if (strstr(line, "\"dictionary\"") != NULL) {
            in_dictionary_array = 1;
            continue;
        }
        
        if (!in_dictionary_array) continue;
        
        // Check if we've reached the end of the array
        if (strstr(line, "]") != NULL) {
            break;
        }
        
        // Extract word from JSON format: "word",
        char* start = strchr(line, '"');
        if (start) {
            start++; // Skip the opening quote
            char* end = strrchr(start, '"');
            if (end) {
                *end = '\0'; // Null-terminate the word
                
                // Allocate memory and copy the word
                dictionary[dictionary_size] = strdup(start);
                dictionary_size++;
                
                if (dictionary_size >= MAX_DICT_SIZE) {
                    fprintf(stderr, "Warning: Dictionary size limit reached\n");
                    break;
                }
            }
        }
    }
    
    fclose(file);
}

void parse_command_line(int argc, char* argv[]) {
    // Default word lengths
    word_lengths[0] = 8;
    word_lengths[1] = 9;
    num_lengths = 2;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-nthreads") == 0 && i + 1 < argc) {
            nthreads = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-verbose") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "-time") == 0) {
            time_option = 1;
        } else if (strcmp(argv[i], "-sorted") == 0) {
            sorted = 1;
        } else if (strcmp(argv[i], "-distinct") == 0) {
            distinct = 1;
        } else if (strcmp(argv[i], "-len") == 0 && i + 1 < argc) {
            // Parse comma-separated list of lengths
            char* lengths_str = argv[++i];
            char* token = strtok(lengths_str, ",");
            num_lengths = 0;
            
            while (token != NULL && num_lengths < 10) {
                word_lengths[num_lengths++] = atoi(token);
                token = strtok(NULL, ",");
            }
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            exit(0);
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            print_usage(argv[0]);
            exit(1);
        }
    }
}

void print_usage(const char* program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -nthreads n    Number of threads (default: 1)\n");
    printf("  -verbose       Print verbose output\n");
    printf("  -time          Print binary search time\n");
    printf("  -sorted        Sort output words\n");
    printf("  -distinct      Remove duplicate words\n");
    printf("  -len l1,l2,... Word lengths to search (default: 8,9)\n");
    printf("  -h, --help     Show this help message\n");
}

void sort_words(char** words, int count) {
    // Simple bubble sort for small arrays
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char* temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

void remove_duplicates(char** words, int* count) {
    if (*count <= 1) return;
    
    int write_index = 1;
    for (int read_index = 1; read_index < *count; read_index++) {
        if (strcmp(words[read_index], words[write_index - 1]) != 0) {
            words[write_index] = words[read_index];
            write_index++;
        } else {
            free(words[read_index]);
        }
    }
    *count = write_index;
} 