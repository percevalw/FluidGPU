

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "simulation.hpp"
#include <iostream>
#include "utils.hpp"

int main(int argc, char **argv)
{
    Simulation sim = Simulation(800, 600, 4000, 0.03);
    return sim.run();
}