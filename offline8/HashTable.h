#include <iostream>
#include <string>
#include <cmath>
#define PRIME_CONST 5
using namespace std;

unsigned int hash1(string key, int maxSize)
{
    int hashCode = 0;

    for (int i = 0; i < key.length(); i++)
    {
        hashCode += (key[i] - 'a') * pow(PRIME_CONST, i);
    }
    // cout << "found " << hashCode % maxSize << endl;
    return hashCode % maxSize;
}

unsigned int hash2(string key, int maxSize)
{
    int hashCode = 0;
    for (char c : key)
        hashCode = (hashCode * 33 + c) % maxSize;
    return hashCode % maxSize;
}

struct Node
{
    string key;
    int value;
    Node *next;

    Node()
    {
        key = "";
        value = 0;
    }
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
        next = NULL;
    }
};

class HashLinked
{
private:
    Node **data;
    int maxSize;
    int size;
    Node *arr = NULL;
    Node *resize();

public:
    HashLinked(int m);
    void insert(string key, int value);
    int search(string key);
    bool deleteElement(string key);
};
class HashLinear
{
private:
    Node **data;
    int maxSize;
    int size;
    Node *arr = NULL;
    Node *resize();

public:
    HashLinear(int m);
    void insert(string key, int value);
    int search(string key);
    bool deleteElement(string key);
};
class HashQuadratic
{
private:
    Node **data;
    int maxSize;
    int size;
    Node *arr = NULL;
    Node *resize();

public:
    HashQuadratic(int m);
    void insert(string key, int value);
    int search(string key);
    bool deleteElement(string key);
};

class DoubleHash
{
private:
    Node **data;
    int maxSize;
    int size;
    Node *arr = NULL;
    Node *resize();

public:
    DoubleHash(int m);
    void insert(string key, int value);
    int search(string key);
    bool deleteElement(string key);
};

HashLinked::HashLinked(int m)
{
    this->maxSize = m;
    this->size = 0;
    this->data = new Node *[maxSize];

    for (int i = 0; i < maxSize; i++)
        data[i] = NULL;
}

void HashLinked::insert(string key, int value)
{
    if (search(key) != 1e9)
        return;
    int pos = hash1(key, maxSize);
    Node *newNode = new Node(key, value);

    if (data[pos] == NULL)
    {
        data[pos] = newNode;
    }
    else
    {
        newNode->next = data[pos];
        data[pos] = newNode;
    }
    size++;
}

int HashLinked::search(string key)
{
    int pos = hash1(key, maxSize);
    for (Node *chainNode = data[pos]; chainNode != NULL; chainNode = chainNode->next)
    {
        if (chainNode->key == key)
            return chainNode->value;
    }
    return 1e9;
}

bool HashLinked::deleteElement(string key)
{
    int pos = hash1(key, maxSize);
    if (data[pos] == NULL)
        return false;

    if (data[pos]->next == NULL)
    {
        data[pos] = NULL;
        return true;
    }
    if (data[pos]->key == key)
    {
        data[pos] = data[pos]->next;
        return true;
    }

    Node *temp = data[pos];
    for (Node *chainNode = data[pos]->next; chainNode != NULL; chainNode = chainNode->next)
    {
        if (chainNode->key == key)
        {
            temp->next = chainNode->next;
            return true;
        }
        temp = chainNode;
    }
    return false;
}

HashLinear::HashLinear(int m)
{
    arr = new Node[m]();
    size = 0;
    maxSize = m;
}

void HashLinear::insert(string key, int value)
{
    // if (search(key) != 1e9)
    //     return;
    int pos = hash1(key, maxSize);

    while ((arr[pos].key != "" && arr[pos].key != "delete") && (arr[pos].value != 0 && arr[pos].value != 1e9))
    {
        if (arr[pos].key == key)
            return;
        pos++;
        pos = pos % maxSize;
    }

    Node newNode(key, value);
    arr[pos] = newNode;
    size++;

    // load factor
    // if (size * 1.0 / maxSize >= 0.75)
    // {
    //     size = 0;
    //     resize();
    // }
}

int HashLinear::search(string key)
{
    int probe = 0;
    int pos = hash1(key, maxSize);

    while (arr[pos].key != "" && arr[pos].value != 0)
    {
        probe++;
        if (arr[pos].key == key)
        {
            // cout << arr[pos].value << " ";
            return probe;
            // return arr[pos].value;
        }
        pos++;
        pos %= maxSize;
    }

    return probe;
}

bool HashLinear::deleteElement(string key)
{
    int pos = hash1(key, maxSize);

    while (arr[pos].key != "" && arr[pos].value != 0)
    {
        if (arr[pos].key == key)
        {
            arr[pos].key = "delete";
            arr[pos].value = 1e9;
            return true;
        }
        pos++;
        pos %= maxSize;
    }

    return false;
}

HashQuadratic::HashQuadratic(int m)
{
    arr = new Node[m]();
    size = 0;
    maxSize = m;
}

void HashQuadratic::insert(string key, int value)
{
    // if (search(key) != 1e9)
    //     return;
    int pos = hash1(key, maxSize);
    int x = 1;
    while ((arr[pos].key != "" && arr[pos].key != "delete") && (arr[pos].value != 0 && arr[pos].value != 1e9))
    {
        if (arr[pos].key == key)
            return;
        pos += x * x;
        pos = pos % maxSize;
        x++;
    }

    Node newNode(key, value);
    arr[pos] = newNode;
    size++;

    // load factor
    // if (size * 1.0 / maxSize >= 0.75)
    // {
    //     size = 0;
    //     resize();
    // }
}

int HashQuadratic::search(string key)
{
    int probe = 0;
    int pos = hash1(key, maxSize);
    int x = 1;

    while (arr[pos].key != "" && arr[pos].value != 0)
    {
        probe++;
        if (arr[pos].key == key)
            return probe;
        // return arr[pos].value;
        pos += x * x;
        pos = pos % maxSize;
        x++;
    }

    return probe;
}
bool HashQuadratic::deleteElement(string key)
{
    int pos = hash1(key, maxSize);
    int x = 1;

    while (arr[pos].key != "" && arr[pos].value != 0)
    {
        if (arr[pos].key == key)
        {
            arr[pos].key = "delete";
            arr[pos].value = 1e9;
            return true;
        }
        pos += x * x;
        pos = pos % maxSize;
        x++;
    }

    return false;
}

DoubleHash::DoubleHash(int m)
{
    arr = new Node[m]();
    size = 0;
    maxSize = m;
}

void DoubleHash::insert(string key, int value)
{
    // if (search(key) != 1e9)
    //     return;
    int pos = hash1(key, maxSize);
    int h2 = hash2(key, maxSize);
    int x = 1;
    while ((arr[pos].key != "" && arr[pos].key != "delete") && (arr[pos].value != 0 && arr[pos].value != 1e9))
    {
        if (arr[pos].key == key)
            return;
        pos = pos + x * h2;
        x++;
        pos = pos % maxSize;
    }

    Node newNode(key, value);
    arr[pos] = newNode;
    size++;

    // load factor
    // if (size * 1.0 / maxSize >= 0.75)
    // {
    //     size = 0;
    //     resize();
    // }
}

int DoubleHash::search(string key)
{
    int probe = 0;
    int pos = hash1(key, maxSize);
    int h2 = hash2(key, maxSize);
    int x = 1;
    while (arr[pos].key != "" && arr[pos].value != 0)
    {
        probe++;
        if (arr[pos].key == key)
        {
            // cout << arr[pos].value << " ";
            return probe;
            // return arr[pos].value;
        }
        pos = pos + x * h2;
        x++;
        pos %= maxSize;
    }

    return probe;
}

bool DoubleHash::deleteElement(string key)
{
    int pos = hash1(key, maxSize);
    int h2 = hash2(key, maxSize);
    int x = 1;
    while (arr[pos].key != "" && arr[pos].value != 0)
    {
        if (arr[pos].key == key)
        {
            arr[pos].key = "delete";
            arr[pos].value = 1e9;
            return true;
        }
        pos = pos + x * h2;
        x++;
        pos %= maxSize;
    }

    return false;
}

Node *HashLinked::resize()
{
    return NULL;
}
Node *HashLinear::resize()
{
    return NULL;
}
Node *HashQuadratic::resize()
{
    return NULL;
}
Node *DoubleHash::resize()
{
    return NULL;
}