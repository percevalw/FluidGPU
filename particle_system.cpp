//
// Created by Perceval Wajsburt on 11/02/2017.
//

#include "particle_system.hpp"
#include "utils.hpp"
#include "gl.h"
#include <limits>
#include <math.h>
#define LIMIT_MAX(a) std::numeric_limits<a>::max()

ParticleSystem::ParticleSystem(double width, double height, double kernel_radius, size_t particles_count) {

    m_width = width;
    m_height = height;
    m_particles_count = particles_count;
    m_kernel_radius = kernel_radius;

    m_locations = new Vec2<double>[m_particles_count];
    m_velocities = new Vec2<double>[m_particles_count];
    z_indices = new uint32_t[m_particles_count];

    for (int i=0; i<m_particles_count; i++) {
        m_locations[i] = Vec2<double>(Utils::randRange(0., m_width), Utils::randRange(0., m_height));
        m_velocities[i] = Vec2<double>(Utils::randRange(-1., 1.), Utils::randRange(-1., 1.));
    }

    m_block_size = (uint16_t)Utils::upper_power_of_two((uint32_t )(m_kernel_radius * LIMIT_MAX(uint16_t)/fmax(width, height)));

    m_block_size2 = m_block_size * m_block_size;

    m_blocks_count = ((LIMIT_MAX(uint16_t)+1)/m_block_size)*((LIMIT_MAX(uint16_t)+1)/m_block_size);

    m_sorted_particles = new uint32_t[m_particles_count];
    m_blocks = new Block[m_blocks_count];

    time = 0;
}

void ParticleSystem::updateBlocks() {
    uint16_t cell_x = 0,
             cell_y = 0;
    uint32_t block_id = 0;

    // Each particle, randomly distributed in the screen get assigned a z-index
    // z_indices : i -> z_index of particle i
    for (int i=0; i<m_blocks_count; i++) {
        m_blocks[i] = {.index= LIMIT_MAX(uint32_t), .particles_count= 0};
    }
    for (int i=0; i<m_particles_count; i++) {

        cell_x = (uint16_t) (m_locations[i].x * LIMIT_MAX(uint16_t) / m_width);
        cell_y = (uint16_t) (m_locations[i].y * LIMIT_MAX(uint16_t) / m_height);
        z_indices[i] = Utils::morton2d<uint16_t, uint32_t>(cell_x, cell_y);
    }
    // We sort the particles along their z-index
    // m_sorted_particles : i -> original index of the particle
    Utils::radix_sort(z_indices, m_sorted_particles, m_particles_count);

    // We go through the sorted particles
    for (uint i=0; i<m_particles_count; i++) {
        // We get the original index of the particle and its z_index
        // to get the block id : the id is to describe each block
        // by the first particle it contains and its particle count
        // since particles are now sorted. Indeed we now need the
        // index of the particle in the sorted array to have the origin
        // of the block.
        block_id = z_indices[m_sorted_particles[i]]/m_block_size2;
        if (m_blocks[block_id].index > i)
            m_blocks[block_id].index = i;
        m_blocks[block_id].particles_count ++;
    }
}

void ParticleSystem::update(double timestep) {
    updateBlocks();
    for (int i=0; i<m_particles_count; i++) {
        m_locations[i] += m_velocities[i] * timestep;
    }
    time += timestep;
}

void ParticleSystem::render() {
    glPointSize(5.f);
    glColor3ub(0,0,255);
    uint32_t particle_i;

    uint32_t max_z_indice = LIMIT_MAX(uint32_t);

    uint32_t m1 = Utils::morton2d<uint32_t, uint16_t>(1, 1);
    uint32_t m_u = Utils::morton_dec_y(m1);
    uint32_t m_d = Utils::morton_inc_y(m1);
    uint32_t m_l = Utils::morton_dec_x(m1);
    uint32_t m_r = Utils::morton_inc_x(m1);
    uint32_t m_d_l = Utils::morton_dec_x(m_d);
    uint32_t m_d_r = Utils::morton_inc_x(m_d);
    uint32_t m_u_l = Utils::morton_dec_x(m_u);
    uint32_t m_u_r = Utils::morton_inc_x(m_u);
    Block b = m_blocks[(int)(time*6) % m_blocks_count];
    glBegin(GL_POINTS);
        for (int i=0; i<m_particles_count; i++) {
            particle_i = m_sorted_particles[i];
            if (i == b.index)
                glColor3ub(255, 0, 0);
            if (i == b.index+b.particles_count)
                glColor3ub(0, 0, 255);
            //if ((int)(particle_i/m_particles_count) % 4 == 0)
            //    //glColor3ub(0, 0, 255);
            //    glColor3ub(
            //            (GLubyte)(255*(z_indices[particle_i]/((double)max_z_indice))),
            //            (GLubyte)(255*(z_indices[particle_i]/((double)max_z_indice))),
            //            (GLubyte)(255*(z_indices[particle_i]/((double)max_z_indice)))
            //    );
            //else
            //    glColor3ub(0, 0, 0);
            glVertex2d(m_locations[particle_i].getX(), m_locations[particle_i].getY());
        }
    glEnd();
}

ParticleSystem::~ParticleSystem() {
    delete [] m_locations;
    delete [] m_velocities;
    delete[] m_sorted_particles;
    delete[] m_blocks;
    delete[] z_indices;
}
