#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TEST 100
const char *answers[] = {"y", "yes", "n", "no"};

void operate(int multiple, int start) {

    printf("start:\n");
    int n = start;
    for (int i = 0; i < TEST; i++) {
        printf("%i -> %i ", n, n*n);
        n += multiple;

        if (((n*n) % multiple == 0) && (n % multiple == 0)) {
            printf("TRUE\n");
        } else {
            printf("FALSE\n");
        }
    }

    return;
}

int main() {

    printf("Give me a number: ");
    int n;
    scanf("%i", &n);
    printf("If n is divisible by %i, then n^2 too.\n", n);

    while (1) {
        printf("Start test? [y/n] ");
        char ans[3];
        scanf("%s", ans);

        //convert ans to lower case
        for (int i = 0; i < strlen(ans); i++) {
            ans[i] = tolower(ans[i]);
        }

        //compare with possible answers
        int found = 0;
        for (int i = 0; i < sizeof(answers) / sizeof(answers[0]); i++) {
            if (strcmp(ans, answers[i]) == 0) {
                if (ans[0] == 'n') {
                    return 0;
                }
                found++;
                break;
            }
        }
        if (found != 0) {
            break;
        } else {
            printf("Incorrect response. Try again.\n");
        }
    }

    //array to store values
    printf("Starting value: ");
    int m;
    scanf("%i", &m);

    //generate numbers
    operate(n, m);

    return 0;
}