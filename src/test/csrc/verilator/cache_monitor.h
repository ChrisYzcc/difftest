// Analysing cache by accesing pins

#ifndef CACHE_MONITOR_H
#define CACHE_MONITOR_H

#include "VSimTop.h"
#include "VSimTop___024root.h"

#include <cstdint>
#include <cstdlib>

class CacheMonitor {
public:
    uint32_t dcache_mshr_states[16];
    uint32_t unalloc_num, prefetch_num, mixed_num, other_num;
    const uint32_t MSHR_STATE_UNALLOC = 0;
    const uint32_t MSHR_STATE_PREFETCH = 1;
    const uint32_t MSHR_STATE_MIXED = 2;
    const uint32_t MSHR_STATE_OTHER = 3;

    const char *dcache_mshr_log = "./rpt/dcache_mshr.log";

    FILE *log_fp = nullptr;

    CacheMonitor();
    ~CacheMonitor();

    void collect_dcache_mshr_states(VSimTop *dut_ptr);

    void update_dcache_mshr_stats(){
        unalloc_num = 0;
        prefetch_num = 0;
        mixed_num = 0;
        other_num = 0;
        for (int i = 0; i < 16; i++){
            if (dcache_mshr_states[i] == MSHR_STATE_UNALLOC){
                unalloc_num++;
            } else if (dcache_mshr_states[i] == MSHR_STATE_PREFETCH){
                prefetch_num++;
            } else if (dcache_mshr_states[i] == MSHR_STATE_MIXED){
                mixed_num++;
            } else {
                other_num++;
            }
        }
    }

    void conditional_log_dcache_mshr_stats(int cycle){
        if (prefetch_num + mixed_num + other_num > 0){
            log_dcache_mshr_stats(cycle);
        }
    }

    void log_dcache_mshr_stats(int cycle){
        fprintf(log_fp, "Cycle %d: Unalloc: %d, Prefetch: %d, Mixed: %d, Other: %d\n", cycle, unalloc_num, prefetch_num, mixed_num, other_num);
    }
};


#endif