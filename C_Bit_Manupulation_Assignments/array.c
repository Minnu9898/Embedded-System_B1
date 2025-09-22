#include <stdio.h>

void findTwoUnique(int arr[], int n) {
    int xorAll = 0;
    for (int i = 0; i < n; i++) {
        xorAll ^= arr[i];
    }

    // Find rightmost set bit
    int setBit = xorAll & ~(xorAll - 1);

    int num1 = 0, num2 = 0;

    // Divide numbers into two groups
    for (int i = 0; i < n; i++) {
        if (arr[i] & setBit)
            num1 ^= arr[i];  // XOR of group 1
        else
            num2 ^= arr[i];  // XOR of group 2
    }

    printf("The two non-repeating elements are: %d and %d\n", num1, num2);
}

int main() {
    int arr[] = {2, 4, 7, 9, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    findTwoUnique(arr, n);

    return 0;
}