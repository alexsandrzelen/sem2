#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Функция записи чисел в файл
void write_numbers(const char* filename) {
    int number = 0;
    int choice = 0;

    FILE* file = fopen(filename, "wt");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }

    do {
        printf("Введите целое число для записи: ");
        while (scanf("%d", &number) != 1) {
            printf("Ошибка. Введите число заново: ");
            while (getchar() != '\n'); // Очистка ввода
        }

        fprintf(file, "%d ", number);

        printf("Хотите ввести еще одно число? Введите 1, если да, любое другое число для выхода: ");
        while (scanf("%d", &choice) != 1) {
            printf("Ошибка. Введите число заново: ");
            while (getchar() != '\n');
        }
    } while (choice == 1);

    fclose(file);
    printf("Числа успешно записаны в файл %s.\n", filename);
}

// Функция чтения чисел из файла
void read_numbers(const char* filename) {
    int number;
    FILE* file = fopen(filename, "rt");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return;
    }

    printf("Содержимое файла %s:\n", filename);
    while (fscanf(file, "%d", &number) == 1) {
        printf("%d ", number);
    }
    printf("\n");
    fclose(file);
}

// Функция подсчета вхождений числа в файле
int count_occurrences(const char* filename, int target) {
    int number;
    int count = 0;
    FILE* file = fopen(filename, "rt");

    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return -1;
    }

    while (fscanf(file, "%d", &number) == 1) {
        if (number == target) {
            count++;
        }
    }

    fclose(file);
    return count;
}

// Функция циклического сдвига массива вправо
void cyclic_shift(int* array, int size, int k) {
    if (size == 0) return;
    k = k % size;
    if (k == 0) return;

    int* temp = (int*)malloc(k * sizeof(int));
    if (temp == NULL) return;

    // Сохраняем последние k элементов
    for (int i = 0; i < k; i++) {
        temp[i] = array[size - k + i];
    }

    // Сдвигаем оставшиеся элементы
    for (int i = size - 1; i >= k; i--) {
        array[i] = array[i - k];
    }

    // Переносим сохраненные элементы в начало
    for (int i = 0; i < k; i++) {
        array[i] = temp[i];
    }

    free(temp);
}

// Функция чтения чисел из файла в массив
int read_numbers_from_file(const char* filename, int* array) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%d", &array[count]) == 1 && count < 100) {
        count++;
    }

    fclose(file);
    return count;
}

// Функция записи массива чисел в файл
void write_numbers_to_file(const char* filename, int* array, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);
}

// Главная функция программы
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");

    if (argc < 2) {
        printf("Использование: %s <filename>\n", argv[0]);
        return 1;
    }

    write_numbers(argv[1]); // Запись чисел в файл
    read_numbers(argv[1]);  // Чтение и вывод содержимого файла

    int target;
    printf("Введите число для подсчета его вхождений в файл: ");
    while (scanf("%d", &target) != 1) {
        printf("Ошибка. Введите число заново: ");
        while (getchar() != '\n');
    }

    int recount = count_occurrences(argv[1], target);
    if (recount != -1) {
        printf("Число %d встречается %d раз(а) в файле %s.\n", target, recount, argv[1]);
    }

    int numbers[100];
    int count = read_numbers_from_file(argv[1], numbers);
    if (count < 0) return 1;

    int k;
    printf("Введите количество позиций для сдвига: ");
    while (scanf("%d", &k) != 1) {
        printf("Ошибка. Введите количество позиций для сдвига: ");
        while (getchar() != '\n');
    }

    cyclic_shift(numbers, count, k);
    write_numbers_to_file(argv[1], numbers, count);
    read_numbers(argv[1]); // Вывод содержимого файла после сдвига

    return 0;
}
