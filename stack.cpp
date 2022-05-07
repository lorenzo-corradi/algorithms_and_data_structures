#include <iostream>

using namespace std;

template <class T>
class Stack {
private:

    T* elem;
    size_t capacity;
    size_t size;
    
public:

    explicit Stack(size_t capacity = 16);
    
    Stack(const Stack& s);
    Stack& operator=(const Stack<T>& s);
    
    Stack(Stack&& s);
    Stack& operator=(Stack<T>&& s);
    
    void swap(Stack& s);
    
    void push(const T& elem);
    void pop();
    
    bool is_empty() const;
    const T& top() const;
    
    size_t size_of() const;
    void display() const;
    
    ~Stack();
    
};

template <class T>
Stack<T>::Stack(const size_t capacity) :
    elem(nullptr),
    capacity(capacity),
    size(0)
    {
        if (capacity > 0) {
            elem = new T[capacity];
        }
    }
    
template <class T>
Stack<T>::Stack(const Stack& s) :
    elem(s.elem),
    capacity(s.capacity),
    size(s.size)
    {}
    
template <class T>
void Stack<T>::swap(Stack& s) {
    using std::swap;
    swap(elem, s.elem);
    swap(capacity, s.capacity);
    swap(size, s.size);
}

template <class T>
Stack<T>::Stack(Stack&& s) :
    Stack(0) {
        swap(s);
    }
    
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s) {
    Stack temp(s);
    swap(temp);
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack&& s) {
    Stack temp(std::move(s));
    swap(temp);
    return *this;
}

template <class T>
Stack<T>::~Stack() {
    delete[] elem;
}

template <class T>
size_t Stack<T>::size_of() const {
    return size;
}

template <class T>
bool Stack<T>::is_empty() const {
    return size_of() == 0;
}

template <class T>
void Stack<T>::push(const T& val) {
    if (capacity <= size) {
        size_t new_capacity = 2 * size + 1;
        T* temp = new T[new_capacity];
        delete[] elem;
        elem = temp;
        capacity = new_capacity;
    }
    
    elem[++size] = val;
}

template <class T>
void Stack<T>::pop() {
    --size;
}

template <class T>
const T& Stack<T>::top() const {
    return elem[size];
}

template<class T>
void Stack<T>::display() const {
    if (size == 0 || capacity == 0) {
        cout << "Empty stack.";
    }
    
    for (size_t i = 0; i <= size; ++i) {
        cout << elem[i] << " ";
    }
    
}

int main()
{
    
    Stack<int>* s = new Stack<int>(5);
    s -> push(10);
    s -> push(20);
    s -> display();
    
    return 0;
}