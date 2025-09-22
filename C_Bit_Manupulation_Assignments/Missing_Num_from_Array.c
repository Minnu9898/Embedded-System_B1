#include <stdio.h>

int findMissingNumber(int arr[], int n) {
    int xor1 = 0, xor2 = 0;

    // XOR of numbers from 1 to n+1
    for (int i = 1; i <= n + 1; i++)
        xor1 ^= i;

    // XOR of all elements in array
    for (int i = 0; i < n; i++)
        xor2 ^= arr[i];

    // Missing number
    return xor1 ^ xor2;
}

int main() {
    int arr[] = {1, 2, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int missing = findMissingNumber(arr, n);
    printf("Missing number = %d\n", missing);

    return 0;
}