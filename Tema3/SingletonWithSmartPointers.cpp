#include <iostream>
#include <string>
#include <memory>
#include <mutex>

class Mutex {
public:
    Mutex(){}
    ~Mutex(){}
    
    void lock(Mutex *pm) {std::cout << "locked" << std::endl;}
    void unlock(Mutex *pm) {std::cout << "unlocked" << std::endl;}

};

class Admin : Mutex {
private:
    static std::shared_ptr<Admin> myInstance_;
    std::string name;
    Mutex *_mutex;

    Admin() : name("default")
    {
        lock(_mutex);
    }

    Admin(const Admin&);
    Admin(Admin&&);
    Admin& operator=(const Admin&);
    Admin& operator=(Admin&&);
    
public:
    ~Admin()
    {
        unlock(_mutex);
    }

    static std::shared_ptr<Admin> getInstance()
    {   
        if(!myInstance_)
        {   
                myInstance_ = std:: shared_ptr<Admin>(new Admin());
        }
        
        return myInstance_;
    }

    inline std::string getName() const;
    inline void setName(std::string name);
};

std::string Admin::getName() const
{
    return name;
}

void Admin::setName(std::string name)
{
    this->name = name;
}

std::shared_ptr<Admin> Admin::myInstance_ = nullptr;

int main()
{
    std::shared_ptr<Admin> a(Admin::getInstance());
    std::cout << a->getName() << std::endl;  // afiseaza default
    a->setName("Oana");
    std::cout << a->getName() << std::endl; // afiseaza Oana
    std::cout << "Counter shared pointer reference:" << a.use_count() << std::endl; 

    std::shared_ptr<Admin> b(Admin::getInstance());
    std::cout << b->getName() << std::endl; //va afisa tot Oana deoarece putem avea un singur administrator
    std::cout << "Counter shared pointer reference:" << b.use_count() << std::endl; 

    return 0;
}

