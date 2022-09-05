#include <iostream>
#include <math.h>
#define ii pair<int, int>
using namespace std;

template <typename T>
struct fNode
{
    fNode<T> *parent, *child, *left, *right;
    T key;
    int degree;
    bool marked;

    fNode()
    {
        this->key = ii(0, 0);
        this->degree = 0;
        this - marked = false;
        this->parent = NULL;
        this->child = NULL;
        this->left = NULL;
        this->right = NULL;
    }
    // for initializing head
    fNode(T key)
    {
        this->key = key;
        this->degree = 0;
        this->marked = false;
        this->parent = NULL;
        this->child = NULL;
        this->left = NULL;
        this->right = NULL;
    }
};

template <typename T>
class FibonacciHeap
{
private:
    fNode<T> *min;
    void fibonacciLink(fNode<T> *, fNode<T> *);
    void cut(fNode<T> *, fNode<T> *);
    void cascadingCut(fNode<T> *);

public:
    int nfNodes;
    FibonacciHeap();
    FibonacciHeap(fNode<T> *);
    fNode<T> *getMinimum();
    void unionHeap(FibonacciHeap<T> *);
    void insert(fNode<T> *);
    void insert(T k)
    {
        fNode<T> *newfNode = new fNode<T>(k);
        this->insert(newfNode);
    }
    fNode<T> *extractMin();
    void decreaseKey(fNode<T> *, T);
    void deletefNode(fNode<T> *);
    bool isEmpty() { return this->min == NULL; }
    void display()
    {
        cout << "display start" << endl;
        displayHelper(this->min);
        cout << "display emd" << endl;
    }
    void displayHelper(fNode<T> *child)
    {
        if (child == NULL)
            return;
        fNode<T> *start = child;
        do
        {
            displayHelper(child->child);
            cout << child->key << " ";

            child = child->right;

        } while (start != child);
        cout << endl;
    }
};

template <typename T>
FibonacciHeap<T>::FibonacciHeap()
{
    this->min = NULL;
    this->nfNodes = 0;
}

template <typename T>
FibonacciHeap<T>::FibonacciHeap(fNode<T> *k)
{
    this->min = k;
    this->nfNodes = 1;
    k->parent = NULL;
    k->child = NULL;
    k->left = k;
    k->right = k;
}

template <typename T>
fNode<T> *FibonacciHeap<T>::getMinimum()
{
    return this->min;
}

template <typename T>
void FibonacciHeap<T>::unionHeap(FibonacciHeap<T> *h)
{
    // if h is empty do nothing
    // if ours is empty, make h min our min
    if (this->isEmpty())
    {
        this->min = h->min;
        this->nfNodes += h->nfNodes;
        return;
    }
    if (h->isEmpty())
        return;

    this->nfNodes += h->nfNodes;
    // cout << h->nfNodes << " " << this->nfNodes << " " << h->min->key << endl;
    // other wise join them
    fNode<T> *firstOfThis, *firstOfH, *lastOfThis, *lastOfH;
    firstOfThis = this->min;
    // cout << "there" << endl;
    lastOfThis = this->min->left;
    // cout << "here" << endl;
    firstOfH = h->min;
    lastOfH = h->min->left;

    firstOfThis->left = lastOfH;
    lastOfH->right = firstOfThis;

    lastOfThis->right = firstOfH;
    firstOfH->left = lastOfThis;

    // if the keys are snaller take h's min
    if (h->min->key < this->min->key)
        this->min = h->min;
}

template <typename T>
fNode<T> *FibonacciHeap<T>::extractMin()
{
    fNode<T> *z = this->min;
    // cout << "this is the min " << z->key << endl;
    if (z == NULL)
        return z;

    this->nfNodes -= 1;
    if (z->right == z)
    {
        this->min = NULL;
        // return z;
    }
    else
    {
        // remove z from root list
        fNode<T> *left = z->left;
        fNode<T> *right = z->right;
        left->right = right;
        right->left = left;
        this->min = right;
    }
    if (z->child != NULL)
    {
        // make z's child's parent null
        fNode<T> *child = z->child;
        child->parent = NULL;
        for (fNode<T> *child = z->child->right; child != z->child; child = child->right)
            child->parent = NULL;

        // add child to the list
        if (this->isEmpty()) // if min isn't stored
            this->min = child;
        else
        {
            fNode<T> *firstOfThis, *lastOfThis, *firstOfChild, *lastOfChild;
            firstOfThis = this->min;
            lastOfThis = this->min->left;
            firstOfChild = child;
            lastOfChild = child->left;

            firstOfThis->left = lastOfChild;
            lastOfChild->right = firstOfThis;

            lastOfThis->right = firstOfChild;
            firstOfChild->left = lastOfThis;
        }
    }
    
    
    if(this->min == NULL) { //if still min not found, must be the last element
        return z;
    }
    // consolidate
    int maxAuxiliarySize = 10 * ((int)floor(log2(this->nfNodes)) + 1);
    fNode<T> *auxArr[maxAuxiliarySize];
    int maxDegree = 0;
    for (int i = 0; i < maxAuxiliarySize; i++)
        auxArr[i] = NULL;

    fNode<T> *start, *curr;
    start = this->min;
    curr = start;

    do
    {
        // cout << " in extract " << endl;
        // this->display();
        int degree = curr->degree;
        fNode<T> *rightToCurr = curr->right;
        // cout << curr->key << " " << rightToCurr->key << endl;
        while (auxArr[degree] != NULL)
        {
            // cout << "inside while" << endl;
            fNode<T> *similiarToCurr = auxArr[degree];
            // cout << "while" << curr->key << " " << similiarToCurr->key << endl;

            if (curr->key > similiarToCurr->key)
                swap(curr, similiarToCurr);

            fibonacciLink(similiarToCurr, curr);
            // cout << "curr " << curr->key << " curr degree " << curr->degree << endl;
            auxArr[degree] = NULL;
            degree++;
        }
        auxArr[degree] = curr;
        maxDegree = max(maxDegree, degree);
        curr = rightToCurr;
    } while (curr != start);
    fNode<T> *previousfNode = auxArr[maxDegree];
    this->min = previousfNode;
    for (int i = 0; i < maxAuxiliarySize; i++)
    {
        if (auxArr[i] != NULL)
        {
            // cout << this->min->key << " " << this->min->degree << endl;
            // cout << auxArr[i]->key << " " << auxArr[i]->degree << " " << i;
            auxArr[i]->left = previousfNode;
            previousfNode->right = auxArr[i];
            if (auxArr[i]->key < this->min->key)
                this->min = auxArr[i];
            previousfNode = auxArr[i];
        }
    }

    // cout << "new min key " << this->min->key << endl;
    // cout << endl;
    return z;
}

template <typename T>
void FibonacciHeap<T>::fibonacciLink(fNode<T> *y, fNode<T> *z)
{
    y->parent = z;
    if (z->child == NULL)
    {
        z->child = y;
        y->right = y;
        y->left = y;
    }
    else
    {
        fNode<T> *firstOfZ = z->child;
        fNode<T> *lastOfZ = z->child->left;

        firstOfZ->left = y;
        y->right = firstOfZ;
        lastOfZ->right = y;
        y->left = lastOfZ;
    }
    z->degree++;
    y->marked = false;
}

template <typename T>
void FibonacciHeap<T>::decreaseKey(fNode<T> *x, T k)
{
    if (k > x->key)
    {
        cout << "New key is greater than current key" << endl;
        return;
    }
    x->key = k;
    fNode<T> *y = x->parent;
    if (y != NULL && x->key < y->key)
    {
        this->cut(x, y);
        this->cascadingCut(y);
    }
    if (x->key < this->min->key)
    {
        this->min = x;
    }
}

template <typename T>
void FibonacciHeap<T>::cut(fNode<T> *x, fNode<T> *y)
{
    x->parent = NULL;
    y->degree--;
    if (x->right == x)
    {
        y->child = NULL;
        return;
    }
    // remove x
    fNode<T> *left = x->left;
    fNode<T> *right = x->right;
    left->right = right;
    right->left = left;
    y->child = left;

    // add x to root list
    fNode<T> *first = this->min;
    fNode<T> *last = this->min->left;

    first->left = x;
    x->right = first;
    last->right = x;
    x->left = last;
    if (x->key < this->min->key)
        this->min = x;
}

template <typename T>
void FibonacciHeap<T>::cascadingCut(fNode<T> *y)
{
    fNode<T> *z = y->parent;
    if (z != NULL)
    {
        if (y->marked == false)
        {
            y->marked = true;
        }
        else
        {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

template <typename T>
void FibonacciHeap<T>::deletefNode(fNode<T> *x)
{
    this->decreaseKey(x, -1e9);
    this->extractMin();
}

template <typename T>
void FibonacciHeap<T>::insert(fNode<T> *x)
{
    this->unionHeap(new FibonacciHeap(x));
}