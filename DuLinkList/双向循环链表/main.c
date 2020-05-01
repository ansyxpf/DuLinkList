//
//  main.c
//  双向循环链表
//
//  Created by 徐鹏飞 on 2020/5/1.
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
Status  creatLinkList(LinkList *L){

    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) {
        return ERROR;
    }

    (*L)->next = (*L);
    (*L)->prior = (*L);

    
    //新增数据
    Node *p,*temp = NULL;
    p = *L;
    
    for (int i = 0; i < 10; i++) {
        temp = (LinkList)malloc(sizeof(Node));
        temp->data = i;
        temp->prior = p;
        p->next = temp;
        p = temp;
    }
    
    p->next = (*L);
    (*L)->prior = temp;
    
    return OK;
}
//2.遍历双向循环链表
Status Display(LinkList L) {
    if (L == NULL) {
        printf("打印的双向循环链表为空!\n\n");
        return ERROR;
    }
    printf("双向循环链表内容:  ");

    
    LinkList p = L->next;
    while (p != L) {
        printf("%d    ",p->data);
        p = p->next;
    }
    printf("\n");
    
    return OK;
}
//3.双向循环链表插入元素
Status LinkListInsert(LinkList *L, int index, ElemType e){
    
    //1.创建指针p,指向双向链表头
    LinkList p = (*L);
    int i = 1;
    //2.双向循环链表为空,则返回error
    if (*L == NULL) {
        return ERROR;
    }
    //3.找到插入前一个位置上的结点p
    while (i < index && p->next != *L) {
        p = p->next;
        i++;
    }
    //4.如果i>index 则返回error
    if (i > index) {
        return ERROR;
    }
    //5.创建新结点temp
    LinkList temp = (LinkList)malloc(sizeof(Node));
    //6.temp 结点为空,则返回error
    if (temp == NULL) {
        return ERROR;
    }
    //7.将生成的新结点temp数据域赋值e.
    temp->data = e;
    //8.将结点temp 的前驱结点为p;
    temp->prior = p;
    //9.temp的后继结点指向p->next;
    temp->next = p->next;
    //10.p的后继结点为新结点temp;
    p->next = temp;
    //如果temp 结点不是最后一个结点
    if (*L != temp->next) {
        temp->next->prior = temp;
    }else {
        (*L)->prior = temp;
    }
    
    return OK;
}
//4.双向循环链表删除结点
Status  LinkListDelete(LinkList *L,int index,ElemType *e){
    
    int i = 1;
    LinkList temp = (*L)->next;
    
    if (*L == NULL) {
        return ERROR;
    }
    //情况1：如果删除到只剩下首元结点了,则直接将*L置空;
    if (temp->next == *L) {
        free(*L);
        (*L) == NULL;
        return OK;
    }
    //情况2：如果删除到剩下不止首元结点，还有其他结点
    //1.找到要删除的结点
    while (i < index) {
        temp = temp->next;
        i++;
    }
    //2.给e赋值要删除结点的数据域
    *e = temp->data;
    //3.修改被删除结点的前驱结点的后继指针
    temp->prior->next = temp->next;
    //4.修改被删除结点的后继结点的前驱指针
    temp->next->prior = temp->prior;
    //5.释放结点temp
    free(temp);
    
    return OK;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 双向循环链表!\n");
    
    LinkList L;
    Status iStatus;
    ElemType temp,item;
    
    iStatus = creatLinkList(&L);
    printf("双向循环链表初始化是否成功(1->YES)/ (0->NO):  %d\n\n",iStatus);
    Display(L);
    
    printf("输入要插入的位置和数据用空格隔开：");
    scanf("%d %d",&temp,&item);
    iStatus = LinkListInsert(&L,temp,item);
    Display(L);
    
    printf("输入要删除位置：");
    scanf("%d",&temp);
    iStatus = LinkListDelete(&L, temp, &item);
    printf("删除链表位置为%d,结点数据域为:%d\n",temp,item);
    Display(L);
    
    
    return 0;
}
