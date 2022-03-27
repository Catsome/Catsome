/*  手撕BST
对一棵初始为空的二叉查找树（Binary Search Tree, BST）进行若干插入或删除操作，请输出最后的二叉查找树.
输入格式:
输入第一行为一个整数 T，表示操作数目。随后T行，每行为Insert K（表示插入整数K）或Remove K（表示删除整数K）。T不超过2×10^5，树高不超过10^4。

输出格式:
输出经上述操作后得到的二叉查找树的中根序列和先根序列，序列中每个整数后一个空格，两个序列之间用空行间隔。

输入样例:
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
输出样例:
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

bool insertInBST(BSTNode*& root, int key)   //在以root为根的BST中插入key，成功返回true，否则false
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
    if (!root){ //递归出口，目标不存在，删除失败
        return false;
    }
    if (key == root->key){  //递归出口，找到目标，进行删除
        if (root->left == NULL && root->right == NULL){ //结点为叶结点
            delete root;
            root = NULL;
        }
        else if (root->left != NULL && root->right != NULL){ //结点有两子树
            BSTNode* p = root->right;
            while (p->left){    //找右子树中最小结点
                p = p->left;
            }
            root->key = p->key;
            deleteInBST(root->right, p->key);    //此删除一定成功
        }
        else{   //结点有一子树
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
