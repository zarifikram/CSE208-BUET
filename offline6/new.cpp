#include <iostream>
#include <stack>
// #include "BinomialHeap.h"
#include "FibonacciHeap.h"
#include <vector>

#define ii pair<int, int>

using namespace std;

int main()
{
    FibonacciHeap<int> *bh = new FibonacciHeap<int>();
    FibonacciHeap<int> *ah = new FibonacciHeap<int>();
    int i = 0;
    Node<int> *x = new Node<int>(14);
    Node<int> *y = new Node<int>(5);
    // cout << i++ << endl;
 
    ah->insert(x);
    // cout << i++ << endl;
    ah->insert(y);
    // cout << i++ << endl;
    bh->insert(new Node<int>(3));
    // cout << i++ << endl;
    bh->insert(new Node<int>(8));
    // cout << i++ << endl;
    bh->insert(new Node<int>(4));
    // cout << i++ << endl;
    bh->unionHeap(ah);
    bh->decreaseKey(x, 2);

    while (!bh->isEmpty())
    {
        // cout << " nodes no : " << bh->nNodes << endl;
        // bh->display();
        cout << (bh->extractMin()->key) << " " << endl;
        // cout << endl << endl;
        // cout << i++ << endl;
    }
    // cout << endl;
    return 0;
}
