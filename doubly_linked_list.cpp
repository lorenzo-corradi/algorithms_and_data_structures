#include <iostream>

using namespace std;

template<class T>
class Node {
    
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node() {
        next = nullptr;
        prev = nullptr;
    }
    
    // "explicit" protects from unwanted intializations
    // Node<int> head = 5; // error
    // Node<int> head = Node<int>(5); // OK
    explicit Node(T&& value):
        data(std::move(value)),
        next(nullptr),
        prev(nullptr)
    {}
    
};

template <class T>
class DoublyLinkedList {
    
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;
    
public:
    DoublyLinkedList():
        head(nullptr),
        tail(nullptr),
        size(0) 
    {}

    
    DoublyLinkedList(const DoublyLinkedList& dll);
    DoublyLinkedList& operator=(const DoublyLinkedList& dll);
    
    DoublyLinkedList(DoublyLinkedList&& dll);
    DoublyLinkedList& operator=(DoublyLinkedList&& dll);
    
    void push_back(T val);
    void pop_back();
    void push_front(T val);
    void pop_front();
    void display() const;
    void insert_at(T val, int position);
    void delete_at(int position);
    bool is_empty() const;
    void swap(DoublyLinkedList& dll);
    size_t size_of() const;
    
    ~DoublyLinkedList();
    
};


template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& dll) :
    head(dll.head),
    tail(dll.tail),
    size(dll.size)
{}


template<class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& dll) :
    DoublyLinkedList() 
    { 
        swap(dll);
    }
    

/* cannot deduce(?)
template<class T>
DoublyLinkedList& DoublyLinkedList<T>::operator=(const DoublyLinkedList& dll) {
    DoublyLinkedList temp(dll);
    swap(temp);
    return *this;
}
*/
    
    
template<class T>
void DoublyLinkedList<T>::swap(DoublyLinkedList& dll) {
    using std::swap;
    swap(head, dll.head);
    swap(tail, dll.tail);
    swap(size, dll.size);
}


template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
        
    Node<T>* temp = head;
        
    while (head != nullptr) {
        head = head -> next;
        delete temp;
        temp = head;
    }
    
    tail = nullptr;
    size = 0;
}


template<class T>
void DoublyLinkedList<T>::push_back(T val) {

    auto* new_node = new Node<T>(std::move(val));

    if (tail != nullptr) {
        tail -> next = new_node;
        new_node -> prev = tail;
        tail = new_node;
    } 
    else {
        tail = new_node;
        head = new_node;
    }
    
    ++size;
    
}


template<class T>
void DoublyLinkedList<T>::push_front(T val) {
    
    auto* new_node = new Node<T>(std::move(val));
    
    if (head != nullptr) {
        head -> prev = new_node;
        new_node -> next = head;
        head = new_node;
    }
    else {
        tail = new_node;
        head = new_node;
    }
    
    ++size;
    
}


template<class T>
void DoublyLinkedList<T>::insert_at(T val, int position) {
    
    auto* new_node = new Node<T>(std::move(val));
    Node<T>* temp = head;
    
    for (int i = 1; i < position; ++i, temp = temp -> next);
    
    new_node -> next = temp;
    new_node -> prev = temp -> prev;
    temp -> prev = new_node;
    
    if (new_node -> prev != nullptr) {
        new_node -> prev -> next = new_node;
    }
    
    if (head == temp) {
        head = new_node;
    }
    
    ++size;
    
}


template<class T>
void DoublyLinkedList<T>::pop_back() {
    if (tail == nullptr) {
        throw runtime_error("can't pop element since linked list is empty.\n");
    }
    
    if (tail == head) {
        delete tail;
        tail = nullptr;
        head = nullptr;
    }
    else {
        Node<T>* previous_node = tail -> prev;
        delete tail;
        
        tail = previous_node;
        tail -> next = nullptr;
    }
    
    --size;
    
};


template<class T>
void DoublyLinkedList<T>::pop_front() {
    if (head == nullptr) {
        throw runtime_error("can't pop element since linked list is empty.\n");
    }
    
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        Node<T>* next_node = head -> next;
        delete head;
        
        head = next_node;
        head -> prev = nullptr;
    }
    
    --size;
    
}


template<class T>
void DoublyLinkedList<T>::delete_at(int position) {
    
    Node<T>* temp = head;
    
    for(int i = 1; i < position; ++i, temp = temp -> next);
    
    if (temp -> next != nullptr) {
        temp -> next -> prev = temp -> prev;
    }
    
    if (temp -> prev != nullptr) {
        temp -> prev -> next = temp -> next;
    }
    
    if (head == temp) {
        head = temp -> next;
    }
    
    if (tail == temp) {
        tail = tail -> prev;
    }
    
    delete temp;
    --size;
    
}


template<class T>
size_t DoublyLinkedList<T>::size_of() const {
    return size;
}


template<class T>
bool DoublyLinkedList<T>::is_empty() const {
    return size_of() == 0;
}


template<class T>
void DoublyLinkedList<T>::display() const {
    
    if (is_empty()) {
        cout << "Empty list.";
    }
    
    for (Node<T>* print_ptr = head; print_ptr != nullptr; print_ptr = print_ptr -> next) {
        cout << print_ptr -> data << " ";
    }
    
    cout << "\n";
    
}


int main()
{
    DoublyLinkedList<int>* linked_list_1 = new DoublyLinkedList<int>();
    DoublyLinkedList<int>* linked_list_2 = new DoublyLinkedList<int>();
    
    linked_list_1 -> push_back(5);
    linked_list_1 -> push_back(6);
    linked_list_1 -> push_back(7);
    linked_list_1 -> pop_front();
    linked_list_1 -> insert_at(100, 1);
    linked_list_1 -> delete_at(2);
    
    //linked_list_1 = linked_list_2;
    
    linked_list_1 -> push_front(4);
    linked_list_1 -> display();
    
    return 0;
}