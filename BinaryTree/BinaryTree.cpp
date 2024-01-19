#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct NODE {
    char szData[64];

    struct NODE* left;
    struct NODE* right;
} NODE;

NODE* g_pRoot;
int g_nSize;

void InsertNode(const char* pszNewData) {
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszNewData);

    if (g_pRoot == NULL)
    {
        g_pRoot = pNewNode;
        return;
    }

    NODE* pTmp = g_pRoot;
    while (pTmp != NULL)
    {
        if (strcmp(pNewNode->szData, pTmp->szData) > 0)
        {
            if (pTmp->right == NULL)
            {
                pTmp->right = pNewNode;
                break;
            }
            else
            {
                pTmp = pTmp->right;
            }
        }
        else
        {
            if (pTmp->left == NULL)
            {
                pTmp->left = pNewNode;
                break;
            }
            else
            {
                pTmp = pTmp->left;
            }
        }
    }
    g_nSize++;
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

NODE* FindNode(const char* pszFindData) {
    NODE* pTmp = g_pRoot;
    while (pTmp != NULL)
    {
        if (strcmp(pszFindData, pTmp->szData) > 0)
        {
            pTmp = pTmp->right;
        }
        else if (strcmp(pszFindData, pTmp->szData) < 0)
        {
            pTmp = pTmp->left;
        }
        else
        {
            return pTmp;
        }
    }
    return NULL;
}

NODE* Up(NODE* pParent) {
    if (pParent == NULL) return NULL;

    NODE* pRight = Up(pParent->right);
    pRight->right = pRight->left;
    pRight->left = pParent->left;
    free(pParent);
    
    return pRight;
}

void DeleteNode(const char* pszDeleteData) {
    NODE* pDeleteNode = FindNode(pszDeleteData);

    if (pDeleteNode == NULL)
    {
        printf("Invalid Data: [%s]", pszDeleteData);
        return;
    }

    NODE* pRight = Up(pDeleteNode);
}

void ReleaseTree(NODE* pParent) {
    if (pParent == NULL) return;

    ReleaseTree(pParent->left);
    ReleaseTree(pParent->right);

    printf("Release: [%p], Data: [%s]\n", pParent, pParent->szData);
    free(pParent);
}

void PrintTree(NODE* pParent) {
    if (pParent == NULL) return;

    PrintTree(pParent->left);

    printf("Left: [%p], Now: [%p], Right: [%p], Data: [%s]\n", pParent->left, pParent, pParent->right, pParent->szData);

    PrintTree(pParent->right);
}

int main()
{
    InsertNode("5번 노드");
    InsertNode("4번 노드");
    InsertNode("7번 노드");
    InsertNode("6번 노드");
    InsertNode("8번 노드");

    PrintTree(g_pRoot);

    DeleteNode("7번 노드");

    PrintTree(g_pRoot);

    ReleaseTree(g_pRoot);
}
