module;

#include <iostream>

export module Cup;

export class Cup
{
    float milliliters_ = 0;
    float volume_;
    
public:
    explicit Cup(const float volume)
    {
        if(volume < 0)
        {
            volume_ = 100;
            std::cout << "Cup can't have a negative volume. Volume has been set to 100" << std::endl;
            return;
        }
        volume_ = volume;
    }

    explicit Cup(const float milliliters, const float volume) : Cup(volume)
    {
        if(milliliters > volume_)
        {
            if(milliliters < 0)
            {
                std::cout << "Milliliters can't be negative. Milliliters has been set to volume." << std::endl;
            }
            
            milliliters_ = volume_;
        }
        else
        {
            milliliters_ = milliliters;
        }
    }

    void print() const
    {
        std::cout << "Volume: " << volume_ << " | Milliliters: " << milliliters_ << std::endl;
    }

    float fill_up(const float milliliters)
    {
        if(milliliters < 0.0f)
        {
            std::cout << "Milliliters can't be negative. Please give a proper input." << std::endl;
            return 0.0f;
        }
        
        milliliters_ += milliliters;
        if(milliliters_ > volume_)
        {
            milliliters_ = volume_;
            return milliliters_ - volume_;
        }
        return milliliters;
    }

    float extract(const float milliliters) const
    {
        float extracted = 0.0f;
        if(milliliters_ >= milliliters)
        {
            extracted = milliliters;
        }
        else
        {
            extracted = milliliters_;
        }
        return extracted - milliliters_;
    }
    
    float get_volume() const { return volume_; }
    float get_milliliters() const { return milliliters_; }
};

export class CupHolder
{
    Cup* first_cup_ = nullptr;
    Cup* second_cup_ = nullptr;

public:
    CupHolder() { }
    explicit CupHolder(Cup* first_cup) : first_cup_(first_cup) { }
    CupHolder(Cup* first_cup, Cup* second_cup) : first_cup_(first_cup)
    {
        if(first_cup_ != second_cup_) second_cup_ = second_cup;
    }

    bool add_cup(Cup* cup)
    {
        if(first_cup_ && cup == first_cup_) return false;
        
        if(!first_cup_) { first_cup_ = cup; return true; }
        if(!second_cup_) { second_cup_ = cup; return true; }
        return false;
    }

    bool remove_cup(const Cup* cup)
    {
        if(cup == first_cup_) { first_cup_ = nullptr; return true; }
        if(cup == second_cup_) { second_cup_ = nullptr; return true; }
        return false;
    }

    int get_cup_count() const
    {
        int count = 0;
        if(first_cup_) ++count;
        if(second_cup_) ++count;
        return count;
    }

    float get_total_contents() const
    {
        float content = 0;
        if(first_cup_) content += first_cup_->get_milliliters();
        if(second_cup_) content += second_cup_->get_milliliters();
        return content;
    }
};