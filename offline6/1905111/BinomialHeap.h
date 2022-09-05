#include <iostream>
#define ii pair<int, int>
using namespace std;

// implement node
template <typename T>
struct Node
{
    Node<T> *parent, *child, *sibling;
    T key;
    int degree;

    Node()
    {
        this->key = ii(0,0);
        this->degree = 0;
        this->parent = NULL;
        this->child = NULL;
        this->sibling = NULL;
    }
    // for initializing head
    Node(T key)
    {
        this->key = key;
        this->degree = 0;
        this->parent = NULL;
        this->child = NULL;
        this->sibling = NULL;
    }
};

template <typename T>
class BinomialHeap
{
    Node<T> *root;
    Node<T> *mergeRoots(BinomialHeap<T> *, BinomialHeap<T> *);
    void binomialLink(Node<T> *, Node<T> *);

public:
    BinomialHeap();
    Node<T> *getMinimum();
    void unionHeap(BinomialHeap<T> *);
    void insert(Node<T> *);
    void insert(T k){
        Node<T> *newNode = new Node<T>(k);
        this->insert(newNode);
    }
    Node<T> *extractMin();
    void decreaseKey(Node<T> *, T);
    void deleteNode(Node<T> *);
    void display()
    {
        displayHelp(this->root);
    }
    void displayHelp(Node<T> *k)
    {
        if (k == NULL)
            return;
        cout << k->key << " ";
        displayHelp(k->sibling);
        cout << endl;
        displayHelp(k->child);
    }

    bool isEmpty(){ return this->root == NULL; }
};

template <typename T>
void BinomialHeap<T>::binomialLink(Node<T> *y, Node<T> *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->degree = z->degree + 1;
    z->child = y;
}

template <typename T>
Node<T> *BinomialHeap<T>::mergeRoots(BinomialHeap<T> *y, BinomialHeap<T> *z)
{
    Node<T> *ret, *temp, *left, *right;
    ret = new Node<T>();
    temp = ret;
    left = y->root;
    right = z->root;

    if (left == NULL)
        return right;
    if (right == NULL)
        return left;

    while (left != NULL || right != NULL)
    {
        if (left == NULL)
        {
            // take right
            temp->sibling = right;
            right = right->sibling;
            temp = temp->sibling;
        }
        else if (right == NULL)
        {
            // take left
            temp->sibling = left;
            left = left->sibling;
            temp = temp->sibling;
        }
        else
        {
            // take left if key is smaller
            if (left->degree < right->degree)
            {
                temp->sibling = left;
                left = left->sibling;
                temp = temp->sibling;
            }
            else
            {
                temp->sibling = right;
                right = right->sibling;
                temp = temp->sibling;
            }
        }
    }
    return ret->sibling;
}

// implement makeHeap
template <typename T>
BinomialHeap<T>::BinomialHeap()
{
    this->root = NULL;
}

// implement minimum

template <typename T>
Node<T> *BinomialHeap<T>::getMinimum()
{
    Node<T> *min = this->root;
    Node<T> *x = this->root;
    while (x != NULL)
    {
        if (x->key < min->key)
        {
            min = x;
        }
        x = x->sibling;
    }
    return min;
}

// implement union
template <typename T>
void BinomialHeap<T>::unionHeap(BinomialHeap<T> *newHeap)
{
    BinomialHeap<T> *ret = new BinomialHeap();
    // cout << "there"<< endl;
    ret->root = mergeRoots(this, newHeap);
    // cout << "here" << endl;
    if (ret->root == NULL)
    {
        this->root = NULL;
        return;
    }
    Node<T> *prev, *x, *next;
    prev = NULL;
    x = ret->root;
    next = x->sibling;

    while (next != NULL)
    {
        if (x->degree != next->degree || (next->sibling != NULL && (next->sibling)->degree == x->degree))
        {
            prev = x;
            x = next;
        }
        else if (x->key <= next->key)
        {
            x->sibling = next->sibling;
            binomialLink(next, x);
        }
        else
        {
            if (prev == NULL)
                ret->root = next;
            else
                prev->sibling = next;

            binomialLink(x, next);
            x = next;
        }
        next = x->sibling;
    }
    this->root = ret->root;
}
// implement insert
template <typename T>
void BinomialHeap<T>::insert(Node<T> *x)
{
    BinomialHeap<T> *newHeap = new BinomialHeap<T>();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    newHeap->root = x;
    this->unionHeap(newHeap);
}

// implement extractMin
template <typename T>
Node<T> *BinomialHeap<T>::extractMin()
{
    Node<T> *min = this->getMinimum();
    Node<T> *prev = NULL;

    Node<T> *x = this->root;
    while (x != min)
    {
        prev = x;
        x = x->sibling;
    }
    if (prev == NULL)
    {
        this->root = x->sibling;
    }
    else
    {
       
        Node<T> *a = x->sibling;
        prev->sibling = a;
        // prev->sibling = x->sibling;
      
    }
 

    // get reverse of min's children
    Node<T> *temp = min->child;
    Node<T> *back = NULL;
    while (temp != NULL)
    {
        Node<T> *forward = temp->sibling;
        temp->sibling = back;
        back = temp;
        temp = forward;
    }

    BinomialHeap<T> *newHeap = new BinomialHeap<T>();
    newHeap->root = back;
    this->unionHeap(newHeap);

    return min;
}

// implement decrease-key
template <typename T>
void BinomialHeap<T>::decreaseKey(Node<T> *x, T k)
{
    if (k > x->key)
    {
        cout << "New key is greater than current key" << endl;
        return;
    }
    x->key = k;
    Node<T> *y = x;
    Node<T> *z = y->parent;

    while (z != NULL && y->key < z->key)
    {
        swap(y->key, z->key);
        y = z;
        z = y->parent;
    }
}

// implement delete
template <typename T>
void BinomialHeap<T>::deleteNode(Node<T> *x)
{
    this->decreaseKey(x, -1e9);
    this->extractMin();
}