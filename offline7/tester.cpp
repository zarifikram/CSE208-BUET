#include <iostream>
#include "RedBlackTree.h"

using namespace std;

int main()
{
    treeNode<int> *nullNode = treeNode<int>::getNullNode();
    treeNode<int> *a = new treeNode<int>(10);
    treeNode<int> *b = new treeNode<int>(4);
    treeNode<int> *c = new treeNode<int>(2);
    treeNode<int> *d = new treeNode<int>(5);

    RedBlackTree<int> *rbt = new RedBlackTree<int>();
    cout << "funn" << endl;
    rbt->insert(a);
    rbt->insert(b);
    rbt->insert(c);
    rbt->insert(d);
    rbt->insertElement(36);
    rbt->insertElement(21);
    rbt->insertElement(-5);
    rbt->insertElement(-12);
    // rbt->inorderTraversal();
    // cout << rbt->search(4)->key << " " << cout << rbt->search(11)->key;
    rbt->deleteElement(10);
    // cout << rbt->deletetreeNode(a);
    // rbt->inorderTraversal();
    rbt->deletetreeNode(b);
    // rbt->deleteElement(4);
    // rbt->inorderTraversal();
    rbt->deletetreeNode(c);
    // rbt->inorderTraversal();
    rbt->deletetreeNode(d);
    rbt->inorderTraversal();

}