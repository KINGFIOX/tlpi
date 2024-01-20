#include <stdio.h>

#ifndef len
#define len 5
#endif

int main(void)
{
    printf("please enter %d nums:\n", len);
    int a[len];
    int sum = 0;
    for (int i = 0; i < len; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    float average = (float)sum / len;
    printf("sum = %d\naverage = %.2f\n", sum, average);

    int even[len] = { 0 };
    int evenTop = -1;
    int odd[len] = { 0 };
    int oddTop = -1;

    for (int i = len - 1; i >= 0; i--) {
        if ((i + 1) % 2 == 1) {
            odd[++oddTop] = a[i];
        } else {
            even[++evenTop] = a[i];
        }
    }

    printf("even order num: ");
    while (evenTop >= 0) {
        printf("%d ", even[evenTop--]);
    }
    printf("\n");
    printf("odd order num: ");
    while (oddTop >= 0) {
        printf("%d ", odd[oddTop--]);
    }

    /*    printf("odd order num: ");
        for (int i = 0; i < len; i++) {
            if (i % 2 == 0) {
                printf("%d ", a[i]);
            }
        }

        printf("\neven order num: ");
        for (int i = 0; i < len; i++) {
            if (i % 2 == 1) {
                printf("%d ", a[i]);
            }
        }
    */

    return 0;
}