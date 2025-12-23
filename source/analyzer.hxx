#pragma once
#include "types.hxx"

class analyzer {
public:
    analyzer(const std::map<DWORD, process_data>& data);
    std::vector<process_data> top_by_avg_cpu(int count);
    std::vector<process_data> top_by_memory_growth(int count);
    std::vector<process_data> top_by_final_memory(int count);

private:
    std::vector<process_data> processes_;
};
