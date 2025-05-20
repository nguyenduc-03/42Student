# 42Student – C Projects from 42 Berlin

[![LinkedIn – Nguyen Duc](https://img.shields.io/badge/LinkedIn-NguyenDuc-blue?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/duc-nguyen-20a9a2136/)
![Last Commit](https://img.shields.io/github/last-commit/nguyenduc-03/42Student?style=flat-square)
![Repo Created](https://img.shields.io/badge/Created-2024-lightgrey?style=flat-square)
![Languages](https://img.shields.io/github/languages/top/nguyenduc-03/42Student?style=flat-square)

Welcome to my journey at [42 Berlin](https://42berlin.de/). This repository is a collection of projects and exercises I worked on during the 42 piscine and beyond. These projects helped build my foundational knowledge in **C programming**, **memory management**, **problem-solving**, and **collaborative development using Git**.

---

## 📋 Table of Contents

1. [About This Repository](#-about-this-repository)
2. [Projects](#-projects)

   * [libft\_v4](#libft_v4)
   * [get\_new\_line](#get_new_line)
   * [ipc](#ipc)
   * [minitalk](#minitalk)
   * [ft\_printf](#ft_printf)
   * [push\_swap\_3](#push_swap_3)
   * [so\_long](#so_long)
   * [thread](#thread)
3. [Skills & Technologies](#-skills--technologies)
4. [Getting Started](#-getting-started)
5. [Building & Usage](#-building--usage)
6. [Contributing](#-contributing)
7. [Contact](#-contact)

---

## 📖 About This Repository

All code in this repository was written in **C** as part of the 42 Berlin curriculum. Each project addresses a specific challenge, from reimplementing standard library functions to creating a minimal message-passing system.

---

## 🚀 Projects

### libft\_v4

A custom implementation of common C standard library functions. Reinforced understanding of pointers, memory allocation, and library organization.

* **Key concepts**: pointer arithmetic, dynamic memory, linked lists
* **Lessons learned**: error handling, writing reusable code

---

### get\_new\_line

An implementation of the `get_next_line` function to read a file descriptor line by line.

* **Key concepts**: buffer management, static variables, file I/O
* **Lessons learned**: efficient I/O, handling edge cases (EOF, buffer remainder)

---

### ipc

A demonstration of inter-process communication using UNIX pipes and signals.

* **Key concepts**: pipes, signals, parent-child synchronization
* **Lessons learned**: low-level IPC, process forking, signal handling

---

### minitalk

A tiny client-server application that sends messages between processes using UNIX signals.

* **Key concepts**: bitwise operations, signal delivery, encoding/decoding
* **Lessons learned**: reliable message transfer, synchronization primitives

---

### ft\_printf

Reimplementation of the `printf` function supporting basic conversion specifiers.

* **Key concepts**: variadic functions, format parsing
* **Lessons learned**: deep dive into standard I/O, modular parsing logic

---

### push\_swap\_3

Sorting algorithm challenge: generate a sequence of operations to sort stacks using only allowed operations.

* **Key concepts**: stack operations, algorithm optimization
* **Lessons learned**: greedy vs. best-case strategies, step minimization

---

### so\_long

A simple 2D game where the player collects items and reaches an exit. Built using the MiniLibX graphics library.

* **Key concepts**: event handling, graphics rendering
* **Lessons learned**: real-time rendering loops, user input mapping

---

### thread

Exploration of multithreading in C using POSIX threads.

* **Key concepts**: pthreads, mutexes, race conditions
* **Lessons learned**: thread safety, synchronization mechanisms

---

## 🔧 Skills & Technologies

* **Languages**: C, Shell scripting
* **Tools**: GNU Make, Git
* **Concepts**: Memory management, pointers, data structures, concurrency, IPC, graphics (MiniLibX)

---

## 🛠️ Getting Started

1. **Clone the repository**:

   ```bash
   git clone git@github.com:nguyenduc-03/42Student.git
   ```
2. **Navigate** to the project directory:

   ```bash
   cd 42Student
   ```

---

## ⚙️ Building & Usage

Each project has its own subdirectory with a `Makefile`. To compile all projects at once:

```bash
make all
```

To compile a specific project, enter its folder and run:

```bash
make
```

Example (libft\_v4):

```bash
cd libft_v4
make
```

---

## 🤝 Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request for improvements.

---

## 📬 Contact

Feel free to reach out via [thaiduc0706@gmail.com](mailto:thaiduc0706@gmail.com) for any questions or feedback.
