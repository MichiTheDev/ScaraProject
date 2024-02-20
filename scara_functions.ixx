module;

#include "scara.h"

export module scara_functions;

export void start(const std::string& level_name, const int scenario = 0)
{
    Scara::starte(level_name, scenario);
}

export void end()
{
    Scara::beende();
}

export void move(const int steps = 1)
{
    for (int i = 0; i < steps; ++i)
    {
        Scara::gehe();
    }
}

export void turn_left()
{
    Scara::dreheLinks();
}

export void turn_around()
{
    Scara::dreheLinks();
    Scara::dreheLinks();
}

export void turn_right()
{
    Scara::dreheLinks();
    Scara::dreheLinks();
    Scara::dreheLinks();
}

export bool stand_on_ankh()
{
    return Scara::stehtAufAnkh();
}

export bool check_for_ankh_then_move()
{
    if(Scara::stehtAufAnkh()) return true;
    Scara::gehe();
    return false;
}

export bool move_then_check_for_ankh()
{
    Scara::gehe();
    return Scara::stehtAufAnkh();
}

export int scan_tile_at(const int x, const int y)
{
    return Scara::scannePosition(x, y);
}

export bool is_tile(const int mask_to_check, const int mask)
{
    return mask_to_check & 1 << mask;
}

export void set_speed(int speed)
{
    Scara::setzeTempo(speed);
}

export void show_rotation(bool value)
{
    Scara::zeigeDrehung(value);
}

export bool abyss_in_front()
{
    return Scara::istVorneAbgrund();
}

export void set_terminal_value(const int& value)
{
    Scara::setzeTerminalwert(value);
}

export int get_terminal_value()
{
    return Scara::holeTerminalwert();
}

export int get_terminal_id()
{
    return Scara::holeTerminalnummer();
}

export bool stand_on_terminal()
{
    return Scara::stehtAufTerminal();
}

export bool move_until_terminal(int& steps)
{
    while(!abyss_in_front())
    {
        move();
        steps++;
        if(stand_on_terminal())
        {
            return true;
        }
    }
    return false;
}