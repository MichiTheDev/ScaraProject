module;

#include <iostream>

export module NNumber;

export class NNumber
{
    using val_t = long;
    val_t number_;
    
public:
    
    NNumber() {}
    explicit NNumber(const val_t number)
    {
        if(number >= 0) number_ = number;
        else number_ = -number;
    }

    // LOGIC FUNCTIONS
    //------------------------------------------------------------------------------------------------------------------
    
    void print() const
    {
        std::cout << number_ << std::endl; 
    }
    
    bool is_prim() const
    {
        if (number_ <= 1)
            return false;
        
        for (int i = 2; i <= number_ / 2; ++i)
            if (number_ % i == 0)
                return false;
 
        return true;  
    }

    bool is_perfect() const
    {
        if(number_ == 0) return false;

        return get_divisor_sum(number_) == number_;
    }

    void next()
    {
        set_value(number_ + 1);
    }
    
    NNumber get_next() const
    {
        return NNumber(number_ + 1);    
    }

    static val_t get_divisor_sum(const int number, const bool with_own_value = false)
    {
        if(number == 0) return 0;
        
        val_t divisor_sum = 1;
        const val_t condition_value = with_own_value ? number : number / 2;
        
        for (int i = 2; i <= condition_value; ++i)
            divisor_sum += number % i == 0 ? i : 0;
        
        return divisor_sum;
    }
    
    // GETTER + SETTER
    //------------------------------------------------------------------------------------------------------------------
    
    val_t get_value() const
    {
        return number_;
    }

    void set_value(const val_t number)
    {
        if(number >= 0) number_ = number;
        else number_ = -number;
    }
};