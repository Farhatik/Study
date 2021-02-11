#include <cstddef>
#include <memory>
#include <tuple>
#include <utility>

using namespace std;

template <typename T,
        typename Deleter = default_delete<T>>
class UniquePtr {
private:
    tuple <T *, Deleter> ptr;

public:
    UniquePtr() {
        std:: get <0> (ptr) = nullptr;
    }
    UniquePtr(T * other) {
        std:: get <0> (ptr) = other;
    }
    UniquePtr(UniquePtr && other):
            ptr(other.ptr) {
        std:: get <0> (other.ptr) = nullptr;
    }
    UniquePtr(T * other, Deleter del) {
        std:: get <0> (ptr) = other;
        std:: get <1> (ptr) = del;
    }

    UniquePtr & operator = (nullptr_t other) {
        std:: get <1> (ptr) (std:: get <0> (ptr));
        std:: get <0> (ptr) = nullptr;
        return *this;
    }
    UniquePtr & operator = (UniquePtr && other) {
        std:: get <1> (ptr) (std:: get <0> (ptr));
        ptr = other.ptr;
        std:: get <0> (other.ptr) = nullptr;
        return *this;
    }
    UniquePtr & operator = (const UniquePtr &) = delete;

    ~UniquePtr() noexcept {
        if (std:: get <0> (ptr) != nullptr) {
            std:: get <1> (ptr) (std:: get <0> (ptr));
        }
    }

    T & operator * () const {
        return * (std:: get <0> (ptr));
    }

    T * operator -> () const {
        return std:: get <0> (ptr);
    }

    T * release() {
        T * temp = std:: get <0> (ptr);
        std:: get <0> (ptr) = nullptr;
        return temp;
    }

    void reset(T * other = nullptr) noexcept {
        std:: get <1> (ptr) (std:: get <0> (ptr));
        std:: get <0> (ptr) = other;
        other = nullptr;
    }

    void swap(UniquePtr & other) {
        std:: swap(ptr, other.ptr);
    }

    T * get() const {
        return std:: get<0>(ptr);
    }

    explicit operator bool() const {
        return (std:: get <0> (ptr) != nullptr);
    }

    const Deleter & get_deleter() const {
        return std:: get <1> (ptr);
    }

    Deleter & get_deleter() {
        return std:: get <1> (ptr);
    }

    UniquePtr(const UniquePtr &) = delete;
};