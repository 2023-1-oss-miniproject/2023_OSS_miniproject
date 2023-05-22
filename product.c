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
        printf("%-4d %10s　　　　%-25s　%d\n", index+1, "음료",d.name, d.price);
    }
    else if(d.category == 1){//케이크
        printf("%-4d　%10s　　　　%-25s　%d\n", index+1, "케이크", d.name, d.price);
    }
    else{//쿠키
        printf("%-4d %10s　　　　%-25s　%d\n", index+1, "쿠키", d.name, d.price);
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
void saveData(Dessert d[], int index)
{
    FILE *fp;
    fp = fopen("menulist.txt", "wt");
    for(int i = 0; i < index; i++)
    {
        if(d[i].price > 0)
            fprintf(fp, "%s %d %d\n", d[i].name, d[i].price, d[i].category);
    }
	
	fclose(fp);
	printf("저장됨!\n");
}//저장함수

int loadData(Dessert d[])
{
    int count = 0;
    FILE *fp;
    fp = fopen("menulist.txt", "rt");
    if(fp == NULL)
    {
        printf("파일 불러오기 실패!, 파일이 없습니다.\n");
        return 0;
    }
    printf("파일 불러오기 성공!\n");
    while(!feof(fp))
    {
        char str[100];
        fscanf(fp, "%[^1234567890]s ", str);
        strncpy(d[count].name, str, sizeof(str)-sizeof(char));
        fscanf(fp, "%d ", &d[count].price);
        fscanf(fp, " %d\n", &d[count++].category);
    }

	fclose(fp);
    if(count==0)
    {
        printf("불러올 목록이 없습니다.\n");
    }

    return count;
}

void search(Dessert d[], int index)
{
    getchar();
    char str[100];
    memset(str, 0, sizeof(str));
    printf("검색하실 내용을 입력해 주세요 : ");
    scanf("%[^\n]s", str);
    
    printf("\n No |  Category  |         Name         | Price\n");
    printf("====================================================\n");

    for(int i = 0; i < index; i++){
        if(strstr(d[i].name, str) && d[i].price >= 0)
            readDessert(d[i], i);
    }
    getchar();
    
}

void howMuch(Dessert d[], int index)
{
    int menuNum;
    int n = 0;
    int numOfDessert;
    int price = 0;
    Dessert newlist[100];

    
    while(1){
        listDessert(d, index);
        printf("\n원하는 메뉴의 번호를 선택해 주세요 : ");
        scanf("%d", &menuNum);
        if(menuNum > 0 && menuNum - 1 < index && d[menuNum-1].price > 0){
            break;
        }
        printf("유효한 입력이 아닙니다. 다시 입력해주세요\n");
        while(getchar() != '\n');
    }

    menuNum--;
    memcpy(&newlist[n], &d[menuNum], sizeof(d[menuNum]));
    while(1){
        printf("%s를/을 얼마나 주문하시겠습니까? : ", newlist[n].name);
        scanf("%d", &numOfDessert);
        if(numOfDessert > 0){
            break;
        }
        printf("유효한 입력이 아닙니다. 다시 입력해주세요\n");
        while(getchar() != '\n');
    }

    newlist[n++].price = numOfDessert;
    price += d[menuNum].price*numOfDessert;

    printf("현재 주문 목록");
    printf("\n No |  Category  |         Name         | Quantity\n");
    printf("====================================================\n");
    for(int i = 0; i < n; i++){
        readDessert(newlist[i], i);
    }
    printf("\n주문 금액 : %d\n", price);
    while(getchar() != '\n');

    char y_n;
    while(1){
        printf("\n더 주문 하시겠습니까?(y/n) : ");
        scanf("%c", &y_n);

        if(y_n == 'n' || y_n == 'N'){
            printf("\n총 주문 금액은 %d원입니다.\n", price);
            return;
        }

        else if(y_n == 'y' || y_n == 'Y'){
            while(1){
                listDessert(d, index);
                printf("\n원하는 메뉴의 번호를 선택해 주세요 : ");
                int innerMenuNum;
                scanf("%d", &innerMenuNum); //범위 초과시 처리 필요
                if(innerMenuNum > 0 && innerMenuNum - 1 < index && d[menuNum-1].price > 0){
                    menuNum = innerMenuNum;
                    break;
                }
                printf("유효한 입력이 아닙니다. 다시 입력해주세요\n");
                while(getchar() != '\n');
            }

            menuNum--;

            while(1){
                printf("%s를/을 얼마나 주문하시겠습니까? : ", d[menuNum].name);
                scanf("%d", &numOfDessert);
                if(numOfDessert > 0){
                    break;
                }
                printf("유효한 입력이 아닙니다. 다시 입력해주세요\n");
                while(getchar() != '\n');
            }
            
            int isContain = 0;
            for(int i = 0; i < n; i++){
                if(!strcmp(newlist[i].name, d[menuNum].name))
                {
                    newlist[i].price += numOfDessert;
                    price += d[menuNum].price * numOfDessert;
                    isContain = 1;
                    continue;
                }
            }
            
            if(!isContain){
                memcpy(&newlist[n], &d[menuNum], sizeof(d[menuNum]));
                newlist[n++].price = numOfDessert;
                price += d[menuNum].price * numOfDessert;
            }
            printf("\n현재 주문 목록");
            printf("\n No |  Category  |         Name         | Quantity\n");
            printf("====================================================\n");
            for(int i = 0; i < n; i++){
                readDessert(newlist[i], i);
            }
            printf("\n주문 금액 : %d\n", price);
            while(getchar() != '\n');
        }
        else
        {
            printf("유효한 입력이 아닙니다. 다시 입력해주세요\n");
            while(getchar() != '\n');
        }
    }
}