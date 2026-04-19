#include "scheduler.h"
#include <stdio.h>

int main() {
    printf("=== RFC 9213 API Gateway Priority Request Scheduler ===\n\n");

    // 10 kapasiteli bir simülasyon kuyruğu
    scheduler_t *gateway = scheduler_create(10);
    if (!gateway) {
        printf("Scheduler baslatilamadi.\n");
        return 1;
    }

    printf("--- Istekler Gateway'e Geliyor ---\n");

    // 1. İstek: Header yok, varsayılan değerleri (u=3, i=false) almalı
    scheduler_add_request(gateway, 101, NULL);
    
    // 2. İstek: Düşük öncelikli (u=5), artımlı (i=true)
    scheduler_add_request(gateway, 102, "u=5, i");
    
    // 3. İstek: En yüksek öncelikli (u=0)
    scheduler_add_request(gateway, 103, "u=0");
    
    // 4. İstek: "i" bayrağı önde, u=1
    scheduler_add_request(gateway, 104, "i, u=1");
    
    // 5. İstek: 101 ID'li istekle aynı öncelikte (u=3).
    // Ancak ondan daha geç geldiği için FIFO mantığıyla 101'den SONRA işlenmeli.
    scheduler_add_request(gateway, 105, "u=3");
    
    // 6. İstek: Geçersiz header syntax. Varsayılan değerlerle (u=3) devam etmeli.
    scheduler_add_request(gateway, 106, "invalid");

    // 7. İstek: Araya daha da kritik bir istek girelim (u=0)
    scheduler_add_request(gateway, 107, "u=0, i");

    printf("\n--- İstekler Isleniyor (Min-Heap Mantigi ile) ---\n");
    
    // Kuyrukta 7 istek var, hepsini sırayla çıkaralım
    for (int i = 0; i < 7; i++) {
        scheduler_process_next(gateway);
    }
    
    printf("\nBos kuyruktan isleme denemesi:\n");
    scheduler_process_next(gateway);

    // Kaynakları temizleyerek bellek sızıntısını önle (Memory freed)
    scheduler_destroy(gateway);
    
    printf("\nSimulasyon basariyla tamamlandi. Bellek sızıntısı yok.\n");
    
    return 0;
}
