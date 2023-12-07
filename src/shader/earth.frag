#version 330
precision mediump float;

in vec3 v2f_normal;
in vec2 v2f_texcoord;
in vec3 v2f_light;
in vec3 v2f_view;

out vec4 f_color;

uniform sampler2D day_texture;
uniform sampler2D night_texture;
uniform sampler2D cloud_texture;
uniform sampler2D gloss_texture;
uniform bool greyscale;

const float shininess = 20.0;
const vec3  sunlight = vec3(1.0, 0.941, 0.898);
const float texInterpolCosAngle = 0.4;

vec3 mirror(vec3 vector, vec3 normal) {
    return 2 * normal * dot(normal, vector) - vector;
}

void main()
{
    vec3 color = vec3(0);
    vec3 dayColor = texture(day_texture, v2f_texcoord.st).rgb;
    vec3 nightColor = texture(night_texture, v2f_texcoord.st).rgb;
	float alpha = 1.0;

    float cloudiness = texture(cloud_texture, v2f_texcoord).r;
    float glossiness = texture(gloss_texture, v2f_texcoord).r;

    float cosTheta = dot(normalize(v2f_normal), normalize(v2f_light));

    vec3 ambientColor = vec3(0, 0, 0);
    vec3 diffuseColor = vec3(0, 0, 0);
    vec3 specularColor = vec3(0, 0, 0);

    if(cosTheta >= 0.0) {
        // Es ist Tag
        vec3 baseColor = dayColor;

        if(cosTheta < texInterpolCosAngle) {
            // Interpoliere zwischen Tag- und Nachtseite
            float t = cosTheta / texInterpolCosAngle;
            baseColor = mix(nightColor, baseColor, t);
            cloudiness = mix(0, cloudiness, t);
        }

        ambientColor = sunlight * baseColor * 0.2;
        diffuseColor = sunlight * baseColor * cosTheta;

        vec3 r = mirror(v2f_light, v2f_normal);
        float cosAlpha = dot(r, v2f_view);
        if(cosAlpha > 0.0)
            specularColor = sunlight * baseColor * pow(cosAlpha, shininess) * 0.2 * glossiness;
    } else {
        // Es ist Nacht
        ambientColor = sunlight * nightColor * 0.2;
        cloudiness = 0;
    }

    color = ambientColor + (diffuseColor + specularColor) * (1 - cloudiness);
    color += cloudiness * vec3(1, 1, 1);

    // convert RGB color to YUV color and use only the luminance
    if (greyscale) color = vec3(0.299*color.r+0.587*color.g+0.114*color.b);

    // add required alpha value
    f_color = vec4(color, alpha);

}
