#include <stdio.h>

int xor1ToN(int n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        case 3: return 0;
    }
    return 0; // never reaches here
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    printf("XOR from 1 to %d = %d\n", n, xor1ToN(n));
    return 0;
}



// // XOR from 1 to n
// int xor1ToN(int n) {
//     switch (n % 4) {
//         case 0: return n;
//         case 1: return 1;
//         case 2: return n + 1;
//         case 3: return 0;
//     }
//     return 0;
// }

// // XOR of range L to R
// int xorRange(int L, int R) {
//     return xor1ToN(R) ^ xor1ToN(L - 1);
// }

// int main() {
//     int L, R;
//     printf("Enter L and R: ");
//     scanf("%d %d", &L, &R);

//     printf("XOR from %d to %d = %d\n", L, R, xorRange(L, R));
//     return 0;
// }