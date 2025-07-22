#ifndef GTR_H
#define GTR_H

#ifdef __cplusplus
extern "C" {
#endif

int gtr_init(const char *lang_override);
void gtr_free();
const char *gtr(const char *key);

#ifdef __cplusplus
}
#endif

#endif // GTR_H
