#include <iostream>

using namespace std;

template <typename T>

class my_unique_ptr {
private:
    T* m_obj;
    
    my_unique_ptr(const my_unique_ptr& obj){}
    my_unique_ptr& operator = (const my_unique_ptr& obj){}
public:
    my_unique_ptr(T *obj) : m_obj(obj){}
    ~my_unique_ptr(){
        if (m_obj != nullptr)
            delete m_obj;
    }
    T* operator * (){
        return m_obj;
    }
    
    T* operator -> (){
        return m_obj;
    }
    
    T* release(){
        T* ptr = m_obj;
        m_obj = nullptr;
        return ptr;
    }
    
};

template <typename T>
class my_shared_ptr{
private:
    int *m_count;
    T* m_ptr;
    
public:
    my_shared_ptr() : m_ptr(nullptr), m_count(0) {}
    my_shared_ptr(T* ptr) : m_ptr(ptr), m_count(new int(1)) {}
    my_shared_ptr(my_shared_ptr<T> &shr_ptr): m_ptr(shr_ptr.m_ptr), m_count(shr_ptr.m_count)
    {
        m_count++;
    }
    ~my_shared_ptr(){
        if (m_count == 1)
            delete m_ptr;
        m_count--;
    }
    
    T* get(){
        return m_ptr;
    }
    
    void reset(){
        if (m_count == 1)
            delete m_ptr;
        m_count --;
        m_ptr = nullptr;
        m_count = new int(0);
    }
    
    void reset(T* shr_ptr){
        if (m_count == 1)
            delete m_ptr;
        
        m_count --;
        m_ptr = shr_ptr;
        m_count = new int(0);
    }
    
    void reset(my_shared_ptr<T> &shr_ptr){
        if (m_count == 1)
            delete m_ptr;
        
        m_count --;
        m_ptr = shr_ptr.m_ptr;
        m_count = shr_ptr.m_count + 1;
    }
    
    my_shared_ptr<T>& operator=(my_shared_ptr<T>& other){
        if (this == &right) {
            return *this;
        }
        
        this->reset(other);
        return *this;
    }
    
    T* operator->(){
        return m_ptr;
    }
    
    T& operator*(){
        return &m_ptr;
    }
};

int main() {
    return 0;
}
