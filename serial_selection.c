#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

void selectionSort(int* A, int n);
void swap(int* a, int* b);
void display(int* arr, int n);

int main() {
    int number, iter = 0;
    
    printf("Enter the Size of the Array: ");
    scanf("%d", &number);
    
    int* Arr = (int*)malloc(number * sizeof(int));

    srand((unsigned)time(NULL));

    for (; iter < number; iter++) {
        printf("Element No. %d: ", iter + 1);
        Arr[iter] = rand() % 100;
        printf("%d\n", Arr[iter]);
    }

    clock_t start, stop;
    double bstart = clock();
    start = clock();
    selectionSort(Arr, number);
    stop = clock();
    double bstop = clock();

    display(Arr, number);

    double burst_time = (bstop - bstart) / CLOCKS_PER_SEC;
    double execution_time = (double)(stop - start) / CLOCKS_PER_SEC;

    printf("Burst Time: %lf\n", burst_time);
    printf("Execution Time: %lf seconds\n", execution_time);

    FILE* fp;
    fp = fopen("Timings.txt", "a");
    fprintf(fp, "Serial Burst Time: %lf\n", burst_time);
    fprintf(fp, "Serial Execution Time: %lf seconds\n", execution_time);
    fclose(fp);

    free(Arr);

    return 0;
}

void display(int* arr, int n) {
    printf("ARRAY: {");
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            printf("%d, ", *(arr + i));
        }
        else {
            printf("%d}\n\n", *(arr + i));
        }
    }
}

void selectionSort(int* A, int n) {
    for (int startpos = 0; startpos < n - 1; startpos++) {
        int minpos = startpos;
        for (int i = startpos + 1; i < n; ++i) {
            if (A[i] < A[minpos]) {
                minpos = i;
            }
        }
        if (minpos != startpos)
            swap(&A[startpos], &A[minpos]);
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
