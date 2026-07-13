<h1 align="center">
    <img alt="cub3d" width="200px" src="https://raw.githubusercontent.com/NataliaMatias2024/42-project-badges/main/badges/cub3dm.png">
</h1>

# 🕹️ Cub3D - @42SP
**Score:** 115/100 ✅ (100% Mandatory + Selected Bonus Features)

This repository contains a 3D graphics engine developed in C using the MLX42 (Codam) library for the `cub3d` project of the [42 São Paulo](https://www.42sp.org.br/) curriculum.

🤝 **Collaboration:** This project was developed in collaboration with [mkitano](https://github.com/mikitano), who was responsible for the core execution and raycasting engine, while my primary focus was on architecting the parser and data validation module.

The project implements rendering through Raycasting (inspired by the classic Wolfenstein 3D), allowing first-person exploration of a maze from a strictly validated `.cub` map file.

## 🚀 Objectives

> - Render a 3D environment from a two-dimensional map using the Raycasting algorithm and DDA (Digital Differential Analyzer).
> - Implement a secure parser module to validate enclosed maps (using DFS/Flood Fill), texture paths, and hexadecimal color conversions.
> - Optimize screen rendering and shading by manipulating memory with atomic buffers (`uint64_t`) and Bitwise operations.
> - Create a seamless interface with smooth controls, including vector-based movement, mouse rotation, and a dynamic minimap.

## 🛠️ Technologies & Concepts
<div align="left">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="Linux" />
</div>

> - **Raycasting & Vectors:** Perpendicular distance calculation and camera projection to transform 2D grids into an illusion of 3D depth.
> - **MLX42 (Codam):** Utilization of the modernized 42 graphics library, supporting native manipulation of the RGBA format and `.png` textures.
> - **Bitwise Operations:** Direct bit manipulation (`<<`, `|`, `&`) to compose solid RGBA colors and apply lighting/shading effects to walls.
> - **Resource Management (FD & Leaks):** Strict control of the File Descriptors lifecycle and GNL calls to shield the program against memory leaks (Valgrind).

## 📁 Project Structure

```bash
cub3D/
├── include/
├── src/             # Project source code (.c divided into parser and engine)
├── lib/
│   ├── libft/       # Foundation libraries (Libft / Get_Next_Line)
│   └── MLX42/       # Graphics library (Codam) compiled via CMake
├── textures/
├── maps/            # .cub files containing configurations and map layouts
├── Makefile         # Compilation automation (all, clean, fclean, re)
└── README.md        # This file     
```

## ⚙️ Compilation & Usage
### Requirements
- Linux
- C compiler (gcc or clang)
- CMake (required by MLX42)
- GLFW dependencies

## 1. Prerequisites
On Linux (WSL/Ubuntu), you must install the GLFW and CMake dependencies required by MLX42:
```bash
$ sudo apt-get update$ sudo apt-get install build-essential libglfw3-dev cmake
```

## 2. Clone
```bash
$ git clone https://github.com/mikitano/cub3D
$ cd cub3D
```

## 3. Compilation
In the root directory of the project, run the Makefile to generate the cub3D executable:
```bash
$ make
```

## 4. Execution
The program requires a valid .cub file path as an argument. The file must contain texture paths, colors, and the map layout.
```bash
# Running a standard map
$ ./cub3D maps/valid_map.cub
```

## 🗺️ Map Format

The engine expects a `.cub` configuration file containing:

- North texture
- South texture
- East texture
- West texture
- Floor color
- Ceiling color
- Map layout

Example:

```text
NO textures/north.png
SO textures/south.png
WE textures/west.png
EA textures/east.png

F 100,100,100
C 40,100,255

111111111
100000001
10N000001
100000001
111111111
```

## 🎮 Interactive Controls

| Key | Action |
|------|--------|
| W | Move forward |
| S | Move backward |
| A | Strafe left |
| D | Strafe right |
| SHIFT | Run |
| N | Show minimap |
| ← / → | Rotate camera |
| M | Active mouse rotate |
| Mouse | Rotate camera (bonus) |
| ESC | Exit game |

## AI Usage
Artificial Intelligence was used as a learning and productivity tool during the development of this project.

It assisted with:

- understanding raycasting mathematics;
- discussing rendering algorithms;
- explaining graphics concepts;
- improving documentation.

All design decisions, implementation, debugging, testing, and final code integration were carried out manually.

## 🧠 Lessons Learned

- Modular Architecture: The importance of isolating the parsing module (validation, data structuring, and file reading) from the execution engine, strictly adhering to the single responsibility principle.
- Applied Vector Math: Demystifying the DDA algorithm and applying trigonometry calculations (sine and cosine) to rotate direction matrices and camera planes.
- Bitwise Operations: Deep understanding of how the machine stores colors in 32-bit blocks and how to convert classic RGB into the transparency standards (Alpha) required by modern graphics systems.
- Memory Resilience: Structuring safe error-handling paths that clear static variables and close file descriptors, ensuring 0 leaks regardless of where the program might fail.

