# Derleyici ve Bayraklar (Compiler & Flags)
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# Klasörler (Directories)
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Kaynak Dosyalar ve Obje Dosyaları
# src/ içindeki tüm .c dosyalarını otomatik bulur
SRCS = $(wildcard $(SRC_DIR)/*.c)
# src/%.c dosyalarını obj/%.o dosyalarına dönüştürür
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Çıktı Dosyası Adı (Binary Name)
TARGET = rfc9213_scheduler

# Varsayılan Hedef (Default Target)
all: $(OBJ_DIR) $(TARGET)

# Obje Klasörünü Oluştur (Create Object Directory)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Bağlama Aşaması (Linking) - Obje dosyalarını birleştirip çalıştırılabilir dosya yapar
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Derleme Aşaması (Compiling) - .c dosyalarını .o dosyalarına çevirir
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Temizleme (Cleanup) - Derlenmiş dosyaları siler
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Derlenmiş dosyalar temizlendi."

# Phony hedefleri (Gerçek dosya olmayan komutlar)
.PHONY: all clean
