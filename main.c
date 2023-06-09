#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "product.h"

int selectMenu(){
    int menu;
    printf("\n******* Dessert CAFE *******\n");
    printf("1. 조회 \n");
    printf("2. 추가 \n");
    printf("3. 수정 \n");
    printf("4. 삭제 \n");
    printf("5. 저장 \n");
    printf("6. 검색 \n");
    printf("7. 계산 \n");
    printf("0. 종료 \n");
    printf("\n번호 선택 : ");
    scanf("%d", &menu);
    
    return menu;
}
int main(){
    Dessert d[100];
    memset(d, 0, sizeof(d));
    int count = 0, index = 0, menu;

    count = loadData(d);
    index = count;

    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        if (menu == 1){//조회
            if(count < 1){
                printf("=> 조회 가능한 메뉴가 없습니다.\n");
                continue;
            }
            listDessert(d, index);
        }
        else if (menu == 2){//추가
            addDessert(&d[index]);
            count++;
            index++;

            qsort(d, count, sizeof(Dessert), compare);

            printf("\n=> 추가됨!\n");
        }
        else if (menu == 3){
            if(count < 1){
                printf("=> 수정 가능한 메뉴가 없습니다.\n");
                continue;
            }
            int num = selectDessert(d, index);
            if(num < 0){
                printf("\n=> 취소됨!\n");
                continue;
            }

            updateDessert(&d[num]);

            qsort(d, count, sizeof(Dessert), compare);
        }
        else if (menu == 4){
            if(count < 1){
                printf("=> 삭제 가능한 메뉴가 없습니다.\n");
                continue;
            }
            int num = selectDessert(d, index);
            if(num < 0){
                printf("\n=> 취소됨!\n");
                continue;
            }

            int result = deleteDessert(&d[num]);
            if(result == 0)
                count--;
            
        }
        else if (menu == 5){
            saveData(d, index);
            if(count < 1){
                printf("=> 저장 가능한 메뉴가 없습니다.\n");
                continue;
            }
            saveData(d, count);
        }
        else if (menu == 6){
            search(d, index);
        }
        else if (menu == 7){
            howMuch(d, index);

            if(count < 1){
                printf("=> 계산 가능한 메뉴가 존재하지 않습니다. 죄송합니다\n");
                continue;
            }
            howMuch(d, count);

        }

        else{
            printf("\n=> 다시 선택해주세요!\n");
        }
    }
    printf("\n종료됨!\n");

    return 0;
}
