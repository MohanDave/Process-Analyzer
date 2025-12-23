#include "pch.hxx"
#include "analyzer.hxx"
analyzer::analyzer(const std::map<DWORD, process_data>& data) {
    for (auto& p : data) processes_.push_back(p.second);
}

std::vector<process_data> analyzer::top_by_avg_cpu(int count) {
    std::vector<process_data> top_by_avg_cpu(processes_.begin(), processes_.end());
    std::sort(top_by_avg_cpu.begin(), top_by_avg_cpu.end(), [](const process_data& a, const process_data& b) {
        double avg_a = 0.0;
        for (const auto& s : a.samples) {
            avg_a += s.cpu_percent;
        }
        avg_a /= a.samples.size();
        double avg_b = 0.0;
        for (const auto& s : b.samples) {
            avg_b += s.cpu_percent;
        }
        avg_b /= b.samples.size();
        return avg_a > avg_b;
    });
    if (top_by_avg_cpu.size() > count) {
        top_by_avg_cpu.resize(count);
    }
    return top_by_avg_cpu;
}

std::vector<process_data> analyzer::top_by_memory_growth(int count) {
    std::vector<process_data> top_by_memory_growth = processes_;
    std::sort(top_by_memory_growth.begin(), top_by_memory_growth.end(), [](const process_data& a, const process_data& b) {
        return (a.final_memory_mb - a.initial_memory_mb) >
               (b.final_memory_mb - b.initial_memory_mb);
    });
    if (top_by_memory_growth.size() > count) {
        top_by_memory_growth.resize(count);
    }
    return top_by_memory_growth;
}

std::vector<process_data> analyzer::top_by_final_memory(int count) {
    std::vector<process_data> top_by_final_memory(processes_.begin(), processes_.end());
    std::sort(top_by_final_memory.begin(), top_by_final_memory.end(), [](const process_data& a, const process_data& b) {
        return a.final_memory_mb > b.final_memory_mb;
    });
    if (top_by_final_memory.size() > count) {
        top_by_final_memory.resize(count);
    }
    return top_by_final_memory;
}
