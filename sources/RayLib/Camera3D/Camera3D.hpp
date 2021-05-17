/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera3D
*/

#ifndef CAMERA3D_HPP_
#define CAMERA3D_HPP_

#include <raylib.h>

namespace RayLib
{
    class Camera3D
    {
        public:
            Camera3D();
            ~Camera3D();

        protected:
        private:
            ::Camera3D camera;
    };
}

#endif /* !CAMERA3D_HPP_ */

