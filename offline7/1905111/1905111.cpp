#include <iostream>
#include "RedBlackTree.h"

using namespace std;

int main()
{
    freopen("input.in", "r", stdin);
    int n, e, x, r;
    cin >> n;
    RedBlackTree<int> *rbt = new RedBlackTree<int>();
    for (int i = 0; i < n; i++)
    {
        cin >> e >> x;
        cout << e << " " << x << " ";
        // if(x==40)rbt->inorderTraversal();
        switch (e)
        {
        case 0:
            cout << rbt->deleteElement(x) << endl;
            break;
        case 1:
            cout << rbt->insertElement(x) << endl;
            break;
        case 2:
            cout << (rbt->search(x) != rbt->nullNode) << endl;
            break;
        case 3:
            cout << rbt->countLessThan(x) << endl;
            break;

        default:
            break;
        }
        
        
    }
}


// parent = z->parent;
//         grandparent = parent->parent;

//         if (grandparent->left == parent)
//         {
//             uncle = grandparent->right;
//             if (uncle->color == RED)
//             {
//                 uncle->color = parent->color = BLACK;
//                 grandparent->color = RED;
//                 z = grandparent;
//             }
//             else
//             {
//                 if (z == parent->right)
//                 { // triangle case
//                     z = parent;
//                     this->leftRotate(z);
//                 }
//                 parent->color = BLACK;
//                 grandparent->color = RED;
//                 this->rightRotate(grandparent);
//             }
//         }
//         else
//         {
//             uncle = grandparent->left;
//             if (uncle->color == RED)
//             {
//                 uncle->color = parent->color = BLACK;
//                 grandparent->color = RED;
//                 z = grandparent;
//             }
//             else
//             {
//                 if (z == parent->left)
//                 { // triangle case
//                     z = parent;
//                     this->rightRotate(z);
//                 }
//                 parent->color = BLACK;
//                 grandparent->color = RED;
//                 this->leftRotate(grandparent);
//             }
//         }


// void RedBlackTree<T>::leftRotate(treeNode<T> *x)
// {
//     // x
//     //    \
//     //       y
//     //      /
//     //    z
//     treeNode<T> *y = x->right;
//     treeNode<T> *z = y->left;
//     z->parent = x;
//     x->right = z;

//     if (x->parent == nullNode)
//         root = y;
//     else if (x == x->parent->left)
//         x->parent->left = y;
//     else
//         x->parent->right = y;
//     y->parent = x->parent;

//     y->left = x;
//     x->parent = y;
// }

// template <typename T>
// void RedBlackTree<T>::rightRotate(treeNode<T> *x)
// {
//     //      x
//     //   /
//     // y
//     //  \    
//     //   z

//     treeNode<T> *y = x->left;
//     treeNode<T> *z = y->right;
//     z->parent = x;
//     x->left = z;
//     if(x->key == 34)cout << x->parent->left->parent->key <<  "a                    ";
//     if (x->parent == nullNode)
//         root = y;
//     else if (x == x->parent->left)
//         x->parent->left = y;
//     else
//         x->parent->right = y;
//     y->parent = x->parent;

//     y->right = x;
//     x->parent = y;
// }