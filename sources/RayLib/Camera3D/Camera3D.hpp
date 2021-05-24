/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera3D
*/

#ifndef CAMERA3D_HPP_
#define CAMERA3D_HPP_

#include <raylib.h>
#include "Vector3.hpp"

namespace RayLib
{
    class Camera3D
    {
        public:
            Camera3D(Vector3 position=Vector3(0.0f, 10.0f, 10.0f),
                    Vector3 target=Vector3(0.0f, 0.0f, 0.0f),
                    Vector3 up=Vector3(),
                    float fovy=45.0f,
                    int projection=CAMERA_PERSPECTIVE);

            ~Camera3D();

            // todo getters and setters

            void SetCameraMode(int mode);
            void BeginMode(void);
            void EndMode(void);



        protected:
        private:
            ::Camera3D camera;
    };
}

#endif /* !CAMERA3D_HPP_ */

