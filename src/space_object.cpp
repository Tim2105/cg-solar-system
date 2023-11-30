#include "space_object.h"

void Space_Object::update()
{
   mat4 matScaling = mat4::scale(radius_);
   mat4 matRotationParent = mat4::rotate_y(angle_parent_);
   vec3 rotationAxis = mat4::rotate_z(angle_tilt_) * vec4(0, 1, 0, 0);
   mat4 matRotationSelf = mat4::rotate_angle_axis(angle_self_, rotationAxis) * mat4::rotate_z(angle_tilt_);
   mat4 matTranslation = mat4::translate(vec3(distance_, 0, 0));

    model_matrix_ = matRotationParent * matTranslation * matRotationSelf * matScaling;
    position_ = matRotationParent * vec4(distance_, 0, 0, 1.0);
}

//-----------------------------------------------------------------------------

void Moon::update()
{
    mat4 matScaling = mat4::scale(radius_);
    mat4 matRotationParent = mat4::rotate_y(angle_parent_);
    vec3 rotationAxis = mat4::rotate_z(angle_tilt_) * vec4(0, 1, 0, 0);
    mat4 matRotationSelf = mat4::rotate_angle_axis(angle_self_, rotationAxis);
    mat4 matTranslation = mat4::translate(vec3(distance_, 0, 0));
    mat4 matTranslationParent = mat4::translate(parent_planet_->position_);

    model_matrix_ = matTranslationParent * matRotationParent *
                    matTranslation * matRotationSelf * matScaling;
    position_ = matTranslationParent * matRotationParent * vec4(distance_, 0, 0, 1.0);
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
