/* upper.c */
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    int ch;

    while((ch = getchar()) != EOF) {
        // 小写转大写
        putchar(toupper(ch));
    }

    return 0;
}
