//
// Created by Perceval Wajsburt on 11/02/2017.
//

#ifndef FLUIDGPU_PARTICLESYSTEM_H
#define FLUIDGPU_PARTICLESYSTEM_H

class ParticleSystem;

#include "vec2.hpp"

typedef struct {
	uint32_t index;
	uint particles_count;
} Block;

class ParticleSystem {

	protected:
        Vec2<double>* m_locations;  // The particles
        Vec2<double>* m_velocities;  // The particles
        uint32_t* m_sorted_particles;  // The particles
        Block* m_blocks;  // The particles

		double m_width, m_height;
        double m_particle_mass;
        double m_kernel_radius;
        size_t m_particles_count, m_blocks_count;
		uint32_t m_block_size, m_block_size2;
        uint32_t *z_indices;

        double time;

	public:
        ParticleSystem(double width, double height, double kernel_radius, size_t particle_count);
        ~ParticleSystem();

		void updateBlocks();

    void render();
        void update(double timestep);
};


#endif //FLUIDGPU_PARTICLESYSTEM_H
