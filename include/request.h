#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>
#include <stdint.h>

// İstek yapısı (struct)
typedef struct {
    int id;               // İsteğin benzersiz kimliği (ID)
    uint8_t urgency;      // Öncelik seviyesi: 0 (en acil) ile 7 (en düşük) arası, varsayılan: 3
    bool incremental;     // Artımlı işleme bayrağı, varsayılan: false
    uint64_t timestamp;   // Sisteme geliş zamanı (aynı urgency değerine sahip isteklerde FIFO için)
} request_t;

#endif // REQUEST_H
