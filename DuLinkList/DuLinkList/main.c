//
//  main.c
//  DuLinkList
//
//  Created by 徐鹏飞 on 2020/4/30.
//  Copyright © 2020 徐鹏飞. All rights reserved.
//双向链表

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

//1 双向链表初始化
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
//2.遍历双向链表
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
//3.双向链表插入
Status ListInsert(LinkList *L, int i, ElemType data) {
    
    //1.插入位置不合法，为0或为负数
    if (i < 1) return ERROR;
    
    //2.新建结点
    LinkList temp = (LinkList)malloc(sizeof(Node));
    temp->data = data;
    temp->prior = NULL;
    temp->next = NULL;
    
    //3.将p指向头结点
    LinkList p = *L;
    
    //4.找到插入的位置i直接的结点
    for (int j = 1; j < i && p; j++) {
        p = p->next;
    }
    
    //5.如果插入的位置超过链表本身的长度
    if (p == NULL) {
        return ERROR;
    }
    
    //6.判断插入位置是否为链表尾部
    if (p -> next == NULL) {
        p->next =temp;
        temp->prior = p;
    }else {
        temp->next = p->next;
        p->next->prior = temp;
        p->next = temp;
        temp->prior = p;
    }

    return OK;
}
//4.删除双向链表指定位置上的结点
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int k = 1;
    LinkList p = (*L);
    
    //1.判断双向链表是否为空，如果为空则返回ERROR;
    if (*L == NULL) {
        return ERROR;
    }
    
    //2.将指针p移动到i的位置
    while (k < i && p != NULL) {
        p = p->next;
        k++;
    }
    
    //3.如果k>i,或者p == NULL 则返回ERROR
    while (k > i || p == NULL) {
        return ERROR;
    }
    
    //4.创建临时指针delTemp 指向要删除的结点，并将要删除的结点的data 赋值给*e，带回到main函数
    LinkList delTemp = p->next;
    *e = delTemp->data;
    
    //5.p->next 等于要删除的结点的下一个结点
    p->next = delTemp->next;
    
    //6.如果要删除结点的下一个结点不为空，则将要删除的下一个结点的前驱指向p
    if (delTemp->next != NULL) {
        delTemp->next->prior = p;
    }
    //7.删除delTemp结点
    free(delTemp);

    return OK;
}
//5.删除双向链表指定的元素
Status LinkListDeleteVAL(LinkList *L, int data) {
    
    LinkList p = *L;//1.创建临时结点指向首结点
    //2.遍历双向链表
    while (p) {
        //3.判断当前结点的数据域和data是否相等，若相等则删除该结点
        if (p->data == data) {
            //4.修改被删除点的前驱结点的后继指针 = 删除结点的后继指针
            p->prior->next = p->next;
            if (p->next != NULL) {//5.判断是否为尾结点，若不是尾结点
                p->next->prior = p->prior;//则删除结点的后继结点的前驱结点 = 删除结点的前驱结点
            }
            free(p);//6.删除delTemp结点
            break;
        }
        p = p->next;//7.若数据域不相等则执行循环操作
    }
    return OK;
}
//6.在双向链表中查找元素
int selectElem(LinkList L,ElemType elem) {
    LinkList p = L->next;
    
    int i = 1;
    while (p) {
        
        if (p->data == elem) {
            return i;
        }
        i++;
        p = p->next;
    }

    return -1;
}
//7.在双向链表中更新结点
Status replaceLinkList(LinkList *L,int index, ElemType newElem) {
    LinkList p = (*L)->next;
    for (int i = 1; i < index; i++) {
        p = p->next;
    }
    p->data = newElem;
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 双向链表!\n");
    Status iStatus = 0;
    LinkList L;
    int temp,item,e;
    iStatus = creatLinkList(&L);
    display(L);
    
    printf("请输入插入的位置 元素\n");
    scanf("%d %d",&temp,&item);
    iStatus = ListInsert(&L, temp, item);
    printf("插入数据，打印链表：\n");
    display(L);
    
    printf("请输入删除的位置\n");
    scanf("%d",&temp);
    iStatus = ListDelete(&L, temp, &e);
    printf("删除元素: 删除位置为%d,data = %d\n",temp,e);
    printf("删除操作之后的,双向链表:\n");
    display(L);
    
    printf("请输入你要删除的内容\n");
    scanf("%d",&item);
    iStatus = LinkListDeleteVAL(&L, item);
    printf("删除指定data域等于%d的结点,双向链表:\n",item);
    printf("删除操作之后的,双向链表:\n");
    display(L);

    
    printf("请输入你要查找的内容\n");
    scanf("%d",&item);
    ElemType index = selectElem(L, item);
    printf("在双向链表中查找到数据域为%d的结点,位置是:%d\n",item,index);

    printf("请输入你要更新的结点以及内容\n");
    scanf("%d %d",&temp,&item);
    iStatus = replaceLinkList(&L, temp, item);
    printf("更新结点数据后的双向链表:\n");
    display(L);
    
    
    return 0;
}
