//=============================================================================
//
//   Exercise code for the lecture "Computer Graphics"
//     by Prof. Mario Botsch, TU Dortmund
//
//   Copyright (C) by Computer Graphics Group, TU Dortmund
//
//=============================================================================
#include "billboard.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>

Billboard::Billboard() : Mesh(), size_(1.0), angle_x_(0), angle_y_(0) {}

//-----------------------------------------------------------------------------

Billboard::~Billboard() {}

//-----------------------------------------------------------------------------

void Billboard::create_glow_texture(int resolution, int inner_radius,
                                    int outer_radius, vec3 color)
{
    size_ = resolution / (2.0 * inner_radius);

    std::vector<float> img;
    int width = resolution;
    int height = resolution;
    img.resize(width * height * 4);

    /** \todo Setup the texture for the sun billboard by filling `img` with color values.
    *	- Draw an opaque (alpha == 1) circle with an `inner_radius` pixel radius in its middle
    *	- Outside that circle the texture should become more and more transparent (alpha < 1) to mimic a nice glow effect
    *   - Make sure that your texture is fully transparent (alpha == 0) at `outer_radius` to avoid seeing visible edges
    *	- Experiment with the color (set in `Solar_Viewer::initialize()`) and with how fast you change the transparency
    *     until the effect satisfies you
    **/

    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            img[(w * width + h) * 4 + 0] = 1.0; //red
            img[(w * width + h) * 4 + 1] = 1.0; //green
            img[(w * width + h) * 4 + 2] = 1.0; //blue
            img[(w * width + h) * 4 + 3] = 1.0; //alpha
        }
    }

    texture_.loadFromVector(img, width, height);
}

//-----------------------------------------------------------------------------

void Billboard::draw(GLenum mode)
{
    if (n_indices_ == 0)
        init_GL_arrays();

    texture_.bind();

    glBindVertexArray(vao_);
    glDrawElements(mode, n_indices_, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

//-----------------------------------------------------------------------------

bool Billboard::init_GL_arrays()
{
    std::cout << "creating billboard " << std::endl;

    GLfloat *positions = new GLfloat[3 * 4];
    GLuint *indices = new GLuint[3 * 2];
    GLfloat *tex_coords = new GLfloat[2 * 4];

    // generate vertices
    positions[0] = -1.0f;
    positions[1] = 1.0f;
    positions[2] = 0.0f;

    tex_coords[0] = 0.0f;
    tex_coords[1] = 1.0f;

    positions[3 + 0] = 1.0f;
    positions[3 + 1] = 1.0f;
    positions[3 + 2] = 0.0f;

    tex_coords[2 + 0] = 1.0f;
    tex_coords[2 + 1] = 1.0f;

    positions[6 + 0] = -1.0f;
    positions[6 + 1] = -1.0f;
    positions[6 + 2] = 0.0f;

    tex_coords[4 + 0] = 0.0f;
    tex_coords[4 + 1] = 0.0f;

    positions[9 + 0] = 1.0f;
    positions[9 + 1] = -1.0f;
    positions[9 + 2] = 0.0f;

    tex_coords[6 + 0] = 1.0f;
    tex_coords[6 + 1] = 0.0f;

    indices[0] = 0;
    indices[1] = 2;
    indices[2] = 1;

    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

    initialize(positions, positions, tex_coords, indices, 2, 4, 6);

    // clean up
    delete[] positions;
    delete[] tex_coords;
    delete[] indices;

    return true;
}

//-----------------------------------------------------------------------------

void Billboard::update_angles(const vec3 &billboard_to_eye)
{
    /** \todo update `angle_x_` and `angle_y_` of the billboard.
    *   - Make sure that the vector `billboard_to_eye` is always perpendicular to the billboard's plane
    *	- The two angles are related to the polar and azimuthal angle of a sphere
    *   - http://dynref.engr.illinois.edu/rvs.html shows a nice interactive demo and how to convert cartesian coordinates to spherical ones,
    *     but have in mind, that OpenGL uses another convention for x,y,z directions than in this example
    *   - The function `atan2(...)` is already defined.
    *   - Both should be stored in degree.
    *   - There is an offset between the spherical angles and the needed angles.
    *   Hint:
    *       It helps to set the look_at to the sun (key 1) and print `angle_x_` and `angle_y_`
    *       to find the right offset by pressing the right, left, up, down keys.
    *       The angles should start by 0 and the `x_angle_` should increase/decrease by pressing
    *       right/left by 10 degree (`y_angle_` analogously by pressing top/down)
    **/

}
