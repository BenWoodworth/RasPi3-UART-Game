
void Terminal::printStr(char* str) {
    for (int i = 0; str[i]; i++) {
        printChar(str[i]);
    }
}
