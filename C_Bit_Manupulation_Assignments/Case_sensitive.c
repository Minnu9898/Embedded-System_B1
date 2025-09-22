#include <stdio.h>

char toLowerCase(char ch) {
    // works only if ch is uppercase A–Z
    return (ch | 0x20);
}



char toUpperCase(char K) {
    // works only if ch is lowercase a–z
    return (K &~0x20);
}


char invertCase(char J) {
    // Works for alphabets only
    if ((J >= 'A' && J <= 'Z') || (J >= 'a' && J <= 'z'))
        return J ^ 0x20;
    else
        return J;  // non-alphabet remains unchanged
}



int main() {
    char c,K,J;
    printf("Enter an uppercase character: ");
    scanf(" %c", &c);
      printf("\nEnter a lowercase character: ");
    scanf(" %c", &K);

    printf("Lowercase: %c\n", toLowerCase(c));
   
    printf("\nUppercase: %c\n", toUpperCase(K));

    printf("Enter a character to Invert: ");
    scanf(" %c", &J);

    printf("Inverted case: %c\n", invertCase(J));
     return 0;
    
}