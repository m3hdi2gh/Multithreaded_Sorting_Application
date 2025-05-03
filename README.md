# Multithreaded Sorting (​C / pthreads)

A compact demo that shows how to use **POSIX threads** to sort an integer list concurrently:

1. **Split** – the input array is divided into two equal halves.  
2. **Sort** – two worker threads run an *in‑place* insertion‑sort on their respective halves.  
3. **Merge** – a third thread merges the two sorted halves into a final, fully‑sorted array.  
4. **Output** – the main thread prints the result.

> Total lines of code: **≈ 100**

---

## Build & Run

```bash
# clone the repo
git clone https://github.com/m3hdi2gh/Multithreaded_Sorting_Application.git
cd Multithreaded_Sorting_Application

# compile (GCC + pthread)
gcc -pthread multithread_sort.c -o mt_sort

# run
./mt_sort        # enter 10 integers when prompted
````

Tested on **GCC 13+** (Linux, macOS). No external dependencies beyond `pthread.h`.

---
