
# 🌐 GTR - Simple C Translation Loader

**GTR** is a lightweight C library that loads translations from JSON files based on system or user language. 

---

## 📦 Features

- Detects system language (Windows/Linux)
- Loads translations from JSON files (e.g. `ts/en_US.json`)
- Simple API: `gtr("key")`
- Optional language override
- Fallback to key if translation is not found

---

## 🔧 Installation

1. Add `gtr.h` and `gtr.c` to your project.
2. Link against the Jansson library:
   ```bash
   gcc your_app.c gtr.c -ljansson -o your_app
   ```

3. Create a folder named `ts/` in your project directory and add translation files named like `en_US.json`, `pt_BR.json`, etc.

---

## 🗂️ JSON Format

Translation files are regular JSON objects. Example:

```json
{
  "Hello": "Olá",
  "File Not Found!": "Arquivo Não Encontrado!",
  "Version %d.%d.%d": "Versão %d.%d.%d",
  "Your Name Is %s": "Seu Nome é %s"
}
```

---

## 🚀 Usage

### Initialize:

```c
#include "gtr.h"
#include <stdio.h>

int main() {
    if (gtr_init(NULL) != 0) {
        fprintf(stderr, "Failed to load translations\n");
        return 1;
    }

    printf("%s\n", gtr("Hello"));  // Output: Olá

    printf(gtr("Version %d.%d.%d"), 1, 2, 3);  // Output: Versão 1.2.3
    printf("\n");

    const char *name = "Lucas";
    printf(gtr("Your Name Is %s"), name);  // Output: Seu Nome é Lucas
    printf("\n");

    fprintf(stderr, "%s\n", gtr("File Not Found!"));  // Output: Arquivo Não Encontrado!

    gtr_free();
    return 0;
}

```

### With language override:

```c
gtr_init("pt_BR"); // Forces Portuguese (Brazil)
```

---

## 🧠 API

```c
int gtr_init(const char *lang_override);
```
- Initializes the translation system.
- Loads the file `ts/LANG.json` where LANG is either from system or overridden.
- Returns `0` on success, `< 0` on failure.

```c
const char *gtr(const char *key);
```
- Looks up the translation for `key`.
- Returns the original `key` if not found.

```c
void gtr_free();
```
- Frees memory used by the translation object.

---

## 🖥️ System Language Detection

- **Windows**: Uses `GetUserDefaultUILanguage()`
- **Linux/Unix**: Uses `LANG` environment variable or `setlocale(LC_ALL, "")`

---

## 📁 Folder Structure Example

```
project/
├── gtr.h
├── gtr.c
├── main.c
└── ts/
    ├── en_US.json
    └── pt_BR.json
```
