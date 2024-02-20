import scara_functions;

#include <iostream>
#include <random>

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,2000000000);
    
    start("AbsoluteEntfernung", 255);

    set_speed(10);
    show_rotation(false);
    
    int steps = 0;

    while(!stand_on_ankh())
    {
        if(abyss_in_front()) break;
        
        move();
    }

    if(!stand_on_ankh())
    {
        turn_around();

        while(!stand_on_ankh())
        {
            if(abyss_in_front()) break;
        
            move();
        }
    }

    while(!stand_on_terminal())
    {
        if(abyss_in_front()) break;
        
        move();
        steps++;
    }

    if(!stand_on_terminal())
    {
        turn_around();
        move(steps);
        steps = 0;

        while(!stand_on_terminal())
        {
            if(abyss_in_front()) break;
        
            move();
            steps++;
        }
    }

    set_terminal_value(steps);
    turn_around();
    move(steps);
    
    end();
}
