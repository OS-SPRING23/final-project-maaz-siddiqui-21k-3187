#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>

void Cocktail_Sort(int *A, int size) {
    int start = 0;
    int end = size - 1;
    while (start != (size / 2)) {
        #pragma omp parallel for
        for (int i = start; i < end; i++) {
            if (A[i] > A[i + 1]) {
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }

        #pragma omp parallel for
        for (int j = end - 1; j >= start; j--) {
            if (A[j] < A[j - 1]) {
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
            }
        }

        start++;
        end--;
    }
}

void Filling(double Start, double End, double Total) {
    FILE *ptr;
    ptr = fopen("Project_Times.txt", "a+");
    if (ptr == NULL) {
        printf("Unable to Open File");
        exit(1);
    } else {
        double total = (End - Start) / CLOCKS_PER_SEC;
        fprintf(ptr, "Burst Time Taken By open-mp_Cocktail_Sort is %lf\n", total);
        fprintf(ptr, "Total Time Taken By open-mp_Cocktail_Sort is %lf\n", Total);
    }
    fclose(ptr);
}

int main(void) {
    srand(time(NULL));
    int n;
    struct timeval stop, start;
    printf("Enter The Size of Array: ");
    scanf("%d", &n);
    int *ptr = (int *)calloc(n, sizeof(int));
    printf("Enter The Elements of the Array\n");
    for (int i = 0; i < n; i++) {
        ptr[i] = rand() % n;
    }

    double Start = omp_get_wtime();
    gettimeofday(&start, NULL);
    Cocktail_Sort(ptr, n);
    gettimeofday(&stop, NULL);
    double End = omp_get_wtime();
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    double Total = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    Filling(Start, End, Total);
}

