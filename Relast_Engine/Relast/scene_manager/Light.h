#pragma once

#ifndef __R_LIGHT__
#define __R_LIGHT__

#include "../core/Tools.h"
#include "Entities.h"

namespace Relast
{
    namespace scene_manager
    {
        class Light :
            public Entity3D
        {
        private:
        protected:
            Light_config* _light_config;
        public:
            Light() 
            {
                if (this->_light_config != nullptr)
                {
                    this->_ambient_color = this->_light_config->_ambient_color;
                    this->_diffuse_color = this->_light_config->_diffuse_color;
                    this->_specular_color = this->_light_config->_specular_color;
                    this->_ambient_intensity = this->_light_config->_ambient_intensity;
                    this->_diffuse_intensity = this->_light_config->_diffuse_intensity;
                    this->_specular_intensity = this->_light_config->_specular_intensity;
                    this->_specular_pow = this->_light_config->_specular_pow;
                }
            };
            ~Light() {};

            Color _ambient_color = Color();
            Color _diffuse_color = Color();
            Color _specular_color = Color();
            FLOAT _ambient_intensity = 1.0f;
            FLOAT _diffuse_intensity = 1.0f;
            FLOAT _specular_intensity = 1.0f;
            FLOAT _specular_pow = 1.0f;

            Light_config* get_light_config() { return this->_light_config; };
            uniforms_config::Uniform_3f* ambient_color_uniform() { return new uniforms_config::Uniform_3f(this->_ambient_color._r, this->_ambient_color._g, this->_ambient_color._b); };
            uniforms_config::Uniform_3f* diffuse_color_uniform() { return new uniforms_config::Uniform_3f(this->_diffuse_color._r, this->_diffuse_color._g, this->_diffuse_color._b); };
            uniforms_config::Uniform_3f* specular_color_uniform() { return new uniforms_config::Uniform_3f(this->_specular_color._r, this->_specular_color._g, this->_specular_color._b); };
            uniforms_config::Uniform_1f* ambient_level_uniform() { return new uniforms_config::Uniform_1f(this->_ambient_intensity); };
            uniforms_config::Uniform_1f* diffuse_level_uniform() { return new uniforms_config::Uniform_1f(this->_diffuse_intensity); };
            uniforms_config::Uniform_1f* specular_level_uniform() { return new uniforms_config::Uniform_1f(this->_specular_intensity); };
            uniforms_config::Uniform_1f* shininess_uniform() { return new uniforms_config::Uniform_1f(this->_specular_pow); };

            void light_config(Light_config* config) { this->_light_config = config; };

            virtual void loop() {};
        };
    }
}


#endif // !__R_LIGHT__