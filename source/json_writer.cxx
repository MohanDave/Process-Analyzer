#include "pch.hxx"
#include "json_writer.hxx"
void json_writer::write(
    const std::vector<process_data>& cpu,
    const std::vector<process_data>& growth,
    const std::vector<process_data>& memory) {

    nlohmann::json j;
    j["scan_duration_seconds"] = 5;
    j["sample_count"] = 10;

    for (auto& p : cpu) {
        double avg = 0;
        for (auto& s : p.samples) avg += s.cpu_percent;
        avg /= p.samples.size();
        j["top_cpu"].push_back({
            {"name", p.name},
            {"pid", p.pid},
            {"average_cpu_percent", avg},
            {"final_memory_mb", p.final_memory_mb}
        });
    }

    for (auto& p : growth) {
        j["top_memory_growth"].push_back({
            {"name", p.name},
            {"pid", p.pid},
            {"initial_memory_mb", p.initial_memory_mb},
            {"final_memory_mb", p.final_memory_mb},
            {"growth_mb", p.final_memory_mb - p.initial_memory_mb}
        });
    }

    for (auto& p : memory) {
        j["top_memory_usage"].push_back({
            {"name", p.name},
            {"pid", p.pid},
            {"memory_mb", p.final_memory_mb},
            {"thread_count", p.thread_count}
        });
    }

    std::ofstream f("analysis.json");
    f << j.dump(4);
}
