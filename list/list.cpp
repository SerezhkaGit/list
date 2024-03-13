#include <iostream>
using namespace std;

template <class T>
class list
{
    template<class T1>
    class Node
    {
    public:
        T1 data;
        Node<T1>* next_node;
    public:
        Node()
        {
            data = T1();
            next_node = nullptr;
        }
        Node(T1 data_) : data{ data_ }, next_node{ nullptr } {}
    };

    Node<T>* head;
    int size;

public:

    list() : head{ nullptr }, size{ 0 } {}

    
    list(const list& otherList) : head{ nullptr }, size{ 0 } 
    {
        Node<T>* otherTmp = otherList.head;
        while (otherTmp != nullptr) {
            insertNode(otherTmp->data);
            otherTmp = otherTmp->next_node;
        }
    }


    list& operator=(const list& otherList) 
    {
        if (this != &otherList) 
        {
            clear();
            Node<T>* otherTmp = otherList.head;
            while (otherTmp != nullptr) 
            {
                insertNode(otherTmp->data);
                otherTmp = otherTmp->next_node;
            }
        }
        return *this;
    }

   
    ~list() {
        clear();
    }

    void insertNode(T value);
    void deleteNode(int index);
    void printNode();
    T at(int index);

    
    list* clone() {
        list* clonedList = new list();
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            clonedList->insertNode(tmp->data);
            tmp = tmp->next_node;
        }
        return clonedList;
    }

   
    list operator+(const list& otherList) 
    {
        list<T> result;
        Node<T>* tmp = head;
        while (tmp != nullptr) 
        {
            result.insertNode(tmp->data);
            tmp = tmp->next_node;
        }
        tmp = otherList.head;
        while (tmp != nullptr) 
        {
            result.insertNode(tmp->data);
            tmp = tmp->next_node;
        }
        return result;
    }

   
    list operator*(const list& otherList) 
    {
        list<T> result;
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            if (otherList.contains(tmp->data)) 
            {
                result.insertNode(tmp->data);
            }
            tmp = tmp->next_node;
        }
        return result;
    }

    
    bool contains(const T& value) const {
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            if (tmp->data == value) {
                return true;
            }
            tmp = tmp->next_node;
        }
        return false;
    }


    
    void clear() {
        while (head != nullptr)
        {
            Node<T>* tmp = head;
            head = head->next_node;
            delete tmp;
        }
        size = 0;
    }
};

template <class T>
void list<T>::insertNode(T value)
{
    Node<T>* newNode = new Node<T>(value);
    size++;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node<T>* tmp = head;
    while (tmp->next_node != nullptr)
    {
        tmp = tmp->next_node;
    }

    tmp->next_node = newNode;
}

template <class T>
void list<T>::printNode()
{
    if (head == nullptr) {
        cout << "List is empty";
        return;
    }

    Node<T>* tmp = head;
    while (tmp->next_node != nullptr)
    {
        cout << tmp->data << ' ';
        tmp = tmp->next_node;
    }
    cout << tmp->data;
}


template <class T>
void list<T>::deleteNode(int index)
{
    if (head == nullptr)
    {
        cout << "List is empty\n";
        return;
    }
    if (size - 1 < index || index < 0)
    {
        cout << "Out of range\n";
        return;
    }

    Node<T>* tmp = head;
    int id = 0;

    while (tmp->next_node != nullptr && id != index - 1)
    {
        tmp = tmp->next_node;
        id++;
    }

    Node<T>* temp = tmp->next_node;
    tmp->next_node = temp->next_node;
    delete temp;
}

template<class T>
T list<T>::at(int index)
{
    Node<T>* tmp = head;
    int id = 0;

    while (tmp->next_node != nullptr)
    {
        if (index == id)
        {
            return tmp->data;
        }
        else
        {
            tmp = tmp->next_node;
            id++;
        }
    }
}

int main()
{
    list<int> f;
    for (int i = 0; i < 6; i++)
    {
        f.insertNode(i);
    }

    f.printNode();
    cout << "\n-------------------------------------------\n";
    f.deleteNode(3);
    f.printNode();
    cout << "\n-------------------------------------------\n";
    cout << f.at(1) << endl;

    
    list<int>* clonedList = f.clone();
    clonedList->printNode();
    cout << "\n-------------------------------------------\n";

    
    list<int> g;
    for (int i = 6; i < 10; i++)
    {
        g.insertNode(i);
    }
    list<int> sum = f + g;
    sum.printNode();
    cout << "\n-------------------------------------------\n";

   
    list<int> intersection = f * g;
    intersection.printNode();
    cout << "\n-------------------------------------------\n";

    delete clonedList;

    return 0;
}
