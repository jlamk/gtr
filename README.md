
# 🌐 GTR

**GTR** is a lightweight C library that loads translations from JSON files based on system or user language. 

---

## 📦 Features

- Detects system language (Windows/Linux)
- Loads translations from JSON files (e.g. `ts/en_US.json`)
- Simple API: `gtr("key")`
- Optional language override
- Fallback to key if translation is not found

---

## Dependencies

[jansson](https://digip.org/jansson/)

## 🔧 Installation

1.

```bash
  mkdir build
  cmake ..
  make
  sudo make install
```

2.
Link GTR to your application:
Add -lgtr -ljansson to your linker flags:

3.
 Create a ts/ folder in the same directory as your app executable, and add translation files like en_US.json, pt_BR.json, etc.

---

## 🗂️ JSON Format

Translation files are regular JSON objects. Example:

pt_BR.json
```json
{
  "Welcome": "Bem-vindo",
  "Exit": "Sair",
  "Error occurred": "Ocorreu um erro",
  "Please wait": "Por favor, aguarde"
}
```

en_US.json
```json
{
  "Welcome": "Welcome",
  "Exit": "Exit",
  "Error occurred": "Error occurred",
  "Please wait": "Please wait"
}
```

es_ES.json
```json
{
  "Welcome": "Bienvenido",
  "Exit": "Salir",
  "Error occurred": "Ocurrió un error",
  "Please wait": "Por favor, espera"
}
```

fr_FR.json
```json
{
  "Welcome": "Bienvenue",
  "Exit": "Quitter",
  "Error occurred": "Une erreur est survenue",
  "Please wait": "Veuillez patienter"
}
```

---

## 🚀 Usage

### Initialize:

```c
#include <gtr.h>
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

## 📁 Folder Structure Example

```
project/
├── main.c
└── build/
    ├── App_Executable
    └── ts/
        ├── en_US.json
        └── pt_BR.json
```
