#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "mylist.h"

typedef struct USERDATA {
    const char* (*GetName)(void*);

    char szName[64];
    char szPhone[64];
} USERDATA;

void PrintList(LIST_INFO* pList) {
    NODE* pTmp = pList->pHead;
    while (pTmp != NULL)
    {
        if (pTmp == pList->pHead || pTmp == pList->pTail)
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
    USERDATA* pUser = NULL;

    LIST_INFO userList01 = { 0 };
    InitList(&userList01);

    pUser = CreateUserData("Seunghyun", "010-1111-1111");
    InsertAtHead(&userList01, pUser);
    pUser = CreateUserData("JSH", "010-2222-2222");
    InsertAtTail(&userList01, pUser);

    LIST_INFO userList02 = { 0 };
    InitList(&userList02);

    pUser = CreateUserData("TEST01", "010-1111-1111");
    InsertAtHead(&userList02, pUser);
    pUser = CreateUserData("TEST02", "010-2222-2222");
    InsertAtTail(&userList02, pUser);
    
    PrintList(&userList01);
    PrintList(&userList02);

    DeleteNode(&userList01, "JSH", GetNameFromUserData);
    DeleteNode(&userList02, "TEST01", GetNameFromUserData);

    ReleaseList(&userList01);
    ReleaseList(&userList02);
}
