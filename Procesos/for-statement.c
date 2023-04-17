#include <stdio.h>
#define LOWER 0 /* LOWER LIMIT OF TABLE*/
#define UPPER 300 /* UPPER LIMIT */
#define STEP 20 /* STEP SIZE */

/* print Fahrenheit-Celsius table */
int main() {
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP) {
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    }
}