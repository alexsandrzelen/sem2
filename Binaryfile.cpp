#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>

void write_numbers(const char* filename) {
    int number;
    int choice;

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }

    do {
        printf("Введите целое число для заполнения: ");
        while (scanf_s("%d", &number) != 1 || getchar() != '\n') {
            printf("Ошибка. Введите число заново\n");
            rewind(stdin);
        }

        fwrite(&number, sizeof(int), 1, file);

        printf("Хотите ввести еще одно число? Введите 1, если да, любое другое число для выхода: ");
        while (scanf_s("%d", &choice) != 1 || getchar() != '\n') {
            printf("Ошибка. Введите число\n");
            rewind(stdin);
        }
    } while (choice == 1);

    fclose(file);
    printf("Числа успешно записаны в файл %s.\n", filename);
}

void read_numbers(const char* filename) {
    int number;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения!\n");
        return;
    }

    printf("Содержимое файла %s:\n", filename);
    while (fread(&number, sizeof(int), 1, file) == 1) {
        printf("%d ", number);
    }
    printf("\n");
    fclose(file);
}


int count_occurrences(const char* filename, int target) {
    int number = 0;
    int count = 0;
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Ошибка открытия файла для чтения!\n");
        return -1; // Ошибка открытия файла
    }

    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (number == target) {
            count++;
        }
    }

    fclose(file);
    return count;
}

void replace_with_max(const char* filename, int target) {
    int number;
    int max = INT_MIN; // Инициализируем как INT_MIN
    int count = 0;
    int* numbers = NULL;

    // Считываем числа и находим максимальный элемент
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения!\n");
        return;
    }

    // Считываем числа в массив и находим максимальный элемент
    while (fread(&number, sizeof(int), 1, file) == 1) {
        // Увеличиваем массив
        numbers = realloc(numbers, sizeof(int) * (count + 1));
        if (numbers == NULL) {
            printf("Ошибка выделения памяти!\n");
            fclose(file);
            return 1;
        }
        numbers[count++] = number;

        // Находим максимальный элемент
        if (number > max) {
            max = number;
        }
    }
    fclose(file);

    // Если максимальный элемент не найден
    if (max == INT_MIN) {
        printf("Файл пуст или не содержит чисел.\n");
        free(numbers);
        return;
    }
    printf("Максимальное число - %d\n", max);

    // Заменяем элементы с заданным значением на максимальный элемент
    for (int i = 0; i < count; i++) {
        if (numbers[i] == target) {
            numbers[i] = max; // Замена
        }
    }

    // Открываем файл для записи
    fopen_s(file, filename, "wb");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи!\n");
        free(numbers);
        return;
    }

    // Записываем измененные числа обратно в файл
    fwrite(numbers, sizeof(int), count, file);
    fclose(file);

    // Выводим измененные числа на экран
    printf("Элементы со значением %d были заменены на максимальный элемент %d в файле %s.\n", target, max, filename);

    free(numbers); // Освобождаем память
}


void SortingOddell(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    int numOfElements = fileSize / sizeof(int);

    // Сортировка нечетных чисел в порядке убывания
    for (int i = 0; i < numOfElements - 1; i++) {
        for (int j = 0; j < numOfElements - 1 - i; j++) {
            int num1, num2;

            // Читаем первое число
            fseek(file, j * sizeof(int), SEEK_SET);
            fread(&num1, sizeof(int), 1, file);

            // Читаем второе число
            fseek(file, (j + 1) * sizeof(int), SEEK_SET);
            fread(&num2, sizeof(int), 1, file);

            // Если оба числа нечетные и num1 < num2, меняем их местами
            if (num1 % 2 != 0 && num2 % 2 != 0 && num1 < num2) {
                // Записываем обратно в файл в отсортированном порядке
                fseek(file, j * sizeof(int), SEEK_SET);
                fwrite(&num2, sizeof(int), 1, file);

                fseek(file, (j + 1) * sizeof(int), SEEK_SET);
                fwrite(&num1, sizeof(int), 1, file);
            }
        }
    }

    fclose(file);
}

void Sortingel(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    int numOfElements = fileSize / sizeof(int);

    for (int i = 0; i < numOfElements - 1; i++) {
        for (int j = 0; j < numOfElements - 1 - i; j++) {
            int num1, num2;

            fseek(file, j * sizeof(int), SEEK_SET);
            fread(&num1, sizeof(int), 1, file);

            fseek(file, (j + 1) * sizeof(int), SEEK_SET);
            fread(&num2, sizeof(int), 1, file);

            if (num1 < num2) {
                fseek(file, j * sizeof(int), SEEK_SET);
                fwrite(&num2, sizeof(int), 1, file);

                fseek(file, (j + 1) * sizeof(int), SEEK_SET);
                fwrite(&num1, sizeof(int), 1, file);
            }
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    
    setlocale(LC_ALL, "Rus");
    int number=0;
   
    if (argc < 2) {
        printf("Использование: %s <Binaryfile>\n", argv[0]);
        return 1;
    }

    
    FILE* file = fopen(argv[1], "wb");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    write_numbers(argv[1]);
    read_numbers(argv[1]);
    
    int target = 0;
    printf("Введите число для подсчета его вхождений в файл: ");
    while (scanf_s("%d", &target) != 1 || getchar() != '\n') {
        printf("Ошибка. Введите число для подсчета его вхождений в файл: ");
        rewind(stdin);
    }
    int recount = count_occurrences(argv[1], target);

    if (recount != -1) {
        printf("Число %d встречается %d раз(а) в файле %s.\n", target, recount, argv[1]);
    }    
    fclose(file);
    
    int targetb = 0;
    printf("Введите число для замены на максимальный элемент: ");
    while (scanf_s("%d", &targetb) != 1 || getchar() != '\n') {
        printf("Ошибка. Введите число для замены на максимальный элемент: ");
        rewind(stdin);
    }

    replace_with_max(argv[1], targetb);

    read_numbers(argv[1]);

    printf("\n");
    SortingOddell(argv[1]);

    read_numbers(argv[1]);

    return 0;

}


