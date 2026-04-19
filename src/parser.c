#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void parse_priority_header(const char* priority_header, uint8_t *urgency, bool *incremental) {
    // RFC 9213'e göre varsayılan değerler
    *urgency = 3;
    *incremental = false;

    if (priority_header == NULL) {
        return; // Header gelmediyse varsayılanlarda bırak
    }

    // String üzerinde arama yapmak için kopyasını alıyoruz (orijinali değiştirmemek için)
    char buffer[256];
    strncpy(buffer, priority_header, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    // Virgülle ayrılmış parçalara (token) ayırıyoruz
    char* token = strtok(buffer, ",");
    while (token != NULL) {
        // Baştaki ve sondaki boşlukları atlamak için basit bir işaretçi öteleme
        while (*token == ' ') token++;

        if (strncmp(token, "u=", 2) == 0) {
            // "u=" ile başlıyorsa urgency değerini al
            int u_val = atoi(token + 2);
            if (u_val >= 0 && u_val <= 7) {
                *urgency = (uint8_t)u_val;
            }
        } 
        else if (strcmp(token, "i") == 0 || strcmp(token, "i=?1") == 0) {
            // "i" bulunursa artımlı işleme doğrudur
            *incremental = true;
        }

        token = strtok(NULL, ",");
    }
}
