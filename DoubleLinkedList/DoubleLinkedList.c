#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct USERDATA {
    char szName[64];
    char szPhone[64];
} USERDATA;

typedef struct NODE {
    char szData[64];

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
    strcpy_s(g_pHead->szData, sizeof(g_pHead->szData), "Dummy Head");
    strcpy_s(g_pTail->szData, sizeof(g_pTail->szData), "Dummy Tail");

    g_nSize = 2;

    printf("pHead: [%p], pTail: [%p], Size: [%d]\n", g_pHead, g_pTail, g_nSize);
}

void InsertBefore(NODE* pPivotNode, const char* pszNewData) {
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));

    memset(pNewNode, 0, sizeof(NODE));

    pNewNode->next = pPivotNode;
    pNewNode->prev = pPivotNode->prev;
    strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszNewData);

    pPivotNode->prev = pNewNode;
    pNewNode->prev->next = pNewNode;
    g_nSize++;
}

void InsertAtHead(const char* pszNewData) {
    InsertBefore(g_pHead->next, pszNewData);

    printf("InsertAtHead(): [%s]\n", pszNewData);
}

void InsertAtTail(const char* pszNewData) {
    InsertBefore(g_pTail, pszNewData);

    printf("InsertAtTail(): [%s]\n", pszNewData);
}

void InsertAt(int idx, const char* pszNewData) {
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
            InsertBefore(pTmp, pszNewData);
        }
        pTmp = pTmp->next;
        i++;
    }
    printf("InsertAt(): [%d], [%s]\n", idx, pszNewData);
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

NODE* FindNode(const char* pszFindData) {
    NODE* pTmp = g_pHead->next;
    while (pTmp != g_pTail) {
        if (strcmp(pTmp->szData, pszFindData) == 0) return pTmp;
        pTmp = pTmp->next;
    }
    return NULL;
}

void DeleteNode(const char* pszDeleteData) {
    NODE* pDeleteNode = FindNode(pszDeleteData);

    if (pDeleteNode == NULL)
    {
        printf("There's No Data: [%s]\n", pszDeleteData);
        return;
    }

    pDeleteNode->prev->next = pDeleteNode->next;
    pDeleteNode->next->prev = pDeleteNode->prev;
    
    free(pDeleteNode);
    g_nSize--;

    printf("DeleteNode(): [%p], Data: [%s], Size: [%d]\n", pDeleteNode, pszDeleteData, g_nSize);
}

void ReleaseList() {
    NODE* pTmp = g_pHead;
    while (pTmp != NULL)
    {
        NODE* pDeleteNode = pTmp;
        pTmp = pTmp->next;
        free(pDeleteNode);
        g_nSize--;
        printf("Release: [%p], Size: [%d]\n", pDeleteNode, g_nSize);
    }
}

void PrintList() {
    NODE* pTmp = g_pHead;
    while (pTmp != NULL)
    {
        printf("Prev: [%p], Curr: [%p], Next: [%p], Data: [%s]\n", pTmp->prev, pTmp, pTmp->next, pTmp->szData);

        pTmp = pTmp->next;
    }
}

int main()
{
    InitList();

    PrintList();

    InsertAtHead("Seunghyun");

    PrintList();

    InsertAtTail("JSH");

    PrintList();

    DeleteNode("Seunghyun");
    DeleteNode("JS");

    PrintList();

    InsertAt(2, "TEST1");
    InsertAt(1, "TEST2");

    PrintList();

    GetAt(2);
    GetAt(1);

    ReleaseList();
}
