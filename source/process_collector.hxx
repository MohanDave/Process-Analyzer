#pragma once
#include "types.hxx"

class process_collector {
public:
    void collect_samples(int sample_count, int interval_ms);
    const std::map<DWORD, process_data>& get_processes() const;

private:
    std::map<DWORD, process_data> tracked_processes_;
    ULONGLONG get_total_cpu_time(FILETIME kernel, FILETIME user) const;
};
