module;

#include <iostream>

export module NNumber;

export class NNumber
{
    int _number;
    mutable bool _prim;
    mutable bool _prim_checked;
    
public:
    
    NNumber() : _number(0) {}
    explicit NNumber(const int n)
    {
        if(n >= 0) _number = n;
        else _number = -n;
    }

    void print() const
    {
        std::cout << _number << std::endl; 
    }
    
    int value() const
    {
        return _number;
    }

    bool is_prim() const
    {
        if(!_prim_checked)
        {
            _prim_checked = true;
            _prim = _is_prim();
        }
        return _prim;    
    }
    
private:
    
    bool _is_prim() const
    {
        if (_number <= 1)
            return false;
        
        for (int i = 2; i <= _number / 2; ++i)
            if (_number % i == 0)
                return false;
 
        return true;    
    }
};