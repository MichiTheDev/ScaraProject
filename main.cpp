import scara_functions;
import NNumber;
import path_finding;

#include <iostream>
#include <random>

int main()
{
    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> dist(0,2000000000);
    //
    // start("AufKuerzestemWeg", dist(rng));
    //
    // show_roation(false);
    // set_speed(10);
    // move_with_shortest_path();
    //
    // end();

    NNumber n1{ 6 };
    NNumber n2{ 8 };

    std::cout << n1.is_perfect() << std::endl;
    std::cout << n2.is_perfect() << std::endl;
}
