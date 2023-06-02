#include <iostream>
#include <string>
#include <memory>

using namespace std;

class A{

    int f{};

public:
    A() {
        cout << " Class A was created" << endl;
    }
    ~A() {
        cout << " Class A was DELETE" << endl;
    }

    string getMessage() const;
        
};

string A::getMessage() const {

    for (int i{}; i < 10; ++i)
        cout << i << " ";
    cout << f << endl;
    return "Class A  message ";
}

class SmartPointer {
    A* a{};
    int* counter{};
public:
    SmartPointer(A* a) :a{ a } {
        counter = new int{ 1 };
        cout << "Counter = " << *counter;
    };

    SmartPointer(const SmartPointer& p) {
        this->a = p.a;
        counter  = p.counter;
        (*counter)++;
        cout << "Counter = " << *counter;
    }

    //SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator= (const SmartPointer&) = delete;

    ~SmartPointer() {
        (*counter)--;
        cout << "Counter = " << *counter;
        if (*counter == 0) {
            delete a;
            delete counter;
        }
    };

    A& operator* () {
        return *a;
    }

    A* operator-> () {
        return a;
    }
};



class Person
{
    std::string m_name;
    //std::shared_ptr<Person> m_partner; // изначально создается пустым
    std::weak_ptr<Person> m_partner; // изначально создается пустым


public:

    Person(const std::string& name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
    {
        if (!p1 || !p2)
            return false;

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << "\n";

        return true;
    }

    // используем lock() для преобразования weak_ptr в shared_ptr
    const std::shared_ptr<Person> getPartner() const { return m_partner.lock(); }
    //const std::string& getName() const { return m_name; }
};




int main(){


    shared_ptr<Person> l(new Person("Lucy"));

    auto lucy{ std::make_shared<Person>("Lucy") };   // создаем Person по имени "Lucy"

    {
        auto ricky{ std::make_shared<Person>("Ricky") }; // создаем Person по имени "Ricky"
        partnerUp(lucy, ricky); // Заставляем "Lucy" указывать на "Ricky" и наоборот
    }

    shared_ptr<Person> p = lucy->getPartner();

    partnerUp(lucy, p); // Заставляем "Lucy" указывать на "Ricky" и наоборот
    

    return 0;

    shared_ptr<A> s_ptr (new A);    
    shared_ptr<A> s_ptr1 (s_ptr);
    {
        shared_ptr<A> s_ptr2;
        s_ptr2 = s_ptr1;
        cout << s_ptr.get() << endl;
        cout << s_ptr1.get() << endl;
        cout << s_ptr2.get() << endl;
    }



    //unique_ptr<A> u_ptr (new A);

    //A* a = u_ptr.get();
    //A* a =  u_ptr.release();
    
    //u_ptr.reset();

    //unique_ptr<A> u_ptr1 (new A);
    //u_ptr1.swap(u_ptr);

    //u_ptr1->getMessage();
    //(*u_ptr1).getMessage();
   
    //unique_ptr<A> u_ptr1(a);

    //unique_ptr<A> u_ptr1;
    //u_ptr1 = u_ptr;



    return 0;

    //A* a = new A;    
    //cout << a->getMessage() << endl;

    cout << "Block 1" << endl;
    SmartPointer pointer(new A);
    {
        
        SmartPointer pointer1 = pointer;
    }

    cout << "Block 2" << endl;
    SmartPointer pointer3(new A);
    {
        
        SmartPointer pointer4 = pointer;
    }


    //cout << pointer->getMessage() << endl;
    

    //SmartPointer pointer1 = pointer;

    //cout << pointer->getMessage() << endl;
    //cout << pointer1->getMessage() << endl;
    

    return 0;
}




