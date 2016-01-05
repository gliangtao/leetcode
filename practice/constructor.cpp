#include <iostream>

using namespace std;
class Base
{
public:
    Base(); // Default constructor.
    virtual void f(); // Virtual member function.
};

Base::Base()
{
    cout << "Constructing Base sub-object\n";
    f(); // Call virtual member function
} // from inside constructor.

void Base::f()
{
    cout << "Called Base::f()\n";
}

class Derived : public Base
{
public:
    Derived(); // Default constructor.
    void f(); // Implementation of virtual
}; // function f for this class.

Derived::Derived()
{
    cout << "Constructing Derived object\n";
}

void Derived::f()
{
    cout << "Called Derived::f()\n";
}

int main()
{
    Derived d;
}
