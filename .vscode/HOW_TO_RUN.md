# How to Build and Run in VSCode

## Quick Start

### Method 1: Build and Run (Easiest - Recommended)
1. Press `Cmd+Shift+P` (Mac) or `Ctrl+Shift+P` (Windows/Linux)
2. Type "Run Task"
3. Select **"Build and Run brainfck"**
   - This will automatically compile with C++17 and run the program in one step!

### Method 2: Build Only
1. Press `Cmd+Shift+B` (Mac) or `Ctrl+Shift+B` (Windows/Linux)
   - This compiles `brainfck.cpp` with C++17
2. Then run manually: `./brainfck`

### Method 3: Using Debug/Run (F5)
1. Press `F5` or click the Run icon in the sidebar
2. Select "Build and Run brainfck"
   - This will compile and run with debugging support

## What's Configured

- **Compiler**: clang++ with C++17 standard (`-std=c++17`)
- **Source**: `brainfck.cpp`
- **Output**: `brainfck` executable
- **Working Directory**: Project root

## Files Created

- `.vscode/tasks.json` - Build and run tasks
- `.vscode/launch.json` - Debug configuration
- `.vscode/settings.json` - C++ standard and compiler settings

## Keyboard Shortcuts

- `Cmd+Shift+B` / `Ctrl+Shift+B` - Build
- `Cmd+Shift+P` → "Run Task" → "Build and Run brainfck" - Build and Run
- `F5` - Debug (builds first)

