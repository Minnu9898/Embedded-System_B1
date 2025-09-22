/*
17. Given a set of numbers where all elements occur an even number of times except one number, find the odd occurring number.
	XOR cancels duplicates
    🔎 Logic

XOR properties:

a ^ a = 0 → duplicates cancel out

a ^ 0 = a

XOR is commutative and associative

So, if all numbers occur even times except one, XOR-ing all numbers will cancel out all even duplicates and leave the odd-occurring number.
*/

#include <stdio.h>

int findOddOccurring(int arr[], int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res ^= arr[i]; // XOR all numbers
    }
    return res;
}

int main() {
    int arr[] = {2, 3, 5, 4, 5, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int odd = findOddOccurring(arr, n);
    printf("The odd occurring number is: %d\n", odd);

    return 0;
}