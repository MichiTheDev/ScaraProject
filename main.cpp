import scara_functions;
import path_finding;

#include <iostream>
#include <random>

#include "scara.h"

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,2000000000);
    
    start("LueckenSchliessen", 123213);
    
    set_speed(5);
    show_rotation(false);

    bool end_reached = false;
    
    Scara::gehe();

    while (true)
    {
        while (!Scara::istVorneAbgrund())
        {
            Scara::gehe();
        }
    
        while(Scara::istVorneAbgrund())
        {
            Scara::schiebeStein();
        }

        Scara::gehe();

        if(!Scara::istSteinVerschiebbar())
        {
            end_reached = true;
        }
        
        if(end_reached)
        {
            Scara::dreheLinks();
            Scara::dreheLinks();
            Scara::gehe();
            while(Scara::istVorneAbgrund())
            {
                if(!Scara::istSteinVerschiebbar()) break;
                Scara::schiebeStein();
            }
        }
        else
        {
            bool first_loop = true;
            do
            {
                if(!first_loop)
                {
                    Scara::gehe();
                }
                
                Scara::dreheLinks();
                Scara::schiebeStein();
    
                Scara::dreheLinks();
                Scara::schiebeStein();
                Scara::schiebeStein();
    
                Scara::dreheLinks();
                Scara::schiebeStein();
                Scara::dreheLinks();

                Scara::dreheLinks();
                Scara::dreheLinks();

                if(Scara::istVorneAbgrund())
                {
                    Scara::dreheLinks();
                    Scara::dreheLinks();
                }
                first_loop = false;
            } while(!Scara::istVorneAbgrund());
        }
        
        if(end_reached)
        {
            break;
        }
        
        Scara::dreheLinks();
        Scara::dreheLinks();
        Scara::gehe();
    }
    
    end();
}

