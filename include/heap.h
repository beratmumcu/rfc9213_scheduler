#ifndef HEAP_H
#define HEAP_H

#include "request.h"

// Min-Heap yapısı
typedef struct {
    request_t **array; // İstek işaretçilerini (pointer) tutan dizi
    int capacity;      // Heap'in maksimum kapasitesi
    int size;          // Heap'teki anlık eleman sayısı
} min_heap_t;

// Min-Heap fonksiyonları
min_heap_t* heap_create(int capacity);
void heap_destroy(min_heap_t *heap);
bool heap_insert(min_heap_t *heap, request_t *req);
request_t* heap_extract_min(min_heap_t *heap);

#endif // HEAP_H
