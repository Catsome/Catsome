
# **二叉查找树 BinarySearchTree(BST)**

## **一.概念**

### **1.定义**

（1）直接定义：二叉查找树是中根序列为递增序（也可以为递减）的二叉树。  
（2）递归定义：  
空树是一颗二叉查找树；  
如果某二叉查找树的左子树不空则左子树上所有结点的值小于根节点，如果右子树不空则右子树上所有结点的值大于根节点；  
二叉查找树的左右子树也是二叉查找树。

### **2.特点**

（1）二叉查找树中没有重复元素；  
（2）左子树不空则左子树上所有结点的值小于根节点，右子树不空则右子树上所有结点的值大于根节点。

### **3.逻辑结构**

（1）树形结构就是普通的二叉树；  
（2）结点至少包含值、左右指针三个域

### **4.常见操作**

（1）插入：从根节点开始，待插入值小于当前结点值则向左子树走，大于则向右子树走，直到：  
待插入值等于当前结点值——说明已在树中，无需插入，操作结束；  
当前结点为空——找到了插入位置，将当前结点值赋为待插入值，操作结束。 

（2）查找：从根节点开始，待查找值小于当前结点值则向左子树走，大于则向右子树走，直到：  
待查找值等于当前结点值——查找成功，返回当前结点，操作结束；  
当前结点为空——查找失败，操作结束。  

（3）删除：从根节点开始，待删除值小于当前结点值则向左子树走，大于则向右子树走，直到：  
当前结点为空——无需删除，操作结束；  
待查找值等于当前结点值——查找成功，此时需要分三种情况处理：  
若结点为叶结点则直接删除；
若结点有一个子结点，则用子结点代替当前结点位置，同时删去当前结点；  
若结点有两个子结点，则用其右子树内中根序的第一个结点（右子树中最小的结点）覆盖它，再从右子树中删去这一结点（这一结点最多只会有一个右子结点）。

## **二.存储结构和操作实现**

### **1.C/C++实现**

C/C++中这一数据结构可以直接用struct/class和指针来模拟，也可以用静态数组模拟。  
**插入、删除两个操作都以查找为基础，所以或许可以先把查找实现为函数，再让其余两种操作调用即可（待实现）。**  
查找操作可以写成递归或迭代，递归逻辑简单一些，但迭代效率更高。  
代码模板如下：  
(1)用指针模拟——迭代
该版本待完善，涉及了许多指针和引用的易错点，逻辑略有复杂，之后再作讨论。
```
#include <cstdio>

struct BSTNode
{
    int key;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* root = NULL;

BSTNode* searchInBST(BSTNode* p, int key)    //在以p为根的BST中查找key，返回结果指针
{
    while (p){  //因p为按值传递才可直接使用
        if (key < p->key){
            p = p->left;
        }
        else if (key > p->key){
            p = p->right;
        }
        else{   //已找到
            return p;
        }
    }

    return p;   //此处p一定为空，查找失败
}

bool insertInBST(BSTNode*& root, int key)   //root可能需要变化（空树），不能按值传递
{
    BSTNode* pnew = new BSTNode;
    pnew->left = pnew->right = NULL;
    pnew->key = key;

    BSTNode* p = root;
    if (!p){    //空树，直接插入
        root = pnew;
    }
    else{
        while (p){      //不能直接调用search，需要找父结点来连接新节点
            if (key < p->key){
                if (p->left){
                    p = p->left;
                }
                else{
                    p->left = pnew;
                    return true;
                }
            }
            else if (key > p->key){
                if (p->right){
                    p = p->right;
                }
                else{
                    p->right = pnew;
                    return true;
                }
            }
            else{   //已找到
                return false;
            }
        }
    }
}

bool deleteInBST(BSTNode*& root, int key)    //删除，未完成
{
    BSTNode* p = searchInBST(root, key);
    //这里不能直接这样调用，因为虽然返回的指针值可以访问到需要删除的部分，但可能无法在delete之后将指向被删除结点的指针重置为NULL
    if (p){ //找到目标，进行删除
        if (p->left && p->right){   //结点有两子树
            
        }
        else if ((!p->left) && (!p->right)){    //结点为叶结点
            delete p;
        }
        else{   //结点有一子树
            if (p->left){
                p->key = p->left->key;
                delete p->left;
                p->left = NULL;
            }
            else{
                p->key = p->right->key;
                delete p->right;
                p->right = NULL;
            }
        }
    }
    else{
        return false;   //目标结点不存在，删除失败
    }
}

```

(2)用指针模拟——递归
```
#include <cstdio>

struct BSTNode
{
    int key;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* root = NULL;

BSTNode* searchInBST(BSTNode* root, int key)    //在以root为根的BST中搜索key
{
    if (!root || root->key == key){ //递归出口
        return root;
    }

    if (key < root->key){
        return searchInBST(root->left, key);
    }
    else{
        return searchInBST(root->right, key);
    }
}

bool insertInBST(BSTNode*& root, int key)   //在以root为根的BST中插入key，成功返回true，否则false
{
    if (!root){ //递归出口，找到目标位置，插入成功
        root = new BSTNode;
        root->key = key;
        root->left = root->right = NULL;
        return true;
    }
    if (key == root->key){  //递归出口，已存在，插入失败
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
```