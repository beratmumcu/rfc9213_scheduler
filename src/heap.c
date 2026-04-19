#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

// İki isteğin önceliğini karşılaştıran yardımcı fonksiyon
// Dönüş değeri < 0 ise req1 önceliklidir (req1 < req2)
// Dönüş değeri > 0 ise req2 önceliklidir
static int compare_requests(request_t *req1, request_t *req2) {
    if (req1->urgency != req2->urgency) {
        // Küçük urgency daha önceliklidir (0 en yüksek)
        return req1->urgency - req2->urgency;
    }
    // Urgency aynıysa, sisteme ilk gelen (timestamp küçük olan) önceliklidir (FIFO)
    if (req1->timestamp < req2->timestamp) return -1;
    if (req1->timestamp > req2->timestamp) return 1;
    return 0;
}

// İki düğümü yer değiştirmek için
static void swap(request_t **a, request_t **b) {
    request_t *temp = *a;
    *a = *b;
    *b = temp;
}

min_heap_t* heap_create(int capacity) {
    min_heap_t *heap = (min_heap_t*)malloc(sizeof(min_heap_t));
    if (!heap) return NULL;
    
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (request_t**)malloc(capacity * sizeof(request_t*));
    if (!heap->array) {
        free(heap);
        return NULL;
    }
    return heap;
}

void heap_destroy(min_heap_t *heap) {
    if (heap) {
        if (heap->array) free(heap->array);
        free(heap);
    }
}

// Yukarı doğru eleman kaydırmak (ekleme işlemi sonrası)
static void heapify_up(min_heap_t *heap, int index) {
    int parent = (index - 1) / 2;
    // Eğer eklenen eleman, ebeveyninden daha öncelikliyse yer değiştir
    if (index > 0 && compare_requests(heap->array[index], heap->array[parent]) < 0) {
        swap(&heap->array[index], &heap->array[parent]);
        heapify_up(heap, parent);
    }
}

bool heap_insert(min_heap_t *heap, request_t *req) {
    if (heap->size == heap->capacity) return false; // Heap dolu
    
    // Elemanı dizinin en sonuna ekle
    int index = heap->size;
    heap->array[index] = req;
    heap->size++;
    
    // Heap özelliğini korumak için yukarı doğru kaydır
    heapify_up(heap, index);
    
    return true;
}

// Aşağı doğru eleman kaydırmak (kök çıkarma işlemi sonrası)
static void heapify_down(min_heap_t *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Sol çocuk kökten daha öncelikli mi?
    if (left < heap->size && compare_requests(heap->array[left], heap->array[smallest]) < 0) {
        smallest = left;
    }
    // Sağ çocuk şu anki en öncelikliden daha öncelikli mi?
    if (right < heap->size && compare_requests(heap->array[right], heap->array[smallest]) < 0) {
        smallest = right;
    }

    // Eğer en öncelikli çocuk bulunduğumuz düğüm değilse yer değiştir
    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        heapify_down(heap, smallest); // Değişen çocuk üzerinden devam et
    }
}

request_t* heap_extract_min(min_heap_t *heap) {
    if (heap->size <= 0) return NULL; // Heap boş
    
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    // Kök elemanı al (en öncelikli olan)
    request_t *root = heap->array[0];
    
    // Son elemanı köke taşı
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    
    // Heap ağacının dengesini (özelliğini) tekrar sağla
    heapify_down(heap, 0);

    return root;
}
