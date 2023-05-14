#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void selectionSort(int* arr, int n);
void swap(int* a, int* b);
void display(int* arr, int n);

int main() {
    int number, iter = 0;
    struct timeval start, stop;
    clock_t ticks;

    printf("Enter the Size of the Array: ");
    scanf("%d", &number);
    int Arr[number];

    srand((unsigned)time(NULL));
    for (; iter < number; iter++) {
        printf("Element No. %d: ", iter + 1);
        Arr[iter] = rand() % 100;
        printf("%d\n", Arr[iter]);
    }

    ticks = clock();
    gettimeofday(&start, NULL);

    #pragma omp parallel shared(Arr, number)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < number; i++) {
            int min_idx = i;
            for (int j = i + 1; j < number; j++) {
                if (Arr[j] < Arr[min_idx])
                    min_idx = j;
            }
            if (min_idx != i)
                swap(&Arr[i], &Arr[min_idx]);
        }
    }

    gettimeofday(&stop, NULL);
    ticks = clock() - ticks;

    double burst_time = ((double)ticks) / CLOCKS_PER_SEC;
    double exec_time = (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000000.0;

    display(Arr, number);

    FILE* fp;
    fp = fopen("Timings.txt", "a");
    fprintf(fp, "OpenMP Burst Time: %lf seconds\n", burst_time);
    fprintf(fp, "OpenMP Execution Time: %lf seconds\n\n", exec_time);
    fclose(fp);

    return 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display(int* arr, int n) {
    printf("ARRAY: {");
    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            printf("%d, ", arr[i]);
        else
            printf("%d}\n\n", arr[i]);
    }
}

