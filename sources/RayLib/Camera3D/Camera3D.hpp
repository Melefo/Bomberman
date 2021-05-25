/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera3D
*/

#ifndef CAMERA3D_HPP_
#define CAMERA3D_HPP_

#include <raylib.h>
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

namespace RayLib
{
    class Camera3D
    {
        public:
            Camera3D(Vector3 position=Vector3(0.0f, 10.0f, 10.0f),
                    Vector3 target=Vector3(0.0f, 0.0f, 0.0f),
                    Vector3 up=Vector3(0.0f, 1.0f, 0.0f),
                    float fovy=45.0f,
                    int projection=CAMERA_PERSPECTIVE);

            ~Camera3D();

            // todo getters and setters

            void SetCameraMode(int mode);
            void BeginMode(void);
            void EndMode(void);

            void Update(void);

            Ray GetMouseRay(Vector2<float> mousePos);



        protected:
        private:
            ::Camera3D _camera;
    };
}

#endif /* !CAMERA3D_HPP_ */

