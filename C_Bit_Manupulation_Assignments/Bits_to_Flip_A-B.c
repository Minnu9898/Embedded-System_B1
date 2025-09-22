/*

23.Count Number of bits to be flipped to convert A to B
	Accept values of A and B
	Do XOR of A and B 
	Check how many 1 are there in A^B (n=n&(n-1)) --->count ++ 
	That much time flip needed
*/

#include <stdio.h>

// Function to count set bits using Brian Kernighan’s method
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // clear the rightmost set bit
        count++;
    }
    return count;
}

// Function to count bits to flip to convert A to B
int bitsToFlip(int A, int B) {
    return countSetBits(A ^ B);
}

int main() {
    int A, B;
    printf("Enter A and B: ");
    scanf("%d %d", &A, &B);

    printf("Number of bits to flip: %d\n", bitsToFlip(A, B));
    return 0;
}
