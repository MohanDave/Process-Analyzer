#pragma once
#include "types.hxx"

class json_writer {
public:
    static void write(
        const std::vector<process_data>& cpu,
        const std::vector<process_data>& growth,
        const std::vector<process_data>& memory);
};
