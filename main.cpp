import scara_functions;

#include <iostream>
#include <random>

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

int main()
{
    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> dist(0,2000000000);
    //
    // start("AbsoluteEntfernung", 255);
    //
    // set_speed(10);
    // show_rotation(false);
    //
    //
    //
    // end();

    Name name1 { "Michi" };
    Name name2 { };

    name1 = name1;

    std::cout << name1.get_name() << std::endl;
}

