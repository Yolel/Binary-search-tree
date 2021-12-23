//
//  main.c
//  DataStructctureExperiment
//
//  Created by Yolel on 2021/12/20.
//
//  P.S.system("clear")used by Mac
//
//  The project has been uploaded to Github（https://github.com/Yolel/）
/*
【问题描述】
完成高校名称的动态查找表的建立、指定关键字的查找、插入与删除指定关键字结点。
【任务要求】
(1)    算法输入：根据实际情况输入若干高校信息，生成二叉排序树，每个结点包括校名、高校类型、所在城市、综合分数。
(2)    算法输出：显示二叉排序树的中序遍历结果、查找成功与否的信息、插入和删除后的中序遍历结果(排序结果)。
(3)    算法要点：二叉排序树建立方法、动态查找方法、二叉树的中序遍历。
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char name[20];
    char type[20];
    char city[20];
    int mark;
}JD;
typedef struct Tree{
    JD data;
    struct Tree *lChild;
    struct Tree *rChild;
}Tree,*BinTree;

int flag;

void PrintTMenu();//打印主菜单界面
void PrintTMenuSearch();//打印搜索界面

BinTree TotalMenu(BinTree T);//switch-case实现调用事件响应函数实现搜索菜单功能
void SearchMenu(BinTree T);//switch-case实现调用事件响应函数实现主菜单功能

JD InputData();//输入JD类型数据
void OutputData(JD data);//输出JD类型数据

BinTree SetNewNode(JD key);//创建新的树节点
BinTree SearchNodeByName(BinTree T,char name[]);//以学校校名搜索
BinTree SearchNodeByType(BinTree T,char type[]);//以学校类型搜索
BinTree SearchNodeByCity(BinTree T,char city[]);//以所在城市搜索
BinTree SearchNodeByMark(BinTree T,int mark);//以综合分数搜素
BinTree InsertNode(BinTree T, JD key);//插入校名不同的学校信息
BinTree DeleteNode(BinTree T,JD key);//删除已经存在的学校信息
void ShowNode(BinTree T);//打印一个节点的学校信息，并统计学校个数

BinTree Create(BinTree T);//建立二叉排序树
BinTree Search(BinTree T);//在二叉排序树中查找
void SearchByName(BinTree T);//按学校校名遍历搜索二叉树
void SearchByType(BinTree T);//按学校类型遍历搜索二叉树
void SearchByCity(BinTree T);//按所在城市遍历搜索二叉树
void SearchByMark(BinTree T);//按综合分数遍历搜索二叉树
BinTree Insert(BinTree T);//在排序树中插入新的学校的信息，并排除重复学校信息
BinTree Delete(BinTree T);//删除已知学校校名的树的节点
void Show(BinTree T);//中序遍历二叉树按学校校名ASKII由小到大排序并打印


int main() {
    system("clear");
    BinTree root = NULL;
    TotalMenu(root);
    return 0;
}


void PrintTMenu(){
    printf("===================================\n");
    printf("      高校排名的动态查找表的实现       \n");
    printf("                                   \n");
    printf("           1:信息输入               \n");
    printf("           2:信息查找               \n");
    printf("           3:信息插入               \n");
    printf("           4:信息删除               \n");
    printf("           5:信息输出               \n");
    printf("：                                 \n");
    printf("           0:退出系统               \n");
    printf("===================================\n");
    printf(">>请输入您的选项:");
}

void PrintTMenuSearch(){
    printf("===================================\n");
    printf("             信息查找               \n");
    printf("           按以下信息查找            \n");
    printf("           1:学校校名               \n");
    printf("           2:高校类型               \n");
    printf("           3:所在城市               \n");
    printf("           4:综合分数               \n");
    printf("           5:返回主菜单             \n");
    printf("：                                 \n");
    printf("           0:退出系统               \n");
    printf("===================================\n");
    printf(">>请输入您的选项:");
}

BinTree TotalMenu(BinTree T){
    while (1) {
        PrintTMenu();
        int opt;
        flag=0;
        scanf("%d",&opt);
        switch (opt) {
            case 1:
                T=Create(T);
                break;
            case 2:
                T=Search(T);
                break;
            case 3:
                T=Insert(T);
                break;
            case 4:
                T=Delete(T);
                break;
            case 5:
                Show(T);
                break;
            case 0:
                exit(0);
            default:
                printf(">>选项输入错误。\n");
                break;
        }
    }
}

void SearchMenu(BinTree T){
    while (1) {
        PrintTMenuSearch();
        int opt;
        scanf("%d",&opt);
        switch (opt) {
            case 1:
                SearchByName(T);
                break;
            case 2:
                SearchByType(T);
                break;
            case 3:
                SearchByCity(T);
                break;
            case 4:
                SearchByMark(T);
                break;
            case 5:
                T=TotalMenu(T);
                break;
            case 0:
                exit(0);
            default:
                printf(">>选项输入错误。\n");
                break;
        }
    }
}

JD InputData(){
    JD data;
    printf(">>请输入学校校名、高校类型、所在城市、综合分数:");
    scanf("%s",data.name);
    scanf("%s",data.type);
    scanf("%s",data.city);
    scanf("%d",&data.mark);
    return data;
}

void OutputData(JD data){
    printf("学校校名:%s ",data.name);
    printf("高校类型:%s ",data.type);
    printf("所在城市:%s ",data.city);
    printf("综合分数:%d\n",data.mark);
}

void ShowNode(BinTree T){
    flag++;
    printf("第%d所学校:\n",flag);
    OutputData(T->data);
}

BinTree SetNewNode(JD key){
    BinTree T= malloc(sizeof (Tree));
    T->data=key;
    T->rChild=NULL;
    T->lChild=NULL;
    return T;
}

BinTree InsertNode(BinTree T,JD key){
    if (T==NULL){
        return SetNewNode(key);
    }
    if (strcmp(T->data.name,key.name)>0){
        T->lChild = InsertNode(T->lChild, key);
    }
    else if (strcmp(T->data.name,key.name)<0){
        T->rChild = InsertNode(T->rChild, key);
    }
    return T;
}

BinTree SearchNodeByName(BinTree T,char name[]){
    while (1){
        if (T==NULL||strcmp(T->data.name,name)==0){
            break;
        } else if (strcmp(T->data.name,name)>0){
            T=T->lChild;
        } else{
            T=T->rChild;
        }
    }
    return T;
}

BinTree SearchNodeByType(BinTree T,char type[]){
    while (1){
        if (T==NULL|strcmp(T->data.type,type)==0){
            break;
        } else if (strcmp(T->data.type,type)>0){
            T=T->lChild;
        } else{
            T=T->rChild;
        }
    }
    return T;
}

BinTree SearchNodeByCity(BinTree T,char city[]){
    while (1){
        if (T==NULL||strcmp(T->data.city,city)==0){
            break;
        } else if (strcmp(T->data.city,city)>0){
            T=T->lChild;
        } else{
            T=T->rChild;
        }
    }
    return T;
}

BinTree SearchNodeByMark(BinTree T,int mark){
    while (1){
        if (T==NULL||T->data.mark==mark){
            break;
        } else if (T->data.mark>mark){
            T=T->lChild;
        } else{
            T=T->rChild;
        }
    }
    return T;
}

BinTree DeleteNode(BinTree T,JD key){
    BinTree t=SearchNodeByName(T,key.name);
    if (t==NULL)
    {
        printf("[警告]未查到此学校信息。\n");
        return T;
    }
    BinTree p,q,s,parent;
    p=T;
    while (p!=NULL){
        if (strcmp(p->data.name ,key.name)==0)  break;
        parent=p;
        p=(strcmp(p->data.name ,key.name)<0)?p->rChild:p->lChild;
    }
    if ((p->lChild==NULL)&&(p->rChild==NULL)){
        if (parent->lChild != NULL&& strcmp(parent->lChild->data.name,key.name)==0){
            parent->lChild = NULL;
        }
        if (parent->rChild!=NULL&&strcmp(parent->rChild->data.name,key.name)==0){
            parent->rChild = NULL;
        }
        printf("[消息]:信息删除成功。\n");
        return p;
    }
    else if (p->lChild!=NULL&&p->rChild==NULL){
        s=p->lChild;
        p->data=s->data;
        p->lChild=s->lChild;
        free(s);
        printf("[消息]:信息删除成功。\n");
        return p;
    }
    else if (p->lChild==NULL&&p->rChild!=NULL){
        s=p->rChild;
        p->data=s->data;
        p->rChild=s->rChild;
        free(s);
        printf("[消息]:信息删除成功。\n");
        return p;
    } else {
        q=p;
        s=p->lChild;
        while (s->rChild!=NULL){
            q=s;
            s=s->rChild;
        }
        p->data=s->data;
        if (q!=p){
            q->rChild=s->lChild;
        }
        else{
            q->lChild=s->lChild;
        }
        free(s);
        printf("[消息]:信息删除成功。\n");
        return p;
    }
}

BinTree Create(BinTree T){
    int num=0;
    printf(">>请输入高校个数:");
    scanf("%d",&num);
    for (int i = 0; i < num; ++i) {
        JD key=InputData();
        T=InsertNode(T,key);
    }
    return T;
}

BinTree Insert(BinTree T){
    if (T==NULL) {
        printf("[警告]:未输入信息。\n");
        return T;
    }
    JD key=InputData();
    if(SearchNodeByName(T,key.name)) {
        printf("[错误]:此学校信息已存在。插入失败。\n");
        return T;
    }
    T=InsertNode(T,key);
    return T;
}

BinTree Delete(BinTree T){
    if (T==NULL) {
        printf("[警告]:未输入信息。\n");
        return T;
    }
    JD key=InputData();
    T=DeleteNode(T,key);
    return T;
}

BinTree Search(BinTree T){
    if (T==NULL) {
        printf("[警告]:未输入信息。\n");
        return T;
    }
    SearchMenu(T);
    return T;
}

void SearchByName(BinTree T){
    char name[20];BinTree t=T;
    printf(">>请输入学校校名:");
    scanf("%s",name);
    t=SearchNodeByName(t,name);
    if (t==NULL){
        printf("[警告]未查到此学校信息。\n");
        Insert(T);
    }
    else
        OutputData(t->data);
}

void SearchByType(BinTree T){
    char type[20];BinTree t=T;
    printf(">>请输入高校类型:");
    scanf("%s",type);
    t=SearchNodeByType(t,type);
    if (t==NULL)
        printf("[警告]未查到此学校信息。\n");
    else
        OutputData(t->data);
}

void SearchByCity(BinTree T){
    char city[20];BinTree t=T;
    printf(">>请输入所在城市:");
    scanf("%s",city);
    t=SearchNodeByCity(t,city);
    if (t==NULL)
        printf("[警告]未查到此学校信息。\n");
    else
        OutputData(t->data);
}

void SearchByMark(BinTree T){
    int mark;BinTree t=T;
    printf(">>请输入综合分数:");
    scanf("%d",&mark);
    t= SearchNodeByMark(t,mark);
    if (t==NULL)
        printf("[警告]未查到此学校信息。\n");
    else
        OutputData(t->data);
}

void Show(BinTree T){
    if (T==NULL) {
        return;
    }
    Show(T->lChild);
    ShowNode(T);
    Show(T->rChild);
}
