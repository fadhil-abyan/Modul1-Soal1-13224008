/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2026/2027
 *   Modul               : Data manipulation, external files, structers, and dynamic arrays
 *   Hari dan Tanggal    : Rabu, 4 November 2026
 *   Nama (NIM)          : Muhammad Fadhil Abyan (13224008)
 *   Nama File           : soal1.c
 *   Deskripsi           : Kode program soal 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

typedef struct {
    char idSensor[256];
    char zona[256];
    float suhu;
} DataSensor;

float average(int n, DataSensor* a){
    if(n == 0) return 0;
    float sum = 0;
    for(int i = 0; i < n; i++){
        sum = sum + a[i].suhu;
    }
    return sum / (float) n;
}

void sort(int n, DataSensor* a){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1-i; j++){
            if(a[j].suhu < a[j+1].suhu){
                DataSensor temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
            else if(a[j].suhu == a[j+1].suhu){
                if(strcmp(a[j].idSensor, a[j+1].idSensor) > 0){
                    DataSensor temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }
            }
        }
    }
}

void printData(int n, DataSensor* a){
    for(int i = 0; i < n; i++){
        printf("%s %.2f\n", a[i].idSensor, a[i].suhu);
    }
}

void toLowString(char* str){
     while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int main(){
    char namaFile[256];
    char zonaTarget[256];

    DataSensor *dataSensor = malloc(INITIAL_CAPACITY * sizeof(DataSensor));
    int count = 0;
    int capacity = INITIAL_CAPACITY;

    char temp_idSensor[256];
    char temp_zona[256];
    float temp_suhu;
    
    scanf("%255s %255s", namaFile, zonaTarget);

    FILE *file =  fopen(namaFile, "r");
    if (file == NULL) { 
        free(dataSensor);
        return -1; 
    }
    while(fscanf(file, " %255[^,],%255[^,],%f", temp_idSensor, temp_zona, &temp_suhu) == 3){
        if(strcmp(toLowString(temp_zona), toLowString(zonaTarget))==0){
            strcpy(dataSensor[count].idSensor, temp_idSensor);
            strcpy(dataSensor[count].zona, temp_zona);
            dataSensor[count].suhu = temp_suhu;
            count++;

            if(count >= capacity){
                capacity = 2* capacity;
                dataSensor = realloc(dataSensor, capacity * sizeof(DataSensor));
            }
        }
        if (count == 0){
            printf("999\n");
            return 0;
        }
    }

    fclose(file);
    
    sort(count, dataSensor);
    float average_value = average(count, dataSensor);
    printData(count, dataSensor);
    printf("AVERAGE %.2f", average_value);

    return 0;
}
