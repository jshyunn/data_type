﻿#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct USERDATA {
    char szName[64];
    char szPhone[64];
} USERDATA;

typedef struct NODE {
    void* pData;

    const char* (*GetName)(void*);

    struct NODE* prev;
    struct NODE* next;
} NODE;

NODE* g_pHead;
NODE* g_pTail;
int g_nSize;

void InitList() {
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));

    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    g_pHead->next = g_pTail;
    g_pTail->prev = g_pHead;

    g_nSize = 2;

    printf("pHead: [%p], pTail: [%p], Size: [%d]\n", g_pHead, g_pTail, g_nSize);
}

void InsertBefore(NODE* pPivotNode, void* pData, const char* (*pfData)(void*)) {
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));

    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->next = pPivotNode;
    pNewNode->prev = pPivotNode->prev;
    pNewNode->pData = pData;
    pNewNode->GetName = pfData;

    pPivotNode->prev = pNewNode;
    pNewNode->prev->next = pNewNode;
    g_nSize++;
}

void InsertAtHead(void* pData, const char* (*pfData)(void*)) {
    InsertBefore(g_pHead->next, pData, pfData);

    printf("InsertAtHead(): [%p]\n", pData);
}

void InsertAtTail(void* pData, const char* (*pfData)(void*)) {
    InsertBefore(g_pTail, pData, pfData);

    printf("InsertAtTail(): [%p]\n", pData);
}

void InsertAt(int idx, void* pData, const char* (*pfData)(void*)) {
    if (idx > g_nSize - 2)
    {
        printf("InsertAt(): Invalid Index[%d]\n", idx);
        return;
    }
    int i = 0;
    NODE* pTmp = g_pHead->next;
    while (pTmp != NULL) {
        if (i == idx)
        {
            InsertBefore(pTmp, pData, pfData);
        }
        pTmp = pTmp->next;
        i++;
    }
    printf("InsertAt(): Index: [%d]\n", idx);
}

int GetSize() {
    return g_nSize;
}

int GetLength() {
    return GetSize();
}

int isEmpty() {
    return GetSize();
}

NODE* GetAt(int idx) {
    int i = 0;
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail) {
        if (i == idx) 
        {
            printf("GetAt(): [%p], [%d]\n", pTmp, i);
            return pTmp;
        }
        pTmp = pTmp->next;
        i++;
    }
    printf("GetAt(): Invalid Index[%d]\n", idx);
    return NULL;
}

NODE* FindNode(const char* pszKey) {
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail) {
        if (strcmp(pTmp->GetName(pTmp->pData), pszKey) == 0) return pTmp;
        pTmp = pTmp->next;
    }
    return NULL;
}

void DeleteNode(const char* pszKey) {
    NODE* pDeleteNode = FindNode(pszKey);

    if (pDeleteNode == NULL)
    {
        printf("There's No Data: [%s]\n", pszKey);
        return;
    }

    pDeleteNode->prev->next = pDeleteNode->next;
    pDeleteNode->next->prev = pDeleteNode->prev;
    
    free(pDeleteNode->pData);
    free(pDeleteNode);
    g_nSize--;

    printf("DeleteNode(): [%p], Size: [%d]\n", pDeleteNode, g_nSize);
}

void ReleaseList() {
    NODE* pTmp = g_pHead;
    while (pTmp != NULL)
    {
        NODE* pDeleteNode = pTmp;
        pTmp = pTmp->next;
        free(pDeleteNode->pData);
        free(pDeleteNode);
        g_nSize--;
        printf("ReleaseList(): [%p], Size: [%d]\n", pDeleteNode, g_nSize);
    }
}

void PrintList() {
    NODE* pTmp = g_pHead;
    while (pTmp != NULL)
    {
        if (pTmp == g_pHead || pTmp == g_pTail)
            printf("Prev: [%p], Curr: [%p], Next: [%p], Name: Dummy\n", pTmp->prev, pTmp, pTmp->next);
        else
            printf("Prev: [%p], Curr: [%p], Next: [%p], Name: [%s]\n", pTmp->prev, pTmp, pTmp->next, pTmp->GetName(pTmp->pData));

        pTmp = pTmp->next;
    }
}

const char* GetNameFromUserData(const USERDATA* pData) {
    return pData->szName;
}

void CreateUserData(const char* pszName, const char* pszPhone) {
    USERDATA* pData = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pData, 0, sizeof(USERDATA));

    strcpy_s(pData->szName, sizeof(pData->szName), pszName);
    strcpy_s(pData->szPhone, sizeof(pData->szPhone), pszPhone);

    InsertAtHead(pData, GetNameFromUserData);
}

int main()
{
    InitList();

    CreateUserData("Seunghyun", "010-1111-1111");
    CreateUserData("JSH", "010-2222-2222");

    PrintList();

    ReleaseList();
}
