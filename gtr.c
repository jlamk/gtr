#include "gtr.h"

#include <jansson.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <locale.h>
#endif


static json_t *g_translation_obj = NULL;

static const char *get_system_language() {
    static char lang[16] = {0};

#ifdef _WIN32
    LANGID lid = GetUserDefaultUILanguage();

    char lang_code[9] = {0};
    char country_code[9] = {0};

    if (!GetLocaleInfoA(MAKELCID(lid, SORT_DEFAULT), LOCALE_SISO639LANGNAME, lang_code, sizeof(lang_code)))
        strcpy(lang_code, "en");
    if (!GetLocaleInfoA(MAKELCID(lid, SORT_DEFAULT), LOCALE_SISO3166CTRYNAME, country_code, sizeof(country_code)))
        strcpy(country_code, "US");

    snprintf(lang, sizeof(lang), "%s_%s", lang_code, country_code);
#else
    const char *lang_env = getenv("LANG");
    if (!lang_env) lang_env = setlocale(LC_ALL, "");
    if (!lang_env || lang_env[0] == '\0')
        return "en_US";

    strncpy(lang, lang_env, sizeof(lang) - 1);
    lang[sizeof(lang) - 1] = '\0';

    char *dot = strchr(lang, '.');
    if (dot) *dot = '\0'; // remove charset como UTF-8

    char *at = strchr(lang, '@');
    if (at) *at = '\0'; // remove modificadores como @latin

#endif

    return lang;
}


int gtr_init(const char *lang_override) {
    const char *lang = lang_override ? lang_override : get_system_language();
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "ts/%s.json", lang);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(stderr, "Translation file not found: %s\n", filepath);
        return -1;
    }

    json_error_t error;
    g_translation_obj = json_loadf(file, 0, &error);
    fclose(file);

    if (!g_translation_obj || !json_is_object(g_translation_obj)) {
        fprintf(stderr, "Failed to parse translation JSON: %s\n", error.text);
        json_decref(g_translation_obj);
        g_translation_obj = NULL;
        return -2;
    }

    return 0;
}

const char *gtr(const char *key) {
    if (!g_translation_obj) return key;

    json_t *value = json_object_get(g_translation_obj, key);
    if (value && json_is_string(value)) {
        return json_string_value(value);
    }

    return key;
}

void gtr_free() {
    if (g_translation_obj) {
        json_decref(g_translation_obj);
        g_translation_obj = NULL;
    }
}
