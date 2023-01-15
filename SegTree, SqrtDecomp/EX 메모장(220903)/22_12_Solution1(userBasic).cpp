////////// ***** user.cpp ***** //////////
char* document[1000000];
int  size = 0;

int strlen(char* str, int i = 0) {
    for (; str[i]; ++i) {}
    return i;
}

void strcpy(char* dest, char* src) {
    while (*dest++ = *src++);
}

void append(char* str) {
    document[size] = new char[strlen(str) + 1];
    strcpy(document[size], str);
    size++;
}

void insert(int line, char* str) {
    for (int c = size; c > line; c--) {
        document[c] = document[c - 1];
    }
    document[line] = new char[strlen(str) + 1];
    strcpy(document[line], str);
    size++;
}

void erase(int line) {
    delete document[line];
    for (int c = line; c < size; c++) {
        document[c] = document[c + 1];
    }
    size--;
}

char* linestring(int line) {
    return document[line];
}