# Aether - File Explorer Simulator

## About The Project
Aether is a visual, File Explorer Simulator built entirely in C/C++. Utilizing the Raylib library for rendering, this project provides a graphical user interface (GUI) to navigate and interact with file directories. It simulates a virtual file system environment where users can click on folder icons to open them, view their contents, and track their current path in real-time.

## Features
* **Graphical Interface:** Built completely from scratch using Raylib.
* **Interactive Directories:** Clickable folder icons that dynamically update the view to show internal contents.
* **Path Tracking:** A live-updating address bar displaying the current directory path.
* **Custom Assets:** Custom icons and fonts mapped to backend file structures.
* **Pure C/C++ Backend:** Efficient file and directory handling using standard C++ libraries.

## Built With
* [C++](https://cplusplus.com/) - Core application logic and backend.
* [Raylib](https://www.raylib.com/) - Rendering, window management, and input detection.

## Getting Started

### Prerequisites
To compile and run this project, you will need:
* A C++ compiler (GCC, Clang, or MSVC)
* [Raylib](https://github.com/raysan5/raylib) installed and configured on your system.
* [CMake / Make] (Optional: specify your build system here)

### Installation & Compilation
1. Clone the repository:
   ` ` `bash
   git clone https://github.com/akulaggarwal12/File-Explorer-Simulator.git
   ` ` `

2. Compiling the Project
Depending on your operating system and setup, choose the compilation method that works best for you.

**Option A: Terminal Compilation (Linux)**
Ensure you have Raylib installed system-wide, then run:
```bash
g++ main.cpp -o file_explorer -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**Option B: Terminal Compilation (Windows via MinGW)**
Assuming you have the Raylib `include` and `lib` folders set up in your compiler path or project directory:
```bash
g++ main.cpp -o file_explorer.exe -O2 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
```

**Option C: Terminal Compilation (macOS)**
Using Clang with Raylib installed via Homebrew (`brew install raylib`):
` ` `bash
clang++ main.cpp -o file_explorer -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
` ` `

**Option D: Using CMake (Recommended for Cross-Platform)**
If you are using CMake to manage your build, run the following commands:
```bash
mkdir build
cd build
cmake ..
make
```
3. Run the Application
Once compiled successfully, execute the generated file from your terminal to launch the simulator.

**On Linux or macOS:**
```bash
./file_explorer
```

**On Windows:**
` ` `cmd
file_explorer.exe
` ` `
