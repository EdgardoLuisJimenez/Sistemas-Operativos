/* Problema que consiste en sumar enteros que estan almacenados en un archivo
con formato plano
- El nombre del archivo debe ser enviado por linea de comando
- La salida debe indicar el tiempo que dura la operacion de lectura*/

#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void mostFrequent(int arr[], int n) {
    // Contar la frecuencia de cada valor en el arreglo ordenado
    int mostFreq = 0; // 2
    int mostFreqVal = arr[0]; // 2
    int freq = 1;// 2
    // 2 5 2 5 2 2 1
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i-1]) {
            freq++;
        } else {
            if (freq > mostFreq) {
                mostFreq = freq;
                mostFreqVal = arr[i-1];
            }
            freq = 1;
        }
    }

    // Comprobar el último valor
    if (freq > mostFreq) {
        mostFreq = freq;
        mostFreqVal = arr[n-1];
    }

    printf("El valor más frecuente es %d, que aparece %d veces.\n", mostFreqVal, mostFreq);
}


int main(int argc, char *argv[]) {

    // Lectura del archivo
    struct timespec startArchiveRead, endArchiveRead;
    double elapsedArchiveRead;
    clock_gettime(CLOCK_REALTIME, &startArchiveRead);

    int n_proc = atoi(argv[2]);
    FILE *file;

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    int size;
    int *array = NULL;
    fscanf(file, "%d", &size);
    array = (int *)malloc(size * sizeof(int));

    if (array == NULL) {
        printf("Error al reservar memoria\n");
        exit(1);
    }
    clock_gettime(CLOCK_REALTIME, &endArchiveRead);


    // Operacion de lectura y estimacion de la suma
    struct timespec startSum, endSum;
    double elapsedSum;
    clock_gettime(CLOCK_REALTIME, &startSum);

    long int sum = 0;
    for (int i = 0; i< size; i++) {
        fscanf(file, "%d", &array[i]);
        sum += array[i];
    }
    clock_gettime(CLOCK_REALTIME, &endSum);

    // Calculando la mediana
    struct timespec startMedian, endMedian;
    double elapsedMedian;
    clock_gettime(CLOCK_REALTIME, &startMedian);

    quickSort(array, 0, size - 1);

    int median = 0;
    if (size % 2 == 0) {
        median = (array[size/2] + array[(size/2) + 1]) / 2;
    } else {
        median = (array[size/2]);
    }

    clock_gettime(CLOCK_REALTIME, &endMedian);




    elapsedArchiveRead = (endArchiveRead.tv_sec - startArchiveRead.tv_sec) + ((endArchiveRead.tv_nsec - startArchiveRead.tv_nsec) / 1000000000.0);
    elapsedSum = (endSum.tv_sec - startSum.tv_sec) + ((endSum.tv_nsec - startSum.tv_nsec) / 1000000000.0);
    elapsedMedian = (endMedian.tv_sec - startMedian.tv_sec) + ((endMedian.tv_nsec - startMedian.tv_nsec) / 1000000000.0);

    printf("El tiempo de lectura del archivo es: %f Segundos\n", elapsedArchiveRead);
    printf("El tiempo de Sumatoria del archivo es: %f Segundos\n", elapsedSum);
    
    printf("El tiempo de calcular la mediana del archivo es: %f Segundos\n", elapsedMedian);

    struct timespec startMostFreq, endMostFreqVal;
    double elapsedMostFreqVal;
    clock_gettime(CLOCK_REALTIME, &startMostFreq);

    mostFrequent(array, size);

    clock_gettime(CLOCK_REALTIME, &endMostFreqVal);
    elapsedMostFreqVal = (endMostFreqVal.tv_sec - startMostFreq.tv_sec) + ((endMostFreqVal.tv_nsec - startMostFreq.tv_nsec) / 1000000000.0);

    printf("El tiempo de calcular el valor mas frecuente es: %f Segundos\n", elapsedMostFreqVal);
    printf("La mediana es: %d", median);

    fclose(file);
    free(array);


    return EXIT_SUCCESS;
}