#include <iostream>

using namespace std;

template<class T>
class Vector {
private:

    T* buffer;
    size_t size;
    size_t capacity;
    
public:
    
    typedef T* iterator;
    
    Vector():
        buffer(nullptr),
        size(0),
        capacity(0)
    {}
    
    Vector(const size_t capacity);
    
    Vector(const Vector& v);
    Vector& operator=(const Vector& v);
    
    Vector(Vector&& v);
    Vector& operator=(Vector&& v);
    
    void swap(Vector& v);
    
    ~Vector();
    
    size_t size_of() const;
    size_t capacity_of() const;
    bool is_empty() const;
    
    void push_back(T val);
    void pop_back();
    void reserve(size_t capacity);
    void display() const;
    iterator begin();
    iterator end();
    
    T& operator[](size_t index);
    
};


template<class T>
Vector<T>::Vector(const Vector& v) :
    buffer(v.buffer),
    size(v.size),
    capacity(v.capacity)
{}


template<class T>
Vector<T>::Vector(const size_t capacity) :
    buffer(nullptr),
    capacity(capacity),
    size(0)
    {
        if (capacity > 0) {
            buffer = new T[capacity];
        }
    }
    
  
template<class T>
void Vector<T>::swap(Vector& v) {
    using std::swap;
    swap(buffer, v.buffer);
    swap(capacity, v.capacity);
    swap(size, v.size);
}



template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
    Vector temp(v);
    swap(temp);
    return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
    Vector temp(std::move(v));
    swap(temp);
    return *this;
}


template<class T>
Vector<T>::Vector(Vector&& v) :
    Vector()
    {
        swap(v);
    }


template<class T>
Vector<T>::~Vector() {
    
    delete[] buffer;
    
}


template<class T>
size_t Vector<T>::capacity_of() const {
    return capacity;
}


template<class T>
size_t Vector<T>::size_of() const {
    return size;
}

template<class T>
bool Vector<T>::is_empty() const {
    return size_of() == 0;
}

template<class T>
void Vector<T>::reserve(size_t capacity_temp) {

    T* buffer_temp = new T[capacity + capacity_temp];
    std::copy(buffer, buffer + size, buffer_temp);
    
    delete[] buffer;
    
    buffer = buffer_temp;
    capacity += capacity_temp;

}


template<class T>
void Vector<T>::push_back(T val) {
    if(size >= capacity) {
        reserve(capacity + 5);
    }
    buffer[++size] = val;
}


template<class T>
void Vector<T>::pop_back() {
    --size;
}


template<class T>
typename Vector<T>::iterator Vector<T>::begin() {
    return buffer;
}

template<class T>
typename Vector<T>::iterator Vector<T>::end() {
    return buffer + size;
}

template<class T>
T& Vector<T>::operator[](size_t index) {
    return cout << buffer[index];
}

template<class T>
void Vector<T>::display() const {
    if (is_empty()) {
        cout << "Empty list.";
    }
    
    for (int i = 0; i <= size; ++i) {
        cout << buffer[i] << " ";
    }
}



int main()
{
    Vector<int>* v1 = new Vector<int>(5);
    //Vector<int> v2(*v1);
    //Vector<int> v3(std::move(v2));
    //Vector<int> v4 = v2;
    //v1 -> reserve(10);
    cout << "capacity of vector: " << v1 -> capacity_of() << endl;
    
    v1 -> push_back(100);
    
    cout << "size of vector: " << v1 -> size_of() << endl;
    
    v1 -> push_back(101);
    v1 -> push_back(102);
    
    v1 -> push_back(101);
    v1 -> push_back(102);
    
    v1 -> push_back(101);
    v1 -> push_back(102);
    
    cout << "size of vector: " << v1 -> size_of() << endl;
    
    v1 -> pop_back();
    v1 -> pop_back();
    v1 -> pop_back();
    v1 -> pop_back();
    v1 -> pop_back();
    v1 -> pop_back();
    v1 -> pop_back();
    
    cout << "size of vector: " << v1 -> size_of() << endl;
    
    
    v1 -> display();
    
    return 0;
}
