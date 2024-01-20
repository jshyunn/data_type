#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct NODE {
    char szData[64];

    struct NODE* parent;
    struct NODE* left;
    struct NODE* right;
} NODE;

NODE* g_pRoot;
int g_nSize;

NODE* CreateNode(const char* pszNewData) {
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszNewData);
    return pNewNode;
}

void InsertNode(NODE* pNewNode) {
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
                pNewNode->parent = pTmp;
                break;
            }
            else
            {
                pTmp = pTmp->right;
            }
        }
        else if (strcmp(pNewNode->szData, pTmp->szData) < 0)
        {
            if (pTmp->left == NULL)
            {
                pTmp->left = pNewNode;
                pNewNode->parent = pTmp;
                break;
            }
            else
            {
                pTmp = pTmp->left;
            }
        }
        else
            break;
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

 void ReinsertNode(NODE* pNow) {
    if (pNow == NULL) return;

    g_nSize--;
    InsertNode(pNow);

    ReinsertNode(pNow->right);
    ReinsertNode(pNow->left);
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

void DeleteNode(const char* pszDeleteData) {
    NODE* pDeleteNode = FindNode(pszDeleteData);

    if (pDeleteNode == NULL)
    {
        printf("Invalid Data: [%s]", pszDeleteData);
        return;
    }

    if (strcmp(pDeleteNode->parent->szData, pDeleteNode->szData) > 0)
        pDeleteNode->parent->left = NULL;
    else
        pDeleteNode->parent->right = NULL;

    ReinsertNode(pDeleteNode->right);
    ReinsertNode(pDeleteNode->left);

    printf("Delete: [%p], Data: [%s]\n", pDeleteNode, pDeleteNode->szData);
    free(pDeleteNode);
    g_nSize--;
}

void ReleaseTree(NODE* pNow) {
    if (pNow == NULL) return;

    ReleaseTree(pNow->left);
    ReleaseTree(pNow->right);

    printf("Release: [%p], Data: [%s]\n", pNow, pNow->szData);
    free(pNow);
}

void PrintTree(NODE* pNow) {
    if (pNow == NULL) return;

    PrintTree(pNow->left);

    printf("Parent: [%p], Left: [%p], Now: [%p], Right: [%p], Data: [%s]\n", pNow->parent, pNow->left, pNow, pNow->right, pNow->szData);

    PrintTree(pNow->right);
}

int main()
{
    NODE* node1 = CreateNode("1번 노드");
    NODE* node2 = CreateNode("2번 노드");
    NODE* node3 = CreateNode("3번 노드");
    NODE* node4 = CreateNode("4번 노드");
    NODE* node5 = CreateNode("5번 노드");
    NODE* node6 = CreateNode("6번 노드");
    NODE* node7 = CreateNode("7번 노드");
    NODE* node8 = CreateNode("8번 노드");
    NODE* node9 = CreateNode("9번 노드");

    InsertNode(node4);
    InsertNode(node5);
    InsertNode(node3);
    InsertNode(node2);
    InsertNode(node1);
    InsertNode(node9);
    InsertNode(node7);
    InsertNode(node8);
    InsertNode(node6);
    printf("%d\n", g_nSize);

    PrintTree(g_pRoot);

    DeleteNode("7번 노드");
    printf("%d\n", g_nSize);
    DeleteNode("3번 노드");
    printf("%d\n", g_nSize);

    PrintTree(g_pRoot);

    ReleaseTree(g_pRoot);
}
