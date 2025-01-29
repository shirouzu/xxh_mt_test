// xxh3 multi-threaded total performance test by H.Shirouzu at 2025-01-29

#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <vector>
#include <cstdio>

#define XXH_INLINE_ALL
#define XXH_VECTOR XXH_AVX2
#include "xxh3.h"

#define GiB (1024LL * 1024 * 1024)
#define THR_MAX     24
#define THR_BUFSZ   (1 * GiB)
#define TOTAL_BUFSZ (THR_MAX * THR_BUFSZ)
#define COUNT       10

std::atomic_bool        StartFlag(false);
std::condition_variable Cv;
std::mutex              CvMtx;

void worker_proc(char *buf, size_t size, int count)
{
    XXH128_hash_t   digest;
    XXH3_state_t    *xxh3State = XXH3_createState();

    { // wait for StartFlag == true
        std::unique_lock<std::mutex> lock(CvMtx);
        Cv.wait(lock, [&] { return StartFlag.load(); });
    }

    for (int i=0; i < count; i++) {
        XXH3_128bits_reset(xxh3State);
        XXH3_128bits_update(xxh3State, buf, size);
        digest = XXH3_128bits_digest(xxh3State);
    }
}

void main_task(int max_thr, char *buf, size_t buf_size, int count)
{
    if (THR_BUFSZ != buf_size / max_thr) abort();

    std::vector<std::thread>    workers;

    for (int i=0; i < max_thr; i++)
        workers.emplace_back(worker_proc, buf + i * THR_BUFSZ, THR_BUFSZ, count);

    auto start = std::chrono::high_resolution_clock::now();
    StartFlag.store(true);
    Cv.notify_all();

    for (auto &tr : workers)
        tr.join();

    auto    end = std::chrono::high_resolution_clock::now();
    auto    elaps = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    printf("Theads=%d: %.2fGiB/s (%lldms for %lldGiB)\n",
        max_thr, (double)buf_size * count * 1000 / GiB / elaps, elaps, buf_size * count / GiB);
}

int main()
{
    printf("Prepare buffer...");
    auto    buf = std::make_unique<char[]>(TOTAL_BUFSZ);
    memset(buf.get(), 0xA5, TOTAL_BUFSZ);
    printf("end\n");

    for (int i=THR_MAX; i >= 1; i--)
        main_task(i, buf.get(), (size_t)i * THR_BUFSZ, COUNT);
}

