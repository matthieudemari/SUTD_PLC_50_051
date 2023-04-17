
#include <stdio.h>

int multiply(int a, int b) {
    return a * b;
}

int main() {
    int a = 5;
    int b = 3;
    int c = 7;
    int sum = 0;
    int i;

    for (i = 0; i < 10; i++) {
        sum += multiply(a, b);
        sum += c;
    }

    printf("%d\n", sum);
    return 0;
}

