module;

#include <iostream>

export module NNumber;

export class NNumber
{
    mutable int _number;
    mutable bool _prim;
    mutable bool _prim_checked;
    mutable bool _perfect;
    mutable bool _perfect_checked;
    
public:
    
    NNumber() : _number(0) {}
    explicit NNumber(const int number)
    {
        if(number >= 0) _number = number;
        else _number = -number;
    }

    // LOGIC FUNCTIONS
    //------------------------------------------------------------------------------------------------------------------
    
    void print() const
    {
        std::cout << _number << std::endl; 
    }
    
    bool is_prim() const
    {
        if(!_prim_checked)
        {
            _prim_checked = true;
            _prim = is_prim(_number);
        }
        
        return _prim;
    }

    bool is_perfect() const
    {
        if(!_perfect_checked)
        {
            _perfect_checked = true;
            _perfect = get_divisor_sum(_number) == _number;
        }
        
        return _perfect;
    }

    // GETTER + SETTER
    //------------------------------------------------------------------------------------------------------------------
    
    int get_value() const
    {
        return _number;
    }

    void set_value(const int number) const
    {
        if(number >= 0) _number = number;
        else _number = -number;
    }
    
    static bool is_prim(const int number)
    {
        if (number <= 1)
            return false;
        
        for (int i = 2; i <= number / 2; ++i)
            if (number % i == 0)
                return false;
 
        return true;    
    }

    static int get_divisor_sum(const int number, const bool with_own_value = false)
    {
        if(number == 0) return 0;
        
        int divisor_sum = 1;
        int condition_value = with_own_value ? number : number / 2;
        
        for (int i = 2; i <= condition_value; ++i)
            divisor_sum += number % i == 0 ? i : 0;
        
        return divisor_sum;
    }
};