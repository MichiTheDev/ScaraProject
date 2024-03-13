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
    
    start("Seitenwechsel", dist(rng));
    
    set_speed(20);
    show_rotation(false);
    
    std::vector<int> bottom_glyph_positions;
    std::vector<int> top_glyph_positions;
    
    Scara::dreheLinks();
    Scara::dreheLinks();
    Scara::dreheLinks();
    while(!Scara::istVorneAbgrund())
    {
        Scara::gehe();
    }
    
    Scara::dreheLinks();
    
    int x = 0;
    while(!Scara::istVorneAbgrund())
    {
        Scara::gehe();
        ++x;
    
        Scara::dreheLinks();
    
        if(!Scara::istVorneAbgrund())
        {
            bottom_glyph_positions.push_back(x);
        }
    
        Scara::dreheLinks();
        Scara::dreheLinks();
        Scara::dreheLinks();
    }
    
    Scara::dreheLinks();
    
    while (!Scara::istVorneAbgrund())
    {
        Scara::gehe();
    }
    
    Scara::dreheLinks();
    
    x = 0;
    while(!Scara::istVorneAbgrund())
    {
        Scara::gehe();
        ++x;
    
        Scara::dreheLinks();
    
        if(!Scara::istVorneAbgrund())
        {
            top_glyph_positions.push_back(x);
        }
    
        Scara::dreheLinks();
        Scara::dreheLinks();
        Scara::dreheLinks();
    }

    if(bottom_glyph_positions.size() != 0 || top_glyph_positions.size() != 0)
    {
        Scara::dreheLinks();
    
        while(!Scara::istVorneAbgrund())
        {
            Scara::gehe();
        }
        
        Scara::dreheLinks();
        
        x = 0;
        int bottom_row = 0;
        while(true)
        {
            Scara::gehe();
            ++x;
        
            if(bottom_glyph_positions[bottom_row] == x)
            {
                ++bottom_row;
        
                Scara::dreheLinks();
        
                Scara::gehe();
        
                while(true)
                {
                    if(Scara::istSteinVerschiebbar() && Scara::istVorneAbgrund())
                    {
                        Scara::schiebeStein();
                    }
                    else
                    {
                        Scara::gehe();
                        break;
                    }
                }
        
                Scara::dreheLinks();
        
                while(!Scara::istVorneAbgrund())
                {
                    Scara::gehe();
                }
        
                Scara::dreheLinks();
        
                while(!Scara::istVorneAbgrund())
                {
                    Scara::gehe();
                }
        
                Scara::dreheLinks();
                
                if(bottom_row >= bottom_glyph_positions.size() - 1)
                {
                    break;
                }
        
                x = 0;
            }
        }
        
        while(!Scara::istVorneAbgrund())
        {
            Scara::gehe();
        }
        
        Scara::dreheLinks();
        
        while(!Scara::istVorneAbgrund())
        {
            Scara::gehe();
        }
        
        Scara::dreheLinks();
        
        int top_row = 0;
        x = 0;
        while(true)
        {
            Scara::gehe();
            ++x;
        
            if(top_glyph_positions[top_row] == x)
            {
                ++top_row;
        
                Scara::dreheLinks();
        
                Scara::gehe();
        
                while(true)
                {
                    if(Scara::istSteinVerschiebbar() && Scara::istVorneAbgrund())
                    {
                        Scara::schiebeStein();
                    }
                    else
                    {
                        Scara::gehe();
                        break;
                    }
                }
        
                Scara::dreheLinks();
        
                while(!Scara::istVorneAbgrund())
                {
                    Scara::gehe();
                }
        
                Scara::dreheLinks();
        
                while(!Scara::istVorneAbgrund())
                {
                    Scara::gehe();
                }
        
                Scara::dreheLinks();
        
                if(top_row >= top_glyph_positions.size() - 1)
                {
                    break;
                }
        
                x = 0;
            }
        }
    }
    
    while(true)
    {
        if(Scara::stehtAufAnkh()) break;
    
        if(!Scara::istVorneAbgrund())
        {
            Scara::gehe();
        }
        else
        {
            Scara::dreheLinks();
            Scara::gehe();
        }
    }
    
    end();
}