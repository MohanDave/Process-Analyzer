
# Process Performance Analyzer

## Design Approach

This tool is designed to monitor all running processes on a Windows system for 5 seconds, sampling every 500ms. For each process, it tracks CPU usage, memory usage (working set in MB), and thread count. The tool analyzes the collected data to identify the top 3 processes in three categories: average CPU usage, memory growth, and final memory usage. The results are exported to a cleanly structured JSON file.

### Code Organization
- **main.cxx**: Entry point, orchestrates collection, analysis, and output.
- **process_collector.hxx/cxx**: Handles process enumeration and sampling using Windows APIs. Tracks processes by PID across samples.
- **analyzer.hxx/cxx**: Analyzes collected data to find top offenders in each category.
- **json_writer.hxx/cxx**: Outputs the analysis in the required JSON format using nlohmann-json.
- **types.hxx**: Defines data structures for process samples and tracking.
- **pch.hxx/cxx**: Precompiled headers for faster builds and consistent includes.

### Why This Structure?
- **Separation of concerns**: Each file has a clear responsibility, making the codebase maintainable and testable.
- **Snake_case naming**: Ensures consistency and readability.
- **Extensive comments**: Explain data structure choices, API usage, and edge case handling.

### Time Spent
- Planning and design: 30 minutes
- Coding and refactoring: 2 hours
- Testing and documentation: 30 minutes

## How to Build and Run
1. Open the solution in Visual Studio 2022 or later.
2. Ensure vcpkg integration is enabled and nlohmann-json is installed.
3. Build in x64 Debug or Release mode.
4. Run the executable. The output will be written to `output/analysis.json`.

---

See `TestGuidelines.md` for further details.
