#include <iostream>
#include <cstdio>
typedef struct person{
    int num;
    struct person* next;
}p;
int FindSurvivor(p** Head,int k,int index){
    struct person* tmp1 = *Head;
    struct person* tmp2 = *Head;
    int flag = 0;
    while(tmp1->next != tmp1){
        if(flag == 0) {
            for (int i = 0; i < index - 1; i++) {
                flag = 666;
                tmp2 = tmp1;
                tmp1 = tmp1->next;
            }
        }
        for(int i = 0; i < k - 1;i++){
            tmp2 = tmp1;
            tmp1 = tmp1->next;
        }
        tmp2->next = tmp1->next;
        printf("killed： %d\n",tmp1->num);
        tmp1 = tmp2->next;
    }
    *Head = tmp1;
    return tmp1->num;
}
void CreateJosephusProblemList(p** Head, int num){
    p* r ;
    for(int i = 1;i <= num; i++){
        p* tmp = (p*)malloc(sizeof(p));
        tmp->num = i;
        tmp->next = nullptr;
        if(*Head == nullptr){
            *Head = tmp;
        }
        else{
            r->next = tmp;
        }
        r = tmp;
    }
    r->next = *Head;
}
int main() {
    struct person* person = nullptr;
    //num of people
    int n = 8;
    //num to be skip
    int m = 4;
    // num to start
    int i = 2;
    //scanf("%d%d%d", &n, &m ,&i);
    CreateJosephusProblemList(&person,n);
    printf("survivor: %d\n", FindSurvivor(&person , m , i));
    return 0;
}
