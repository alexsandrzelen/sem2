//Зелень 27.03.22.
// Задание 1 
//Найти и вывести остаток от деления целого числа на 4, не выполняя деления
//и не используя операцию взятия остатка от деления.
//Задание 2 
//Структура содержит информацию о животных зоопарка : количество особей
//(число), название(указатель), вложенную структуру – дату поступления в
//зоопарк(строка фиксированной длины) и среднюю продолжительность
//жизни.Найти животных с заданным названием.Удалить животных с
//заданным количеством особей.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int remainder_by_4(int n) {
    return n & 3; // побитовое И с 3 (0b11) даёт остаток от деления на 4
}

void task1(int num) {
    printf("Введите число: ");
    while (scanf_s("%d", &num) != 1 && getchar() != '\n') {
        printf("Ошибка! Введите число: ");
        rewind(stdin);
    }
    printf("Остаток от деления %d на 4: %d\n", num, remainder_by_4(num));
}

#define DATE_SIZE 11   // Формат даты "DD.MM.YYYY"
#define NAME_SIZE 50   // Максимальная длина названия животного

// Структура для хранения информации о животных
typedef struct {
    int count;                    // Количество особей
    char name[NAME_SIZE];         // Название животного
    char date[DATE_SIZE];         // Дата поступления
    double lifespan;               // Средняя продолжительность жизни
} Animal;

// Функция ввода строки вручную
void input_string(char* str, int size) {
    char c;
    int i = 0;
    while ((c = getchar()) != '\n' && c != EOF); // Очистка буфера ввода
    while (i < size - 1) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        str[i++] = c;
    }
    str[i] = '\0'; // Завершающий символ
}

void checkDates(char* str, int size) {
    int day=0, month=0, year=0;
    char answer=0;
  
    while (1) {
        printf("\n");
        printf("Введите день: ");
        while (scanf_s("%d", &day) != 1 || day < 0 || day > 31) {
            printf("Ошибка! Введите день (число)(31 макс.): ");
            rewind(stdin);
        }

        printf("Введите месяц: ");
        while (scanf_s("%d", &month) != 1 || month < 0 || month > 12) {
            printf("Ошибка! Введите месяц (число)(12 макс.): ");
            rewind(stdin);
        }
        

        printf("Введите год: ");
        while (scanf_s("%d", &year) != 1 || year < 0 || year > 2025) {
            printf("Ошибка! Введите год (число)(2025 макс.): ");
            rewind(stdin);
        }
      

        // Проверка високосного года
        int isLeap = 0;
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            isLeap = 1;
        }

        // Определение количества дней в месяце
        int daysInMonth = 0;
        if (month == 1 || month == 3 || month == 5 || month == 7 ||
            month == 8 || month == 10 || month == 12) {
            daysInMonth = 31;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        }
        else if (month == 2) {
            daysInMonth = isLeap ? 29 : 28;
        }

        // Проверка корректности даты
        if (year >= 1 && year <= 9999 &&
            month >= 1 && month <= 12 &&
            day >= 1 && day <= daysInMonth) {
            printf("Дата корректна: %02d.%02d.%04d\n", day, month, year);
            sprintf(str, "%02d.%02d.%04d", day, month, year);
            break;
        }
        else {
            printf("Дата некорректна.\n");
            printf("Пожалуйста, убедитесь в корректности данных и повторите ввод.");
            continue;
        }
    }
}

// Функция для ввода данных о животном
void input_animal(Animal* a) {
    printf("Введите название животного: ");
    input_string(a->name, NAME_SIZE);

    printf("Введите количество особей: ");
    while (scanf_s("%d", &a->count) != 1 && getchar() != '\n') {       
        printf("Ошибка! Введите количество особей: ");
        rewind(stdin);
    }

    printf("Введите дату поступления (DD.MM.YYYY): ");
    checkDates(a->date, DATE_SIZE);

    printf("Введите среднюю продолжительность жизни: ");
    while (scanf_s("%lf", &a->lifespan) != 1 && getchar() != '\n') {
        printf("\n");
        printf("Ошибка! Введите среднюю продолжительность жизни: ");
        rewind(stdin);
    }
}

// Функция для вывода данных о животном
void print_animal(const Animal* a) {
    printf("\nНазвание: %s\n", a->name);
    printf("Количество особей: %d\n", a->count);
    printf("Дата поступления: %s\n", a->date);
    printf("Средняя продолжительность жизни: %.2lf лет\n", a->lifespan);
}

// Функция сравнения строк
int my_strcmp(const char* a, const char* b) {
    if (a == NULL || b == NULL) return -1;

    while (*a && (*a == *b)) {
        a++;
        b++;
    }

    return *(unsigned char*)a - *(unsigned char*)b;
}

// Функция поиска животных по названию
void find_by_name(Animal* animals, int size, const char* target_name, int found) {
    
    for (int i = 0; i < size; i++) {
        if (my_strcmp(animals[i].name, target_name) == 0) {
            print_animal(&animals[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Животные с названием '%s' не найдены.\n", target_name);
    }
}

// Функция удаления животных с заданным количеством особей
int delete_by_count(Animal* animals, int size, int target_count) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (animals[i].count != target_count) {
            animals[new_size++] = animals[i]; 
        }
    }
    return new_size;
}

int task2(num_animals) {
    
    printf("Введите количество животных в зоопарке: ");
    while (scanf_s("%d", &num_animals) != 1 && getchar() != '\n') {
        printf("Ошибка! Введите количество животных в зоопарке: ");
        rewind(stdin);
    }
  
    Animal* zoo = (Animal*)malloc(num_animals * sizeof(Animal));
    if (!zoo) {
        printf("Ошибка выделения памяти!\n");
        return -1;
    }
    
    // Ввод данных о животных
    for (int i = 0; i < num_animals; i++) {
        printf("Введите данные для животного %d:\n", i + 1);       
        input_animal(&zoo[i]);
    }

    // Вывод всех данных
    printf("\nСписок всех животных:\n");
    for (int i = 0; i < num_animals; i++) {
        print_animal(&zoo[i]);
    }
    int choice1 = 1;
    while (choice1 != 0) {
        int found = 0;     
        char search_name[NAME_SIZE];
        printf("\nВведите название животного для поиска: ");
        input_string(search_name, NAME_SIZE);
        find_by_name(zoo, num_animals, search_name, found);       
        printf("\nЕсли желаете продолжить поиск введите любой текст кроме '0': ");
        scanf_s("%d", &choice1);       
    } 
    printf("\n");
    // Удаление животных с заданным количеством особей
    int delete_count = 0;
    
    printf("Введите количество особей для удаления животного: ");
    while (scanf_s("%d", &delete_count) != 1 || getchar() != '\n') {
        printf("Oшибка! Введите количество особей для удаления животного: ");
        rewind(stdin);
    }
    num_animals = delete_by_count(zoo, num_animals, delete_count);

    // Вывод списка после удаления
    printf("\nСписок после удаления:\n");
    for (int i = 0; i < num_animals; i++) {
        print_animal(&zoo[i]);
    }

    // Освобождение памяти
    free(zoo);
    printf("\nПамять освобождена. Программа завершена.\n\n");
    return 1;
}


