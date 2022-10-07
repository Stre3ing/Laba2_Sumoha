// Лаба №2 Задание №2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Лаба 2 Задание 2 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>

//сортировка методом Шелла
void ShellSort(int n, int mass[])
{
    int i, j, step;
    int tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = mass[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mass[j - step])
                    mass[j] = mass[j - step];
                else
                    break;
            }
            mass[j] = tmp;
        }
}
void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}
void Save(FILE* F, double result_sh, double result_qs, double result_qsort)
{
    fprintf(F, "%5.3f|%5.3f|%5.3f|", result_sh, result_qs, result_qsort);
    return;
}
int comp(const void* a, const void* b)
{
    int data_1 = *(int*)a;
    int data_2 = *(int*)b;
    if (data_1 < data_2) return -1;
    else if (data_1 == data_2) return 0;
    else return 1;

}

int main()
{
    SetConsoleCP(1251);     //русификация
    SetConsoleOutputCP(1251);
    int N_r[3] = { 100000, 500000, 1000000 };
    char n_file[50];
    FILE* F;
    printf("Введите имя файла, в который будут записывать данные: ");
    scanf("%s", n_file);
    F = fopen(n_file, "w");
    if (n_file == NULL)
    {
        printf("Ошибка открытия файла");
        _getch();
        return 0;
    }
    fprintf(F, "%3s|%17d|%17d|%17d|\n"," ", N_r[0], N_r[1], N_r[2]);
    fprintf(F, "%3s|%5s|%5s|%5s|%5s|%5s|%5s|%5s|%5s|%5s|\n"," ", "sh", "qs", "qsort", "sh", "qs", "qsort", "sh", "qs", "qsort");
    //выделение памяти под массив
    int* Sh;
    int* Qs;
    int* Qsort;
    fprintf(F, "%3s|", "r");
    for (int j = 0; j < 3; j++)
    {
        Sh = (int*)malloc(N_r[j] * sizeof(int));
        Qs = (int*)malloc(N_r[j] * sizeof(int));
        Qsort = (int*)malloc(N_r[j] * sizeof(int));
        for (int i = 0; i < N_r[j]; i++)
        {
            Sh[i] = rand() % 1001 - 1000;
            Qs[i] = rand() % 1001 - 1000;
            Qsort[i] = rand() % 1001 - 1000;
        }
        clock_t start_sh, stop_sh, start_qs, stop_qs, start_qsort, stop_qsort;
        start_sh = clock();
        ShellSort(N_r[j], Sh);
        stop_sh = clock();
        start_qs = clock();
        qs(Qs, 0, N_r[j] - 1);
        stop_qs = clock();
        start_qsort = clock();
        qsort(Qsort, N_r[j], sizeof(int), comp);
        stop_qsort = clock();
        double result_sh = (double)(stop_sh - start_sh) / 1000;
        double result_qs = (double)(stop_qs - start_qs) / 1000;
        double result_qsort = (double)(stop_qsort - start_qsort) / 1000;
        Save(F, result_sh, result_qs, result_qsort);
        free(Sh);
        free(Qs);
        free(Qsort);
    }

    fprintf(F, "\n%3s|", "d");
    for (int j = 0; j < 3; j++)
    {
        int Max = 1000000, razn = 1;
        Sh = (int*)malloc(N_r[j] * sizeof(int));
        Qs = (int*)malloc(N_r[j] * sizeof(int));
        Qsort = (int*)malloc(N_r[j] * sizeof(int));
        for (int i = 0; i < N_r[j]; i++)
        {
            Sh[i] = Max - razn;
            Qs[i] = Max - razn;
            Qsort[i] = Max - razn;
            Max -= razn;
        }
        clock_t start_sh, stop_sh, start_qs, stop_qs, start_qsort, stop_qsort;
        start_sh = clock();
        ShellSort(N_r[j], Sh);
        stop_sh = clock();
        start_qs = clock();
        qs(Qs, 0, N_r[j] - 1);
        stop_qs = clock();
        start_qsort = clock();
        qsort(Qsort, N_r[j], sizeof(int), comp);
        stop_qsort = clock();
        double result_sh = (double)(stop_sh - start_sh) / 1000;
        double result_qs = (double)(stop_qs - start_qs) / 1000;
        double result_qsort = (double)(stop_qsort - start_qsort) / 1000;
        Save(F, result_sh, result_qs, result_qsort);
        free(Sh);
        free(Qs);
        free(Qsort);
    }

    fprintf(F, "\n%3s|", "u");
    for (int j = 0; j < 3; j++)
    {
        Sh = (int*)malloc(N_r[j] * sizeof(int));
        Qs = (int*)malloc(N_r[j] * sizeof(int));
        Qsort = (int*)malloc(N_r[j] * sizeof(int));
        int razn = 1, Min = 0;
        for (int i = 0; i < N_r[j]; i++)
        {
            Sh[i] = Min + razn;
            Qs[i] = Min + razn;
            Qsort[i] = Min + razn;
            Min += razn;
        }
        clock_t start_sh, stop_sh, start_qs, stop_qs, start_qsort, stop_qsort;
        start_sh = clock();
        ShellSort(N_r[j], Sh);
        stop_sh = clock();
        start_qs = clock();
        qs(Qs, 0, N_r[j] - 1);
        stop_qs = clock();
        start_qsort = clock();
        qsort(Qsort, N_r[j], sizeof(int), comp);
        stop_qsort = clock();
        double result_sh = (double)(stop_sh - start_sh) / 1000;
        double result_qs = (double)(stop_qs - start_qs) / 1000;
        double result_qsort = (double)(stop_qsort - start_qsort) / 1000;
        Save(F, result_sh, result_qs, result_qsort);
        free(Sh);
        free(Qs);
        free(Qsort);
    }

    fprintf(F, "\n%3s|", "ud");
    for (int j = 0; j < 3; j++)
    {
        Sh = (int*)malloc(N_r[j] * sizeof(int));
        Qs = (int*)malloc(N_r[j] * sizeof(int));
        Qsort = (int*)malloc(N_r[j] * sizeof(int));
        int Max = 1000000, razn = 1, Min = 0;
        for (int i = 0; i < N_r[j]; i++)
        {
            if (i < N_r[j] / 2)
            {
                Sh[i] = Min + razn;
                Qs[i] = Min + razn;
                Qsort[i] = Min + razn;
                Min += razn;
            }
            else
            {
                Sh[i] = Max - razn;
                Qs[i] = Max - razn;
                Qsort[i] = Max - razn;
                Max -= razn;
            }
        }
        clock_t start_sh, stop_sh, start_qs, stop_qs, start_qsort, stop_qsort;
        start_sh = clock();
        ShellSort(N_r[j], Sh);
        stop_sh = clock();
        start_qs = clock();
        qs(Qs, 0, N_r[j] - 1);
        stop_qs = clock();
        start_qsort = clock();
        qsort(Qsort, N_r[j], sizeof(int), comp);
        stop_qsort = clock();
        double result_sh = (double)(stop_sh - start_sh) / 1000;
        double result_qs = (double)(stop_qs - start_qs) / 1000;
        double result_qsort = (double)(stop_qsort - start_qsort) / 1000;
        Save(F, result_sh, result_qs, result_qsort);
        free(Sh);
        free(Qs);
        free(Qsort);
    }
    printf("Данные сохранены в %s", n_file);
    fclose(F);
    _getch();
    return 0;
}

        
    
