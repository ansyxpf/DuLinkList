//
//  main.c
//  DuLinkList
//
//  Created by 徐鹏飞 on 2020/4/30.
//  Copyright © 2020 徐鹏飞. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

//定义结点
typedef struct Node{
    ElemType data;
    struct Node *prior;
    struct Node *next;
}Node;

typedef struct Node * LinkList;

//1 双向循环链表初始化
Status creatLinkList(LinkList *L){
    
    (*L) = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) return ERROR;
    
    (*L)->prior = NULL;
    (*L)->next = NULL;
    (*L)->data = -1;//这3行是初始化头结点，头结点可以不赋值，因为始终不会打印头结点
    
    LinkList p = *L;
    for (int i = 0; i < 10; i++) {
        //1.创建新结点temp
        LinkList temp = (LinkList)malloc(sizeof(Node));
        if (temp == NULL) return ERROR;
        temp->prior = NULL;
        temp->next = NULL;
        temp->data = i;
        //2.为temp建立一个双向链表关系
        p->next = temp;
        temp->prior = p;
        p = p->next;
    }
    
    
    return  OK;
}
//2.循环遍历双向链表
void display(LinkList L) {
    LinkList temp = L->next;
    if (temp == NULL) {
        printf("打印的双向循环链表为空!\n\n");
        return ;
    }
    printf("双向循环链表内容:  ");
    while (temp) {
        printf("%d   ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 双向链表!\n");
    Status iStatus = 0;
    LinkList L;
    int temp,item,e;
    iStatus = creatLinkList(&L);
    display(L);
    return 0;
}
