#include <stdio.h>
#include <time.h>
#include <wait.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

clock_t start, stop;
int linearSearch(int* A, int n, int tos);
void* selectionSort(void* input);
void swap(int* a, int* b);
void display(int* arr, int n);
#define MAX_THREAD 4

struct sortingArgs{
    int *arr;
    int n;
};

int main(){
    int noDuplication = 0;
    pthread_t threads[MAX_THREAD];
    int number, iter = 0, find;

    struct sortingArgs Args;
    
    printf("\nEnter the Size of the Array: ");    
    scanf("%d", &number);
    Args.n = number;
    int Arr[number];
    Args.arr = Arr;
    for(; iter<number; iter++){
        printf(/*\nEnter */"\nElement No. %d: ", iter + 1);
        Arr[iter] = rand() % 100;  
        printf("%d", Arr[iter]);
    }
    
    start = clock();
    for(int i = 0; i < MAX_THREAD; i++){
        pthread_create(&threads[i], NULL, selectionSort, &Args);
    }
    
    for(int i = 0; i < MAX_THREAD; i++){
        pthread_join(threads[i], NULL);
    }
    stop = clock();
    
    double burst_time = ((double)stop - (double)start) / CLOCKS_PER_SEC;
    double exec_time = (double)(stop - start) / (double)(CLOCKS_PER_SEC * MAX_THREAD);
    
    display(Arr, number);
    FILE* fp;
    fp = fopen("Timings.txt", "a");
    fprintf(fp, "Multi-threading Burst Time: %lf seconds\n", burst_time);
    fprintf(fp, "Multi-threading Execution Time: %lf seconds\n\n", exec_time);    
    fclose(fp);
}

void* selectionSort(void* input){
    struct sortingArgs *Arg = (struct sortingArgs*) input;
    int *A;
    A = Arg->arr;
    int n = Arg->n;
    
    for(int startpos =0; startpos < n-1; startpos++){
        int maxpos = startpos;
        for(int i=startpos +1; i< n; ++i){
            if(A[i] < A[maxpos]){
                maxpos = i;
            }
        }
        if(maxpos != startpos){
            swap(&A[startpos], &A[maxpos]);
        }
    }
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display(int* arr, int n){
    printf("\nARRAY: {");
    for(int i = 0; i < n; i++){
        if(i != n - 1){
            printf("%d, ", *(arr + i));
        } else{
            printf("%d}\n\n", *(arr + i));
        }
    }
}

