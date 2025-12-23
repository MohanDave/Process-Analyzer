\## Process Performance Analyzer Coding Test



\### Overview

You will build a command-line tool that monitors system processes for 5 seconds, then exports a clean analysis of the top 3 performance offenders to a JSON on disk.



\### Requirements



\*\*1. Data Collection (5 second scan)\*\*



When you run the tool, it should:

\- Take samples every 500ms for 5 seconds (10 samples total)

\- Track for each process:

&nbsp; - Process name (executable name, e.g., "chrome.exe") and PID

&nbsp; - CPU usage per sample

&nbsp; - Memory usage per sample (working set in MB)

&nbsp; - Thread count



\*\*2. Analysis \& Output\*\*



After 5 seconds, export `analysis.json` with:

\- \*\*Top 3 by Average CPU\*\* - Processes with highest average CPU usage

\- \*\*Top 3 by Memory Growth\*\* - Processes that increased memory the most

\- \*\*Top 3 by Final Memory\*\* - Processes using the most memory at end



\*\*3. JSON Format\*\*



```json

{

&nbsp; "scan\_duration\_seconds": 5,

&nbsp; "sample\_count": 10,

&nbsp; "timestamp": "2024-11-16T15:30:25Z",

&nbsp; 

&nbsp; "top\_cpu": \[

&nbsp;   {

&nbsp;     "name": "chrome.exe",

&nbsp;     "pid": 1234,

&nbsp;     "average\_cpu\_percent": 25.3,

&nbsp;     "final\_memory\_mb": 512.5

&nbsp;   },

&nbsp;   // ... 2 more

&nbsp; ],

&nbsp; 

&nbsp; "top\_memory\_growth": \[

&nbsp;   {

&nbsp;     "name": "firefox.exe",

&nbsp;     "pid": 5678,

&nbsp;     "initial\_memory\_mb": 200.0,

&nbsp;     "final\_memory\_mb": 285.0,

&nbsp;     "growth\_mb": 85.0

&nbsp;   },

&nbsp;   // ... 2 more

&nbsp; ],

&nbsp; 

&nbsp; "top\_memory\_usage": \[

&nbsp;   {

&nbsp;     "name": "system",

&nbsp;     "pid": 4,

&nbsp;     "memory\_mb": 1024.5,

&nbsp;     "thread\_count": 256

&nbsp;   },

&nbsp;   // ... 2 more

&nbsp; ]

}

```



\*\*4. Code Quality Requirements\*\*



\*\*(CRITICAL)  Comment your code explaining:\*\*

\- WHY you chose specific data structures

\- HOW you calculate CPU percentage

\- WHY you used specific Windows API functions

\- HOW you track processes across samples (matching PIDs)

\- Any edge cases you handle



\*\*Example:\*\*

```cpp

// Using a map<PID, process\_data> to track processes across samples

// because processes can start/die during monitoring. We need to

// match PIDs from sample to sample to calculate deltas correctly.

std::map<DWORD, process\_data> tracked\_processes;

```



\### Project Structure Requirements



\*\*DO NOT put everything in one main.cxx file.\*\* Organize your code properly with multiple files and headers.



\*\*Example structure\*\* (you can organize however you want, just keep it clean):



```

analyzer/

├── analyzer.sln                 

├── analyzer.vcxproj             

├── vcpkg.json                   // For nlohmann-json dependency

├── source/

│   ├── pch.hxx                  

│   ├── pch.cxx                  

│   ├── main.cxx                 

│   ├── process\_collector.hxx    

│   ├── process\_collector.cxx

│   ├── analyzer.hxx             

│   ├── analyzer.cxx

│   ├── json\_writer.hxx          

│   ├── json\_writer.cxx

│   └── types.hxx                

├── output/

│   └── analysis.json            

└── README.md

```



\*\*Key points:\*\*

\- Separate concerns into multiple files (don't dump everything in main)

\- Use `.cxx` for source files, `.hxx` for headers

\- Use \*\*snake\_case\*\* for all naming (variables, functions, files, etc.)



\### Technical Requirements



\*\*Build System:\*\*

\- Use \*\*Visual Studio solution (.sln)\*\* - NOT CMake

\- Visual Studio 2022 or 2026 Insiders

\- Configuration: x64 Release and Debug



\*\*Dependencies:\*\*

\- Use \*\*nlohmann-json\*\* via \*\*vcpkg.json\*\*

\- Set up vcpkg integration properly in your project



\*\*Precompiled Headers:\*\*

\- Create `pch.hxx` and `pch.cxx`

\- Include commonly used headers:

&nbsp; - `<Windows.h>`

&nbsp; - `<iostream>`

&nbsp; - `<vector>`

&nbsp; - `<map>`

&nbsp; - `<string>`

&nbsp; - `<algorithm>`

&nbsp; - Any other frequently used headers

\- Configure project to use precompiled headers



\*\*Code Style:\*\*

\- Use \*\*snake\_case\*\* for everything (functions, variables, files, classes, etc.)

\- Example: `process\_data`, `calculate\_cpu\_usage()`, `json\_writer.cxx`



\*\*Windows APIs you'll need:\*\*

\- `CreateToolhelp32Snapshot()` - enumerate processes

\- `OpenProcess()` - get process handle

\- `GetProcessMemoryInfo()` - memory stats

\- `GetProcessTimes()` - CPU calculation

\- `<psapi.h>`, `<tlhelp32.h>`



\### Deliverables



1\. \*\*Complete Visual Studio solution\*\*

&nbsp;  - analyzer.sln and analyzer.vcxproj

&nbsp;  - vcpkg.json with nlohmann-json dependency

&nbsp;  - Properly configured with PCH

&nbsp;  - Compiles in Release and Debug



2\. \*\*Source code\*\* with proper organization

&nbsp;  - Multiple files, clean separation

&nbsp;  - Well-commented explaining your decisions

&nbsp;  - snake\_case naming throughout



3\. \*\*Example `analysis.json`\*\* from your system



4\. \*\*README.md\*\* explaining:

&nbsp;  - Your design approach (2-3 paragraphs)

&nbsp;  - How you organized the code and why

&nbsp;  - Time spent



\### What We're Evaluating



\*\*Project organization\*\* - Multiple files, clean structure (not one giant file)  

\*\*Visual Studio setup\*\* - Correct .sln, vcpkg.json, PCH configured  

\*\*Works correctly\*\* - Accurate data, top 3 make sense  

\*\*Well-commented\*\* - Shows you understand what you're doing  

\*\*Clean code\*\* - Readable, maintainable, snake\_case  

\*\*Error handling\*\* - Doesn't crash on edge cases  

&nbsp;\*\*README\*\* - Clear explanation of your approach





