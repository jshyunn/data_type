#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "mylist.h"

void InitList(LIST_INFO* pList) {
    pList->pHead = (NODE*)malloc(sizeof(NODE));
    pList->pTail = (NODE*)malloc(sizeof(NODE));

    memset(pList->pHead, 0, sizeof(NODE));
    memset(pList->pTail, 0, sizeof(NODE));

    pList->pHead->next = pList->pTail;
    pList->pTail->prev = pList->pHead;

    pList->nSize = 2;

    printf("pHead: [%p], pTail: [%p], Size: [%d]\n", pList->pHead, pList->pTail, pList->nSize);
}

void InsertBefore(LIST_INFO* pList, NODE* pPivotNode, void* pData) {
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));

    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->next = pPivotNode;
    pNewNode->prev = pPivotNode->prev;
    pNewNode->pData = pData;

    pPivotNode->prev = pNewNode;
    pNewNode->prev->next = pNewNode;
    pList->nSize++;
}

void InsertAtHead(LIST_INFO* pList, void* pData) {
    InsertBefore(pList, pList->pHead->next, pData);

    printf("InsertAtHead(): [%p]\n", pData);
}

void InsertAtTail(LIST_INFO* pList, void* pData) {
    InsertBefore(pList, pList->pTail, pData);

    printf("InsertAtTail(): [%p]\n", pData);
}

void InsertAt(LIST_INFO* pList, int idx, void* pData) {
    if (idx > pList->nSize - 2)
    {
        printf("InsertAt(): Invalid Index[%d]\n", idx);
        return;
    }
    int i = 0;
    NODE* pTmp = pList->pHead->next;
    while (pTmp != NULL) {
        if (i == idx)
        {
            InsertBefore(pList, pTmp, pData);
        }
        pTmp = pTmp->next;
        i++;
    }
    printf("InsertAt(): Index: [%d]\n", idx);
}

int GetSize(LIST_INFO* pList) {
    return pList->nSize;
}

int GetLength(LIST_INFO* pList) {
    return GetSize(pList);
}

int isEmpty(LIST_INFO* pList) {
    return GetSize(pList);
}

NODE* GetAt(LIST_INFO* pList, int idx) {
    int i = 0;
    NODE* pTmp = pList->pHead->next;
    while (pTmp != pList->pTail) {
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

NODE* FindNode(LIST_INFO* pList, const char* pszKey, const char* (*pfGetKey)(void*)) {
    NODE* pTmp = pList->pHead->next;
    while (pTmp != pList->pTail) {
        if (strcmp(pfGetKey(pTmp->pData), pszKey) == 0)
            return pTmp;
        pTmp = pTmp->next;
    }
    return NULL;
}

void DeleteNode(LIST_INFO* pList, const char* pszKey, const char* (*pfGetKey)(void*)) {
    NODE* pDeleteNode = FindNode(pList, pszKey, pfGetKey);

    if (pDeleteNode == NULL)
    {
        printf("There's No Data: [%s]\n", pszKey);
        return;
    }

    pDeleteNode->prev->next = pDeleteNode->next;
    pDeleteNode->next->prev = pDeleteNode->prev;

    free(pDeleteNode->pData);
    free(pDeleteNode);
    pList->nSize--;

    printf("DeleteNode(): [%p], Size: [%d]\n", pDeleteNode, pList->nSize);
}

void ReleaseList(LIST_INFO* pList) {
    NODE* pTmp = pList->pHead;
    while (pTmp != NULL)
    {
        NODE* pDeleteNode = pTmp;
        pTmp = pTmp->next;
        free(pDeleteNode->pData);
        free(pDeleteNode);
        pList->nSize--;
        printf("ReleaseList(): [%p], Size: [%d]\n", pDeleteNode, pList->nSize);
    }
}