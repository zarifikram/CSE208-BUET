#include <iostream>
#define RED 0
#define BLACK 1

using namespace std;

template <typename T>
struct treeNode
{

    treeNode<T> *parent, *left, *right;
    T key;
    int color;

    treeNode()
    {
        this->key = 0;
        this->color = RED;
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
    }

    treeNode(T key)
    {
        treeNode<T> *nullNode = treeNode<T>::getNullNode();
        this->key = key;
        this->color = RED;
        this->parent = nullNode;
        this->left = nullNode;
        this->right = nullNode;
    }
    treeNode(int color, int ok)
    {
        this->key = NULL;
        this->color = color;
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
    }

    static treeNode<T> *getNullNode()
    {
        return new treeNode<T>(BLACK, 1e9);
    }
};

template <typename T>
class RedBlackTree
{
private:
    treeNode<T> *root;
    void leftRotate(treeNode<T> *);
    void rightRotate(treeNode<T> *);
    void insertFixup(treeNode<T> *);
    void deleteFixup(treeNode<T> *);
    treeNode<T> *treeSuccessor(treeNode<T> *);
    void inorderHelper(treeNode<T> *);
    treeNode<T> *searchHelper(treeNode<T> *, T);
    void transplant(treeNode<T> *, treeNode<T> *);
    int countLessThanHelper(treeNode<T> *, T);

public:
    treeNode<T> *nullNode = new treeNode<T>(BLACK, 1e9);
    treeNode<T> *deletetreeNode(treeNode<T> *);
    void insert(treeNode<T> *);
    treeNode<T> *search(T);
    bool deleteElement(T);
    bool insertElement(T);
    void inorderTraversal();
    bool isEmpty() { return this->root == nullNode; };
    RedBlackTree() { this->root = nullNode; }
    int countLessThan(T);
};

template <typename T>
void RedBlackTree<T>::leftRotate(treeNode<T> *x)
{
    // x
    //    \
    //       y
    //      /
    //    z
    treeNode<T> *y = x->right;

    x->right = y->left;

    if (y->left != nullNode)
        y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == nullNode)
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rightRotate(treeNode<T> *x)
{
    //      x
    //   /
    // y
    //  \    
    //   z

    treeNode<T> *y = x->left;

    x->left = y->right;

    if (y->right != nullNode)
        y->right->parent = x;
    y->parent = x->parent;

    if (x->parent == nullNode)
        this->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

template <typename T>
void RedBlackTree<T>::insert(treeNode<T> *z)
{

    treeNode<T> *y = nullNode;
    treeNode<T> *x = this->root;
    while (x != nullNode)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if (y == nullNode)
        this->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = z->right = nullNode;
    z->color = RED;
    // if(z->key == 58) cout <<"jere   "<< (z->left == nullNode)<< " " << z->right->key << endl;
    this->insertFixup(z);
}

template <typename T>
void RedBlackTree<T>::insertFixup(treeNode<T> *z)
{

    treeNode<T> *parent, *grandparent, *uncle;
    while (z->parent->color == RED)
    {

        parent = z->parent;
        grandparent = parent->parent;

        if (z->parent->parent->left == z->parent)
        {
            uncle = z->parent->parent->right;
            if (uncle->color == RED)
            {
                uncle->color = z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                { // triangle case
                    z = z->parent;
                    this->leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                this->rightRotate(z->parent->parent);
            }
        }
        else
        {
            uncle = z->parent->parent->left;
            if (uncle->color == RED)
            {
                uncle->color = z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                { // triangle case
                    z = z->parent;
                    this->rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                this->leftRotate(z->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
    // cout << z->color << endl;
}

template <typename T>
treeNode<T> *RedBlackTree<T>::deletetreeNode(treeNode<T> *z)
{

    treeNode<T> *y, *x, *deleted;
    deleted = z;
    y = z;
    int yColor = y->color;
    // cout << "               " <<(z->left->key) << " " << z->parent->key << " " << z->right->key <<"          " <<endl;
    if (z->left == nullNode)
    {
        x = z->right;
        this->transplant(z, z->right);
    }
    else if (z->right == nullNode)
    {
        x = z->left;
        this->transplant(z, z->left);
    }
    else
    {
        y = this->treeSuccessor(z->right);
        // cout << y->key << " ";
        yColor = y->color;
        x = y->right;
        // cout << y->key << " " <<(x == nullNode) << endl;
        if (y->parent == z)
            x->parent = y;
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yColor == BLACK)
        deleteFixup(x);
    return deleted;
}

template <typename T>
treeNode<T> *RedBlackTree<T>::treeSuccessor(treeNode<T> *z)
{
    while (z->left != nullNode)
        z = z->left;
    return z;
}

template <typename T>
void RedBlackTree<T>::deleteFixup(treeNode<T> *x)
{
    //  cout <<     "               " << (x->key) << " " << x->parent->key<<"          " <<endl;

    while (x->color == BLACK && x != this->root)
    {

        if (x == x->parent->left)
        {
            treeNode<T> *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    this->rightRotate(w);
                    // cout << "               " << (x->parent->key) << " " << w->key << " " << w->right->key << "          " << endl;
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = this->root;
            }
        }
        else
        {

            treeNode<T> *w = x->parent->left;
            if (w->color == RED)
            {

                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    this->leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = this->root;
            }
        }
    }
    // cout << "hsafa";
    x->color = BLACK;
}

template <typename T>
treeNode<T> *RedBlackTree<T>::search(T value)
{
    if (this->root == nullNode)
        return this->root;
    return searchHelper(this->root, value);
}

template <typename T>
treeNode<T> *RedBlackTree<T>::searchHelper(treeNode<T> *z, T value)
{
    // cout << "here rn " <<  z->key << endl;
    if (z == nullNode || z->key == value)
        return z;
    else if (z->key < value)
        return searchHelper(z->right, value);
    else
        return searchHelper(z->left, value);
}

template <typename T>
bool RedBlackTree<T>::deleteElement(T value)
{
    treeNode<T> *deletedElement = search(value);
    if (deletedElement == nullNode)
        return false;
    this->deletetreeNode(deletedElement);
    return true;
}

template <typename T>
bool RedBlackTree<T>::insertElement(T value)
{
    if (this->search(value) != this->nullNode)
        return false;
    this->insert(new treeNode<T>(value));
    return true;
}

template <typename T>
void RedBlackTree<T>::inorderTraversal()
{
    this->inorderHelper(this->root);
}

template <typename T>
void RedBlackTree<T>::inorderHelper(treeNode<T> *z)
{
    if (z == nullNode)
        return;
    this->inorderHelper(z->left);
    cout << z->key << " " << (z->color == 0 ? "RED" : "BLACK") << endl;
    this->inorderHelper(z->right);
}

template <typename T>
void RedBlackTree<T>::transplant(treeNode<T> *u, treeNode<T> *v)
{
    if (u->parent == this->nullNode)
    {
        this->root = v;
    }
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

template <typename T>
int RedBlackTree<T>::countLessThan(T value)
{
    return this->countLessThanHelper(this->root, value);
}

template <typename T>
int RedBlackTree<T>::countLessThanHelper(treeNode<T> *z, T value)
{
    if (z == nullNode)
        return 0;
    return (z->key < value) + this->countLessThanHelper(z->left, value) + countLessThanHelper(z->right, value);
}