int strlen(const char* s, int len = 0)
{
    while (s[len]) len++;
    return len;
}

int strcmp(const char* s, const char* t)
{
    while (*s && *s == *t) s++, t++;
    return *s - *t;
}

void strcpy(char* dest, const char* src)
{
    while ((*dest++ = *src++));
}