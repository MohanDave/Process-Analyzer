#include "pch.hxx"
#include "process_collector.hxx"
#include "analyzer.hxx"
#include "json_writer.hxx"

int main() {
    process_collector c;
    c.collect_samples(10, 500);

    analyzer a(c.get_processes());
    json_writer::write(
        a.top_by_avg_cpu(3),
        a.top_by_memory_growth(3),
        a.top_by_final_memory(3));

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}
