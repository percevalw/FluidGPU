//
// Created by Perceval Wajsburt on 11/02/2017.
//

#include "simulation.hpp"
#include "gl.h"

Simulation::Simulation(int width, int height, int particle_count, float timestep) {
    m_width = width;
    m_height = height;
    m_tics = 0;
    m_timestep = timestep;
    m_particle_system = new ParticleSystem(width, height, 50, particle_count);
}

Simulation::~Simulation() {
}

int Simulation::run() {
    bool loop = true;
    int new_tics = 0;
    int tics_delay = (int)(m_timestep * 1000);
    SDL_Event evenements;

    SDL_Window* fenetre;
    SDL_GLContext contexteOpenGL(0);

    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }


    // Version d'OpenGL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre

    fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }


    // Création du contexte OpenGL

    contexteOpenGL = SDL_GL_CreateContext(fenetre);

    if(contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();

        return -1;
    }

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,m_width,0,m_height);
    glClearColor(129.f/256, 181.f/256, 254.f/256, 1.f);

    while(loop)
    {
        SDL_PollEvent(&evenements);

        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            loop = false;

		new_tics = SDL_GetTicks();
		if (new_tics - m_tics > tics_delay) m_tics = new_tics;
		else SDL_Delay((Uint32)(tics_delay - (new_tics - m_tics)));

        glClear(GL_COLOR_BUFFER_BIT);

        m_particle_system->update(m_timestep);
        m_particle_system->render();

        glFlush();

        SDL_GL_SwapWindow(fenetre);
    }

    SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
