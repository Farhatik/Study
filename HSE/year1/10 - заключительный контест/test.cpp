#include <iostream>
#include <memory>
#include <string>

class Expression {
public:
    virtual int Evaluate() const = 0;
    virtual std::string ToString() const = 0;
    virtual ~Expression() {}
};

using ExpressionPtr = std::shared_ptr<Expression>;

using namespace std;

class Constantic : public Expression {
private:
    int num;

public:
    Constantic(int x) : num(x) {
    }
    int Evaluate() const override {
        return num;
    }
    std::string ToString() {
        string to_string(int num);
    }
    ~Constantic() {
    }
};

class Sum_EX : public Expression {
private:
    ExpressionPtr first, second;
public:
    Sum_EX(ExpressionPtr f, ExpressionPtr s) : first(f), second(s) {
    }
    int Evalute() const override {
        return (*first + *second);
    };
    std::string ToString() {
        string to_string(*first) ;
    }

};
int main() {
    ExpressionPtr ex1 = Sum(Product(Const(3), Const(4)), Const(5));
    std::cout << ex1->ToString() << "\n";  // 3 * 4 + 5
    std::cout << ex1->Evaluate() << "\n";  // 17

    ExpressionPtr ex2 = Product(Const(6), ex1);
    std::cout << ex2->ToString() << "\n";  // 6 * (3 * 4 + 5)
    std::cout << ex2->Evaluate() << "\n";  // 102
}

