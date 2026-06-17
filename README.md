# JString 

A lightweight, header-only C library that brings Java-style string utilities to C — no dependencies, no fuss.

---

## Why JString?

Working with strings in C is powerful but verbose. JString gives you familiar Java-like utilities (`contains`, `startsWith`, `split`, `trim` and more) built on top of a zero-copy `String_View` — so you get convenience without sacrificing performance.

---

## Installation

JString is header-only, so there's nothing to compile or link.

1. Clone the repo (or just download the header):
```bash
git clone https://github.com/your-username/jstring.git
```

2. Copy `jstring.h` into your project.

3. In **one** `.c` file, define the implementation before including:
```c
#define JSTRING_IMPLEMENTATION
#include "jstring.h"
```

4. In all other files, include normally:
```c
#include "jstring.h"
```

