//
// Created by Perceval Wajsburt on 11/02/2017.
//

#ifndef FLUIDGPU_SIMULATION_H
#define FLUIDGPU_SIMULATION_H

#include <SDL2/SDL.h>
#include "particle_system.hpp"

class Simulation {
    int m_width;
    int m_height;
    long int m_tics;
    float m_timestep;

    ParticleSystem* m_particle_system;

    public:
        Simulation(int width, int height, int particle_count, float timestep);
        ~Simulation();
        int run();
};


#endif //FLUIDGPU_SIMULATION_H
