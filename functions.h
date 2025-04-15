
int remainder_by_4(int n);
void task1(int num);

#define DATE_SIZE 11   
#define NAME_SIZE 50   


typedef struct {
    int count;                    
    char name[NAME_SIZE];        
    char date[DATE_SIZE];       
    float lifespan;               
} Animal;

void input_string(char* str, int size);
void checkDates(char* str, int size);
void input_animal(Animal* a);
void print_animal(const Animal* a);
int my_strcmp(const char* str1, const char* str2);
void find_by_name(Animal* animals, int size, const char* target_name, int found);
int delete_by_count(Animal* animals, int size, int target_count);
void task2(num_animals);
