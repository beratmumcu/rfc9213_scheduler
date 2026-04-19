#include "scheduler.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

scheduler_t* scheduler_create(int max_requests) {
    scheduler_t *scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));
    if (!scheduler) return NULL;

    scheduler->queue = heap_create(max_requests);
    if (!scheduler->queue) {
        free(scheduler);
        return NULL;
    }
    
    scheduler->current_time = 0; // Sistemin başlangıç anı (Timestamp için)
    return scheduler;
}

void scheduler_destroy(scheduler_t *scheduler) {
    if (scheduler) {
        // İdealde içeride bekleyen request_t bellekleri de serbest bırakılmalı
        // Simülasyon kolaylığı için var olan elemanları free ile temizliyoruz
        while (scheduler->queue->size > 0) {
            request_t *req = heap_extract_min(scheduler->queue);
            free(req);
        }
        heap_destroy(scheduler->queue);
        free(scheduler);
    }
}

bool scheduler_add_request(scheduler_t *scheduler, int req_id, const char *priority_header) {
    request_t *new_req = (request_t*)malloc(sizeof(request_t));
    if (!new_req) {
        printf("Hata: Bellek ayrilamadi!\n");
        return false;
    }

    new_req->id = req_id;
    new_req->timestamp = scheduler->current_time++; // Geliş sırasını kaydet (FIFO için)

    // Priority header'ı çözümle ve değerleri isteğe ata
    parse_priority_header(priority_header, &new_req->urgency, &new_req->incremental);

    printf("[Gateway] Istek alindi: ID=%d | Header: \"%s\" -> (urgency=%d, incremental=%s)\n",
           new_req->id,
           priority_header ? priority_header : "(varsayilan)",
           new_req->urgency,
           new_req->incremental ? "true" : "false");

    if (!heap_insert(scheduler->queue, new_req)) {
        printf("Hata: Kuyruk dolu! Istek ID=%d reddedildi.\n", req_id);
        free(new_req);
        return false;
    }

    return true;
}

void scheduler_process_next(scheduler_t *scheduler) {
    request_t *req = heap_extract_min(scheduler->queue);
    
    if (req) {
        printf("[Scheduler] ISLENIYOR: ID=%d | Urgency=%d | Incremental=%s | Gelis Sirasi(TS)=%llu\n",
               req->id, req->urgency, req->incremental ? "true" : "false", (unsigned long long)req->timestamp);
        
        // İşlem bittiğinde belleği iade ediyoruz (Memory leak önleme)
        free(req);
    } else {
        printf("[Scheduler] Kuyruk bos, islenecek istek yok.\n");
    }
}
