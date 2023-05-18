#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "product.h"

int addDessert(Dessert *d){// *추가 사항(잘못된 입력에 대한 처리)*
    getchar();  //버퍼 비우기
    printf("\n");
    printf("디저트의 이름 : ");
    fgets(d->name, 100, stdin);
    d->name[strlen(d->name)-1] = '\0';

    printf("디저트의 가격 : ");
    scanf("%d", &d->price);

    getchar();  //버퍼 비우기
    printf("디저트의 종류 ( 음료 => '0' / 케이크 => '1' / 쿠키 => '2' ) : ");
    scanf("%d", &d->category);

    return 0;
} //Create
void readDessert(Dessert d, int index){
    if(d.price < 0)
        return;

    if(d.category == 0){//음료
        printf("%-4d %10s      %-25s    %d\n", index+1, "음료",d.name, d.price);
    }
    else if(d.category == 1){//케이크
        printf("%-4d  %10s      %-25s    %d\n", index+1, "케이크", d.name, d.price);
    }
    else{//쿠키
        printf("%-4d %10s      %-25s    %d\n", index+1, "쿠키", d.name, d.price);
    }

} //Read
int updateDessert(Dessert *d){
    int request;

    char n_name[100] = "";
    int n_price;
    int n_category;

    getchar();  //버퍼 비우기
    printf("\n");
    printf("디저트의 이름 : ");
    fgets(n_name, 100, stdin);
    n_name[strlen(n_name) -1] = '\0';

    printf("디저트의 가격 : ");
    scanf("%d", &n_price);

    getchar();  //버퍼 비우기
    printf("디저트의 종류(0 : 음료, 1 : 케이크, 2 : 쿠키) : ");
    scanf("%d", &n_category);

    getchar();  //버퍼 비우기
    printf("정말로 바꾸시겠습니까?(1 : update, 0 : No update)");
    scanf("%d", &request);
    
    if(request == 1){
        strcpy(d->name, n_name);
        d->name[strlen(n_name)] = '\0';
        d->price = n_price;
        d->category = n_category;

        printf("변경이 완료되었습니다.\n");
        return 0;
    }
    else{
        printf("변경이 취소되었습니다.\n");
        return -1;
    }

}  //Update
int deleteDessert(Dessert *d){
    int request;

    getchar();  //버퍼 비우기
    printf("정말로 삭제하시겠습니까?(1 : update, 0 : No update)");
    scanf("%d", &request);

    if(request == 1){

        d->price = -1;

        printf("삭제가 완료되었습니다.\n");
        return 0;
    }
    else{
        printf("삭제가 취소되었습니다.\n");
        return -1;
    }

}  //Delete
void listDessert(Dessert d[], int count){
    printf("\n No |  Category  |         Name         | Price\n");
    printf("====================================================\n");

    for(int i = 0; i < count; i++){
        readDessert(d[i], i);
    }

}  //List Dessert
int selectDessert(Dessert d[], int count){
    int num;

    listDessert(d, count);
    printf("\n번호는 (취소 :0)? ");
    scanf("%d", &num);

    if(num <= 0)
        return -1;
    else if(num > count){
        return -1;
    }
    return num-1;
} //select Dessert
int compare(const void *a, const void *b){
    Dessert *pa = (Dessert*)a;
    Dessert *pb = (Dessert*)b;

    if(pa->category > pb->category)
        return 1;
    else if(pa->category < pb->category)
        return -1;
    else
        return 0;
}//비교함수
void saveData(Dessert d[], int count)
{
    FILE *fp;
    fp = fopen("menulist.txt", "wt");
    for(int i = 0; i < count; i++)
    {
        fprintf(fp, "%s/%d %d\n", d[i].name, d[i].price, d[i].category);
    }
	
	fclose(fp);
	printf("저장됨!\n");
}//저장함수

int loadData(Dessert *d)
{
    int count = 0;
    FILE *fp;
    fp = fopen("menulist.txt", "rt");
    while(!feof(fp))
    {
        fscanf(fp, "%s ", d[count].name);
        fscanf(fp, "%d ", &d[count].price);
        fscanf(fp, " %d\n", &d[count++].category);
    }
	fclose(fp);
    return count;
}