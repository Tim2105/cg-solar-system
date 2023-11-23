#include "space_object.h"

void Space_Object::update()
{
    /** \todo Update `model_matrix_` and position (`position_`) for each object.
    * 1. Combine translation and scaling matrices to get a result like in screenshots/planet_system_initial.png assuming:
    *   - sun at origin
    *   - all objects scaled by radius
    *   - all objects translated by `distance` in x direction
    * 2. Now use y-axis-rotation matrices in the right places to allow rotation
    *    around the object's axis (angle_self) and sun (angle_parent)
    * 3. You can also support a tilt angle if you like (`angle_tilt`) rotations
    * 4. Update the object's position using your constructed model matrix
    * Hints:
    *   - See glmath.h/cpp for an overview about implemented matrices.
    *   - Order is important!
    */

}

//-----------------------------------------------------------------------------

void Moon::update()
{
    /** \todo Update moon's `model_matrix_` and position (`position_`).
    *  The moon is a bit special, it must rotate around its `parent_planet_`. Be careful with the
    *  translation-rotation-order since rotation matrices always rotate around the current origin.
    */

}
//-----------------------------------------------------------------------------

void Space_Object::create_glow(float outer_radius, vec3 color)
{
    // create Billboard
    glow_ = new Billboard;

    // initialize texture layout
    glow_->texture_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR,
                         GL_LINEAR, GL_REPEAT);

    // create texture image
    int res = 1024;
    glow_->create_glow_texture(res, (int)(res / (2.0 * outer_radius)) - 1,
                               res / 2 - 1, color);

    // initialize quad vertex layouts
    glow_->init_GL_arrays();
}

//-----------------------------------------------------------------------------

void Space_Object::update_glow_angles(vec3 eye)
{
    if (glow_ != nullptr)
    {
        vec3 pos_to_eye = normalize(vec3(eye) - vec3(position_));
        glow_->update_angles(pos_to_eye);
    }
}

//=============================================================================
