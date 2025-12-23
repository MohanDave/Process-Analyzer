#pragma once
#include "pch.hxx"

struct process_sample {
    double cpu_percent;
    double memory_mb;
};

struct process_data {
    process_data() : initial_memory_mb(0.0), final_memory_mb(0.0), thread_count(0) {}
    std::string name;
    DWORD pid;
    std::vector<process_sample> samples;
    double initial_memory_mb;
    double final_memory_mb;
    DWORD thread_count;
};
