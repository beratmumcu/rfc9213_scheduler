#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "heap.h"
#include <stdbool.h>

// Scheduler (Zamanlayıcı) yapısı
typedef struct {
    min_heap_t *queue;
    uint64_t current_time; // İsteklere geliş sırasına göre zaman damgası vurmak için sayaç
} scheduler_t;

scheduler_t* scheduler_create(int max_requests);
void scheduler_destroy(scheduler_t *scheduler);

// Gelen isteği header'ıyla alır, ayrıştırır ve kuyruğa ekler
bool scheduler_add_request(scheduler_t *scheduler, int req_id, const char *priority_header);

// Kuyruktaki (en öncelikli) sıradaki isteği çıkarır ve işler
void scheduler_process_next(scheduler_t *scheduler);

#endif // SCHEDULER_H
