# Tower of Hanoi (Using `<graphics.h>`)

A simple **Tower of Hanoi** visualization in C++ using the legacy graphic.h library . The program animates the disks moving between three pegs with smooth vertical and horizontal transitions.

## Table of Contents
- [About the Code](#about-the-code)
- [Requirements](#requirements)
- [How to Compile](#how-to-compile)
  - [Using MinGW (with WinBGI)](#using-mingw-with-winbgi)
- [Usage](#usage)

## About the Code

- **Language**: C++  
- **Graphics**: Uses **WinBGI** or a similar implementation of `<graphics.h>`.  
- **Main Functions**:
  1. Prompts the user for the number of disks (up to 12).  
  2. Draws the pegs and a base line.  
  3. Uses the classic **Tower of Hanoi** recursive algorithm to move disks from peg 0 to peg 2.  
  4. Animates each disk move in a simple step-by-step manner with delays.

## Requirements
1. Windows environment (for `<graphics.h>` / WinBGI).  
2. A compiler or IDE that supports `<graphics.h>`:
   - **Dev-C++** with WinBGI built-in.  
   - **MinGW** (GCC on Windows) with WinBGI installed manually.  

## How to Compile

### Using MinGW (with WinBGI)
1. Install WinBGI (or a `<graphics.h>` library) for MinGW.  
   - This typically involves placing `graphics.h` in `MinGW\include` and a library file (e.g., `libbgi.a`) in `MinGW\lib`.  
2. Open a terminal (Command Prompt, PowerShell) in the folder containing your `.cpp` file.  
3. Compile with:
   g++ visualization.cpp -o visualization.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
4. Run the program: .\visualization.exe

##Usage
1. Execute the compile program
2. Enter the number of disks
3. A graphic appears showing:
  - 3 pegs in a row, with the disks on the left peg
  - Disks moving step by step to the right peg
6. Press any key to close the window



