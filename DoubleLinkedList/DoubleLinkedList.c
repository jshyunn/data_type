#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct USERDATA {
    const char* (*GetName)(void*);

    char szName[64];
    char szPhone[64];
} USERDATA;

typedef struct NODE {
    void* pData;

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

void InsertBefore(NODE* pPivotNode, void* pData) {
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));

    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->next = pPivotNode;
    pNewNode->prev = pPivotNode->prev;
    pNewNode->pData = pData;

    pPivotNode->prev = pNewNode;
    pNewNode->prev->next = pNewNode;
    g_nSize++;
}

void InsertAtHead(void* pData) {
    InsertBefore(g_pHead->next, pData);

    printf("InsertAtHead(): [%p]\n", pData);
}

void InsertAtTail(void* pData) {
    InsertBefore(g_pTail, pData);

    printf("InsertAtTail(): [%p]\n", pData);
}

void InsertAt(int idx, void* pData) {
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
            InsertBefore(pTmp, pData);
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
        USERDATA* pUser = pTmp->pData;
        if (strcmp(pUser->GetName(pUser), pszKey) == 0) return pTmp;
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
        {
            USERDATA* pUser = pTmp->pData;
            printf("Prev: [%p], Curr: [%p], Next: [%p], Name: [%s]\n", pTmp->prev, pTmp, pTmp->next, pUser->GetName(pUser));
        }

        pTmp = pTmp->next;
    }
}

const char* GetNameFromUserData(const USERDATA* pData) {
    return pData->szName;
}

USERDATA* CreateUserData(const char* pszName, const char* pszPhone) {
    USERDATA* pData = (USERDATA*)malloc(sizeof(USERDATA));
    memset(pData, 0, sizeof(USERDATA));

    strcpy_s(pData->szName, sizeof(pData->szName), pszName);
    strcpy_s(pData->szPhone, sizeof(pData->szPhone), pszPhone);

    pData->GetName = GetNameFromUserData;
    return pData;
}

int main()
{
    InitList();

    USERDATA* pUser = NULL;
    pUser = CreateUserData("Seunghyun", "010-1111-1111");
    InsertAtHead(pUser);
    pUser = CreateUserData("JSH", "010-2222-2222");
    InsertAtHead(pUser);

    PrintList();

    ReleaseList();
}
