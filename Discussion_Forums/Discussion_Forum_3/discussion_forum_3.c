#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 12

char* original_names[N] = {"kiwi", "berries", "apple", "orange",
    "strawberry", "pineapple", "Kiwi", "Berries", "Apple",
    "Orange", "Strawberry", "Pineapple"};

void swap(void* v[], int i, int j) {
    void* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void generic_qsort(void* v[], int left, int right, int (*comp)(const void*, const void*)) {
    int i, last;
    if (left >= right) return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((*comp)(&v[i], &v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    generic_qsort(v, left, last - 1, comp);
    generic_qsort(v, last + 1, right, comp);
}

// 4.1: Sort in decreasing order
int reverse_strcmp(const void* a, const void* b) {
    const char* sa = *(const char**)a;
    const char* sb = *(const char**)b;
    return strcmp(sb, sa); // reverse order
}

// 4.2: Sort ignoring case
int case_insensitive_cmp(void* a, void* b) {
#ifdef _WIN32
    return _stricmp(*(char**)a, *(char**)b);
#else
    return strcasecmp(*(char**)a, *(char**)b);
#endif
}

void print_names(char* arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
}

void copy_names(char* dest[], char* src[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

int main(void) {
    int n = N;
    char* names_inc[N], *names_dec[N];

    copy_names(names_inc, original_names, n);
    copy_names(names_dec, original_names, n);

    // Increasing order
    printf("Increasing order:\n");
    generic_qsort((void**)names_inc, 0, n - 1, (int(*)(const void*, const void*))strcmp);
    print_names(names_inc, n);

    // Decreasing order
    printf("Decreasing order:\n");
    generic_qsort((void**)names_dec, 0, n - 1, reverse_strcmp);
    print_names(names_dec, n);

    return 0;
} 