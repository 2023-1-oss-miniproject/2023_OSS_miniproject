typedef struct{
    char name[100];  //디저트 이름
    int price;  //디저트 가격
    int category;   //디저트의 category (0 : 음료, 1 : 케이크, 2 : 쿠키)
} Dessert;

int addDessert(Dessert *d); //Create
void readDessert(Dessert d, int index); //Read
int updateDessert(Dessert *d);  //Update
int deleteDessert(Dessert *d);  //Delete
void listDessert(Dessert d[], int count);  //List Dessert
int selectDessert(Dessert d[], int count); //select Dessert
int compare(const void *a, const void *b);
void saveData(Dessert d[], int index);
int loadData(Dessert d[]);
void search(Dessert d[], int index);
void howMuch(Dessert d[], int index);