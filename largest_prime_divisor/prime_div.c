#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int obtainDivisor(int n) {
    int largest_prime_divisor = 0;
    
    do {
        for (int d = 2; d <= n; d++) {
            if (n % d == 0) {
                largest_prime_divisor = d;
                while (n % d == 0) {
                    n /= d;
                }
            }
        }
    } while (n > 1);
    
    return largest_prime_divisor;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Incorrect usage. Try: .\\prime_div.exe min_value max_value\n");
        return 1;
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    int range = max - min + 1;
    char **divisors = malloc(sizeof(char *) * range);

    if (divisors == NULL) {
        printf("Error.\n");
        return 1;
    }

    for (int i = 0; i < range; i++) {
        int divisor = obtainDivisor(min + i);
        
        if (divisor == min + i) {
            divisors[i] = strdup("prime");
        } else {
            divisors[i] = malloc(sizeof(char) * 20);
            sprintf(divisors[i], "%d", divisor);
        }

        printf("For the number %d, %s\n", min + i, divisors[i]);
    }

    for (int i = 0; i < range; i++) {
        free(divisors[i]);
    }

    free(divisors);
    return 0;
}