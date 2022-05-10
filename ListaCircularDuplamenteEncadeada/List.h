#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

struct node;

class List{

public:
    List();

    ~List();

    void push_back(int key);

    int pop_back();

    void insertAfter(int key, int k);

    void remove(int key);

    void removeAll(int key);

    void print();

    void printReverse();

    bool empty();

    int size();

    void clear();

    void concat(List *lst);

    void auxConcat();

    List *copy();

    void copyArray(int n, int arr[]);

    bool equal(List *lst);

private:

    node* head;
    int tamanho;
};


#endif // LIST_H_INCLUDED
