#include "pch.hxx"
#include "process_collector.hxx"

ULONGLONG process_collector::get_total_cpu_time(FILETIME kernel, FILETIME user) const {
    ULARGE_INTEGER k{}, u{};
    k.LowPart = kernel.dwLowDateTime;
    k.HighPart = kernel.dwHighDateTime;
    u.LowPart = user.dwLowDateTime;
    u.HighPart = user.dwHighDateTime;
    return k.QuadPart + u.QuadPart;
}

void process_collector::collect_samples(int sample_count, int interval_ms) {
    SYSTEM_INFO sys{};
    GetSystemInfo(&sys);
    int cpu_count = sys.dwNumberOfProcessors;

    std::map<DWORD, ULONGLONG> last_cpu;

    for (int i = 0; i < sample_count; ++i) {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 pe{};
        pe.dwSize = sizeof(pe);

        if (Process32First(snap, &pe)) {
            do {
                HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
                if (!proc) continue;

                FILETIME c, e, k, u;
                if (!GetProcessTimes(proc, &c, &e, &k, &u)) {
                    CloseHandle(proc);
                    continue;
                }

                ULONGLONG total = get_total_cpu_time(k, u);
                ULONGLONG delta = total - last_cpu[pe.th32ProcessID];
                last_cpu[pe.th32ProcessID] = total;

                PROCESS_MEMORY_COUNTERS pmc{};
                GetProcessMemoryInfo(proc, &pmc, sizeof(pmc));
                double mem_mb = pmc.WorkingSetSize / (1024.0 * 1024.0);

                double cpu = (delta / 100000.0) / (interval_ms * cpu_count);

                auto& p = tracked_processes_[pe.th32ProcessID];
                p.pid = pe.th32ProcessID;
#ifdef UNICODE
                {
                    std::wstring wname = pe.szExeFile;
                    int size = WideCharToMultiByte(CP_UTF8, 0, wname.c_str(), -1, nullptr, 0, nullptr, nullptr);
                    if (size > 0) {
                        std::string name(size - 1, '\0');
                        WideCharToMultiByte(CP_UTF8, 0, wname.c_str(), -1, &name[0], size, nullptr, nullptr);
                        p.name = name;
                    } else {
                        p.name.clear();
                    }
                }
#else
                p.name = pe.szExeFile;
#endif
                p.thread_count = pe.cntThreads;
                p.samples.push_back({ cpu, mem_mb });

                if (i == 0) p.initial_memory_mb = mem_mb;
                p.final_memory_mb = mem_mb;

                CloseHandle(proc);
            } while (Process32Next(snap, &pe));
        }
        CloseHandle(snap);
        Sleep(interval_ms);
    }
}

const std::map<DWORD, process_data>& process_collector::get_processes() const {
    return tracked_processes_;
}
