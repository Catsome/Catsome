/*  ��˺BST
��һ�ó�ʼΪ�յĶ����������Binary Search Tree, BST���������ɲ����ɾ����������������Ķ��������.
�����ʽ:
�����һ��Ϊһ������ T����ʾ������Ŀ�����T�У�ÿ��ΪInsert K����ʾ��������K����Remove K����ʾɾ������K����T������2��10^5�����߲�����10^4��

�����ʽ:
���������������õ��Ķ�����������и����к��ȸ����У�������ÿ��������һ���ո���������֮���ÿ��м����

��������:
16
Insert 17
Insert 31
Insert 13
Insert 11
Insert 20
Insert 35
Insert 25
Insert 8
Insert 4
Insert 11
Insert 24
Insert 40
Insert 27
Insert 9
Remove 17
Remove 13
�������:
4 8 9 11 20 24 25 27 31 35 40

20 11 8 4 9 31 25 24 27 35 40
*/
#include <cstdio>
#include <cstring>

struct BSTNode
{
    int key;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* root = NULL;

bool insertInBST(BSTNode*& root, int key)   //����rootΪ����BST�в���key���ɹ�����true������false
{
    if (!root){
        root = new BSTNode;
        root->key = key;
        root->left = root->right = NULL;
        return true;
    }
    if (key == root->key){
        return false;
    }


    if (key < root->key){
        return insertInBST(root->left, key);
    }
    else{
        return insertInBST(root->right, key);
    }
}

bool deleteInBST(BSTNode*& root, int key)
{
    if (!root){ //�ݹ���ڣ�Ŀ�겻���ڣ�ɾ��ʧ��
        return false;
    }
    if (key == root->key){  //�ݹ���ڣ��ҵ�Ŀ�꣬����ɾ��
        if (root->left == NULL && root->right == NULL){ //���ΪҶ���
            delete root;
            root = NULL;
        }
        else if (root->left != NULL && root->right != NULL){ //�����������
            BSTNode* p = root->right;
            while (p->left){    //������������С���
                p = p->left;
            }
            root->key = p->key;
            deleteInBST(root->right, p->key);    //��ɾ��һ���ɹ�
        }
        else{   //�����һ����
            BSTNode* p = root;
            if (root->left){
                root = root->left;
            }
            else{
                root = root->right;
            }
            delete p;
        }

        return true;
    }

    if (key < root->key){
        return deleteInBST(root->left, key);
    }
    else{
        return deleteInBST(root->right, key);
    }
}

void preorderAndPrint(BSTNode* root)
{
    if (root){
        printf("%d ", root->key);
        preorderAndPrint(root->left);
        preorderAndPrint(root->right);
        return;
    }
    else
        return;
}

void inorderAndPrint(BSTNode* root)
{
    if (root){
        inorderAndPrint(root->left);
        printf("%d ", root->key);
        inorderAndPrint(root->right);
        return;
    }
    else
        return;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; ++i){
        char operation[7];
        int K;
        scanf("%s%d", operation, &K);
        if (!strcmp(operation, "Insert")){
            insertInBST(root, K);
        }
        else{
            deleteInBST(root, K);
        }
    }

    inorderAndPrint(root);
    printf("\n\n");
    preorderAndPrint(root);

    return 0;
}
