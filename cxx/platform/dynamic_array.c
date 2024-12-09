#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//
//#define ARRAY_GROWTH_FACTOR 2
//
//#define array_init(type, array, initial_capacity) \
//    do {                                          \
//        array = malloc(sizeof(type) * (initial_capacity)); \
//        if (array == NULL) exit(1);              \
//    } while (0)
//
//#define array_resize(type, array, capacity) \
//    do {                                    \
//        array = realloc(array, sizeof(type) * (capacity)); \
//        if (array == NULL) exit(1);         \
//    } while (0)
//
//
//int array_push(void** array, size_t * size, size_t * capacity, size_t elem_size, const void* element) {
//    if (*size >= *capacity) {
//        *capacity *= ARRAY_GROWTH_FACTOR;
//        void* new_data = realloc(*array, *capacity * elem_size);
//        if (!new_data) return -1;
//        *array = new_data;
//    }
//
//    memcpy((char*)(*array) + (*size) * elem_size, element, elem_size);
//    (*size)++;
//    return 0;
//}
//
//
//int main() {
//    int* array;
//    size_t size = 0;
//    size_t capacity = 4;
//
//    array_init(int, array, capacity);
//
//    for (int i = 0; i < 10; i++) {
//        array_push((void**)&array, &size, &capacity, sizeof(int), &i);
//    }
//
//    for (size_t i = 0; i < size; i++) {
//        printf("%d ", array[i]);
//    }
//
//    free(array);
//    return 0;
//}




#define pointer_array_init(array, initial_capacity) \
    do {                                            \
        array = malloc(sizeof(void*) * (initial_capacity)); \
        if (array == NULL) exit(1);                \
    } while (0)

#define pointer_array_resize(array, capacity) \
    do {                                      \
        array = realloc(array, sizeof(void*) * (capacity)); \
        if (array == NULL) exit(1);           \
    } while (0)
   
#define pointer_array_free_all(array, size, free_func) \
    do {                                               \
        for (size_t i = 0; i < (size); ++i) {          \
            free_func((array)[i]);                     \
        }                                              \
        free(array);                                   \
    } while (0)


int pointer_array_push(void*** array, size_t * size, size_t * capacity, void* element) {
    if (*size >= *capacity) {
        *capacity *= 2;
        void** new_data = realloc(*array, sizeof(void*) * (*capacity));
        if (!new_data) return -1;
        *array = new_data;
    }

    (*array)[(*size)++] = element;
    return 0;
}


void free_string(void* ptr) {
    free(ptr);
}

int main() {
    void** array;
    size_t size = 0;
    size_t capacity = 4;

    pointer_array_init(array, capacity);

    for (int i = 0; i < 5; i++) {
        char* str = (char*)malloc(16);
        snprintf(str, 16, "String %d", i);
        pointer_array_push(&array, &size, &capacity, str);
    }

    for (size_t i = 0; i < size; i++) {
        printf("%s\n", (char*)array[i]);
    }

    pointer_array_free_all(array, size, free_string);
    return 0;
}
