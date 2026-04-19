# rfc9213_scheduler
A modular API Gateway Priority Request Scheduler developed in C, utilizing a Min-Heap data structure and fully compliant with RFC 9213 (Extensible HTTP Priorities) standards.
# RFC 9213 Compliant API Gateway Priority Request Scheduler

This project is an API Gateway request scheduler developed in C, fully compliant with **RFC 9213 (Extensible HTTP Priorities)** standards. The system organizes incoming HTTP requests using a high-performance **Min-Heap (Priority Queue)** data structure instead of a standard FIFO array.

## 🚀 About the Project
API Gateways can receive thousands of requests per second. Processing these requests based on their priority level is critical for optimizing system resources. The main objectives of this project are:
1. Parse HTTP Headers according to RFC 9213 standards (`urgency` and `incremental` parameters).
2. Insert and extract requests from the queue with an **O(log n)** time complexity.
3. Design a clean, scalable, and memory-leak-free system using a modular C architecture (Header/Source separation).

## ⚙️ Technical Specifications & Algorithm

* **Data Structure:** Requests are stored and managed within a **Min-Heap**.
* **Priority Criteria 1 (Urgency):** According to RFC 9213, the `urgency` value ranges from 0 (highest priority) to 7 (lowest priority). The Min-Heap algorithm ensures that the request with the lowest urgency value is always at the root node.
* **Priority Criteria 2 (Timestamp):** To maintain a stable sorting algorithm (Stable FIFO), if multiple requests share the same urgency value, the system evaluates their arrival time (`timestamp`). The request that arrived first is processed first.
* **Time Complexity:** Both insertion (`heap_insert`) and extraction (`heap_extract_min`) operations run in **O(log n)** time.

## 📂 Project Architecture

The project strictly follows a modular architecture, separating interfaces (`.h`) from implementations (`.c`).

```text
rfc9213_scheduler/
├── include/
│   ├── heap.h         # Min-Heap data structure definitions
│   ├── parser.h       # RFC 9213 header parser interface
│   ├── request.h      # Core Request object structure
│   └── scheduler.h    # Gateway scheduler interface
├── src/
│   ├── heap.c         # Heapify algorithms implementation
│   ├── parser.c       # String manipulation (strtok) and parsing logic
│   ├── scheduler.c    # Queue management and memory allocation
│   └── main.c         # Test simulation
├── Makefile           # Automated build rules
└── README.md
🛠️ Build and Run
To compile and run this project on your local machine, ensure you have gcc and make installed.
1-Clone the repository:
git clone [https://github.com/YOUR_USERNAME/rfc9213-scheduler.git](https://github.com/YOUR_USERNAME/rfc9213-scheduler.git)
cd rfc9213-scheduler
2-Compile the project:make
3-Run the simulation:
./rfc9213_scheduler
📊 Sample Output & Test Scenario
Complex requests with varying priorities are routed to the system and successfully sorted/processed via the Min-Heap logic. (Output from the simulation):
=== RFC 9213 API Gateway Priority Request Scheduler ===

--- Istekler Gateway'e Geliyor ---
[Gateway] Istek alindi: ID=101 | Header: "(varsayilan)" -> (urgency=3, incremental=false)
[Gateway] Istek alindi: ID=102 | Header: "u=5, i" -> (urgency=5, incremental=true)
[Gateway] Istek alindi: ID=103 | Header: "u=0" -> (urgency=0, incremental=false)
[Gateway] Istek alindi: ID=104 | Header: "i, u=1" -> (urgency=1, incremental=true)
[Gateway] Istek alindi: ID=105 | Header: "u=3" -> (urgency=3, incremental=false)
[Gateway] Istek alindi: ID=106 | Header: "invalid" -> (urgency=3, incremental=false)
[Gateway] Istek alindi: ID=107 | Header: "u=0, i" -> (urgency=0, incremental=true)

--- Istekler Isleniyor (Min-Heap Mantigi ile) ---
[Scheduler] ISLENIYOR: ID=103 | Urgency=0 | Incremental=false | Gelis Sirasi(TS)=2
[Scheduler] ISLENIYOR: ID=107 | Urgency=0 | Incremental=true | Gelis Sirasi(TS)=6
[Scheduler] ISLENIYOR: ID=104 | Urgency=1 | Incremental=true | Gelis Sirasi(TS)=3
[Scheduler] ISLENIYOR: ID=101 | Urgency=3 | Incremental=false | Gelis Sirasi(TS)=0
[Scheduler] ISLENIYOR: ID=105 | Urgency=3 | Incremental=false | Gelis Sirasi(TS)=4
[Scheduler] ISLENIYOR: ID=106 | Urgency=3 | Incremental=false | Gelis Sirasi(TS)=5
[Scheduler] ISLENIYOR: ID=102 | Urgency=5 | Incremental=true | Gelis Sirasi(TS)=1

Simulasyon basariyla tamamlandi. Bellek sizintisi yok.
👨‍💻 Author
Name: Berat [Your Last Name]

University: Kirklareli University, Faculty of Engineering
---

### 3. İngilizce Git Commit Mesajları
Kodlarını parçalar halinde gönderirken terminalde (veya GitHub Desktop'ta) kullanabileceğin profesyonel İngilizce commit mesajları:

1. `git add include/request.h` 
   * **Commit:** `feat: define Request struct and RFC 9213 parameters`
2. `git add src/parser.c include/parser.h`
   * **Commit:** `feat: add HTTP Priority header parser module`
3. `git add src/heap.c include/heap.h`
   * **Commit:** `feat: implement Min-Heap algorithm and compare_requests logic`
4. `git add src/scheduler.c include/scheduler.h src/main.c`
   * **Commit:** `feat: complete Scheduler interface and main test simulation`
5. `git add Makefile README.md`
   * **Commit:** `docs: add project documentation and Makefile`

Bu dokümantasyonla birlikte projene bakan herhangi bir yabancı mühendis, sistem programlama ve veri yapıları konusundaki teknik yetkinliğini anında fark edecektir! Başka bir çeviri veya düzenleme istersen buradayım.
