//=============================================================================
//
//   Exercise code for the lecture "Computer Graphics"
//     by Prof. Mario Botsch, TU Dortmund
//
//   Copyright (C) by Computer Graphics Group, TU Dortmund
//
//=============================================================================
#pragma once
//=============================================================================

#include "glmath.h"
#include "texture.h"
#include "mesh.h"

#include <vector>

//=============================================================================

class Billboard : public Mesh
{
public:
    //! default constructor
    Billboard();

    //! default destructor
    ~Billboard();

    //! function that sets up the glow texture's color values
    //! \resolution is the textures resolution (with == height) in pixels
    //! \inner_radius is the radius from center in pixel below which the texture is fully opaque
    //! \outer_radius is the radius from center in pixel above which the texture is fully transparent
    //! \color is the glow's color
    void create_glow_texture(int resolution, int inner_radius, int outer_radius,
                             vec3 color);

    //! computes rotation angles for our billboard
    void update_angles(const vec3 &billboard_to_eye);

    //! init OpenGL arrays
    bool init_GL_arrays();

    //! render the billboard
    void draw(GLenum mode = GL_TRIANGLES) override;

    //! rotation angles
    float angle_x_, angle_y_;

    //! size of our billboard
    float size_;

    //! billboards texture
    Texture texture_;
};
