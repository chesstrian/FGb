typedef void CUtils;

#ifdef __cplusplus
extern "C" {
#endif

CUtils *str_new(char *str);
void str_print(const CUtils *u);
char *str_value(const CUtils *u);
char *str_replace(const CUtils *u, char *search, char *replacement);
void str_delete(CUtils *u);

#ifdef __cplusplus
}
#endif
