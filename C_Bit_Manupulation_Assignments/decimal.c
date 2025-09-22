#include <stdio.h>

void printBinary(int num) {
    int n = sizeof(num) * 8; // total bits in integer

    for (int i = n - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

int main() {
    int num;
    printf("Enter a decimal number: ");
    scanf("%d", &num);

    printf("Binary representation: ");
    printBinary(num);

    return 0;
}