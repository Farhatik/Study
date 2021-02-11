#include <algorithm>
#include <cstddef>
#include <memory>
#include <iostream>
#include <utility>
#include <tuple>
using namespace std;



template<typename T, typename Deleter = default_delete<T>()>
class UniquePtr {
private:
    tuple<T*, Deleter> patron;

public:
    UniquePtr(UniquePtr &other) = delete;
    UniquePtr operator=(UniquePtr &other) = delete;
    UniquePtr(UniquePtr &&move_ptr) {
        std::get<0>(patron) = std::get<0>(move_ptr);
        std::get<0>(move_ptr) = nullptr;
    }
    UniquePtr() {
        std::get<0>(patron) = nullptr;
    }
    UniquePtr(T * ptr) {
        std::get<0>(patron) = ptr;
    }
    UniquePtr(T * ptr, Deleter Killer) {
        std::get<0>(patron) = ptr;
        std::get<1>(patron) = Killer;
    }
    Deleter& get_deleter() const {
        return std::get<1>(patron);
    }
    Deleter& get_deleter() {
        return std::get<1>(patron);
    }
    UniquePtr &operator=(nullptr_t pat) {
        delete std::get<0>(patron);
        std::get<0>(patron) = nullptr;
        return *this;
    }
    UniquePtr &operator=(UniquePtr &&move_ptr) {
        delete std::get<0>(patron);
        std::get<0>(patron) = std::get<0>(move_ptr);
        std::get<0>(move_ptr) = nullptr;
        return *this;
    }

    ~UniquePtr() {
            std::get<1>(patron)(std::get<0>(patron));
    }

    T &operator*() const {
        return *(std::get<0>(patron));
    }

    T *operator->() const {
        return std::get<0>(patron);
    }

    T *release() {
        T *pat = std::get<0>(patron);
        std::get<0>(patron) = nullptr;
        return pat;
    }

    void reset(T *pat) {
        delete std::get<0>(patron);
        std::get<0>(patron) = pat;
    }

    void swap(UniquePtr &other) {
        std::swap(patron, other.patron);
    }

    T *get() const {
        return std::get<0>(patron);
    }

    explicit operator bool() const {
        return (std::get<0>(patron) != nullptr);
    }
};

