#pragma once

typedef struct NODE {
    void* pData;

    struct NODE* prev;
    struct NODE* next;
} NODE;

typedef struct LIST_INFO {
    NODE* pHead;
    NODE* pTail;
    int nSize;
} LIST_INFO;

void InitList(LIST_INFO*);
void InsertBefore(LIST_INFO*, NODE*, void*);
void InsertAtHead(LIST_INFO*, void* pData);
void InsertAtTail(LIST_INFO*, void* pData);
void InsertAt(LIST_INFO*, int idx, void* pData);
int GetSize(LIST_INFO*);
int GetLength(LIST_INFO*);
int isEmpty(LIST_INFO*);
NODE* GetAt(LIST_INFO*, int idx);
NODE* FindNode(LIST_INFO*, const char* pszKey, const char* (*pfGetKey)(void*));
void DeleteNode(LIST_INFO*, const char* pszKey, const char* (*pfGetKey)(void*));
void ReleaseList(LIST_INFO*);