import scara_functions;

#include <iostream>
#include <random>

#include "scara.h"

class Name
{
public:
    Name() { memory_ = new char[1] { 0 }; }
    explicit Name(const char* name)
    {
        length_ = static_cast<int>(strlen(name)) + 1;
        memory_ = new char[length_];
        strcpy_s(memory_, length_, name);
    }

    Name(const Name& name)
    {
        memory_ = new char[name.length_];
        length_ = name.length_;
        strcpy_s(memory_, length_, name.memory_);
    }
    
    ~Name()
    {
        delete[] memory_;
    }

    [[nodiscard]] const char* get_name() const
    {
        return memory_;
    }

    [[nodiscard]] int get_length() const
    {
        return length_;
    }

    Name& operator=(const Name& name)
    {
        if(name.memory_ != memory_)
        {
            delete[] memory_;
            memory_ = new char[name.length_];
            length_ = name.length_;
            strcpy_s(memory_, length_, name.memory_);
        }
        return *this;
    }

private:
    char* memory_ = nullptr;
    int length_ = 0; 
};

class Person
{
    std::string first_name_;
    std::string last_name_;
    int age_ = 0;

public:
    virtual ~Person() = default;
    Person(const std::string& name, const std::string& last_name, const int age = 0) : first_name_{name}, last_name_{last_name}, age_{age} { } 
    
    void rename(const std::string& new_name = nullptr, const std::string& new_last_name = nullptr)
    {
        if(!first_name_.empty()) first_name_ = new_name;
        if(!last_name_.empty()) first_name_ = new_last_name;
    }
    
    [[nodiscard]] std::string get_name() const
    {
        return first_name_;
    }

    [[nodiscard]] std::string get_last_name() const
    {
        return last_name_;
    }
    
    [[nodiscard]] int get_age() const
    {
        return age_;
    }
};

class Employee : public Person
{
    float monthly_salary_ = 0;
    
public:
    Employee(const std::string& first_name, const std::string& last_name, const int age = 0, const float monthly_salary = 0)
    : Person{first_name, last_name, age}, monthly_salary_{monthly_salary} {}

    [[nodiscard]] float get_monthly_salary() const
    {
        return monthly_salary_;
    }

    [[nodiscard]] virtual float get_yearly_salary() const
    {
        return 12.0f * monthly_salary_;
    }
};

class Manager : public Employee
{
    float christmas_bonus_;
    
public:

    Manager(const std::string& first_name, const std::string& last_name, const int age = 0, const float monthly_salary = 0, const float christmas_bonus = 0)
        : Employee(first_name, last_name, age, monthly_salary), christmas_bonus_(christmas_bonus) {}
    
    [[nodiscard]] float get_yearly_salary() const override
    {
        return christmas_bonus_ + Employee::get_yearly_salary();
    }
};

bool check_for_path()
{
    if(Scara::istVorneAbgrund())
    {
        Scara::dreheLinks();

        if(Scara::istVorneAbgrund())
        {
            Scara::dreheLinks();
            Scara::dreheLinks();

            if(Scara::istVorneAbgrund())
            {
                Scara::dreheLinks();
                Scara::dreheLinks();
                Scara::dreheLinks();
                return false;
            }
            return true;
        }
        return true;
    }
    return true;
}

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,2000000000);
    
    start("VerwirrenderPfad", 5);
    
    set_speed(8);
    show_rotation(true);

    //Pickup palette and rotate towards path
    while(!Scara::istVornePalette())
    {
        Scara::dreheLinks();
    }
    Scara::nimmPalette();
    Scara::dreheLinks();
    Scara::dreheLinks();
    
    while (true)
    {
        //Move until abyss
        while(!Scara::istVorneAbgrund())
        {
            Scara::gehe();
        }

        if(Scara::stehtAufAnkh()) break;
        
        //Check for all directions => if there is a way, take it. Otherwise, place palette and check if there is a way
        if(!check_for_path())
        {
            Scara::dreheLinks();
            Scara::dreheLinks();
            Scara::legePalette();
            Scara::gehe();

            while(!check_for_path())
            {
                Scara::dreheLinks();
            }
            Scara::gehe();
            Scara::dreheLinks();
            Scara::dreheLinks();
            Scara::nimmPalette();
            Scara::dreheLinks();
            Scara::dreheLinks();
        }
    }

    while(!Scara::istVorneAbgrund())
    {
        Scara::dreheLinks();
    }
    Scara::legePalette();
    
    end();

    
}

