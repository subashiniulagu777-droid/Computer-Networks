#include <stdio.h>
#include <ctype.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        char str[1001];
        int sum = 0;
        scanf("%s", str);
        for (int i = 0; str[i] != '\0'; i++) {
            if (isdigit(str[i])) {
                sum += str[i] - '0';
            }
        }
        printf("%d\n", sum);
    }

    return 0;
}