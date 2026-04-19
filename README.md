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
