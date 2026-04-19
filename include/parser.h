#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include <stdbool.h>

// HTTP Priority header'ını ayrıştırmak için fonksiyon
// priority_header: Örnek -> "u=1, i" veya "u=5"
// urgency: Çıkarılan u değeri (varsayılan 3 atanır)
// incremental: Çıkarılan i değeri (varsayılan false atanır)
void parse_priority_header(const char* priority_header, uint8_t *urgency, bool *incremental);

#endif // PARSER_H
