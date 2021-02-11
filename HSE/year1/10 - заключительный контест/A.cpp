#include <iostream>
#include <algorithm>
#include <utility>
#include <cstddef>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <list>


using namespace std;

template<typename T>
class  UniquePtr {
private:
    T * ptr = nullptr;

public:
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr() {
        ptr = nullptr;
    }
    UniquePtr(T * other_ptr) {
        ptr = other_ptr;
    }
    UniquePtr(UniquePtr && move_ptr):ptr(std::move(move_ptr.ptr)){}
    UniquePtr& operator =(nullptr_t patron) {
        delete ptr;
        ptr = nullptr;
        return *this;
    }
    UniquePtr& operator=(UniquePtr && move_ptr) {
        delete ptr;
        ptr = std::move(move_ptr.ptr);
        return *this;
    }
    ~UniquePtr() {
        delete ptr;
    }
    const T& operator*() const {
        return *ptr;
    }
    T * operator->() const {
        return ptr;
    }
    T * release() {
        T * patron = ptr;
        ptr = nullptr;
        return patron;
    }
    void reset(T * patron)  {
        delete ptr;
        ptr = patron;
    }
    void swap(UniquePtr& other) {
        auto patron = other.ptr;
        other.ptr = ptr;
        ptr = patron;
    }
    T * get() const {
        return ptr;
    }
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

int main() {
    /*int a = 0;
    cout << sizeof(string) << " - size of string\n";
    cout << sizeof(int) << " - size of int\n";
    cout << sizeof(double) << " - size of double\n";;
    cout << sizeof(char) << " - size of char\n";;
    cout << sizeof(int *) << " - size of int ptr\n";;
    vector<int> v;
    cout << sizeof(UniquePtr<int>) << " - size of MyUniq_PTR\n";
    cout << sizeof(nullptr) << " - size of NullPTR\n";
      */
    int * p0 = new int(42);
    int * p1 = new int(17);
    UniquePtr<int> smart_ptr0;
    UniquePtr<int> smart_ptr1(p1);
    //cout << (p1 == nullptr) << endl;
    //swap(smart_ptr0, smart_ptr1);
    //smart_ptr0.swap(smart_ptr1);
    cout << *smart_ptr0 << " " << *smart_ptr1;
}
/*
 * Вопросы на среду
 * 1) Когда мы пишем ф-ию свап для юник птр (нужно ли проверять что
 * сам птр и other_ptr - не нульптр и почему мы не можем свапнуть с нульптрлм
 *
 */
