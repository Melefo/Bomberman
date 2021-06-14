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
    /**
     * @brief Camera3D
     * Encapsulation of the raylib structure Camera3D
     */
    class Camera3D
    {
        public:

            /**
             * @brief Construct a new Camera 3D object
             * 
             * @param position the camera's position in world space (default: x:0.0 y: 10.0 z:10.0)
             * @param target the camera will face these coordinates
             * @param up the camera's upwards vector in local space
             * @param fovy the camera's field of view in degrees
             * @param projection camera mode
             */
            Camera3D(Vector3 position=Vector3(0.0f, 10.0f, 10.0f),
                    Vector3 target=Vector3(0.0f, 0.0f, 0.0f),
                    Vector3 up=Vector3(0.0f, 1.0f, 0.0f),
                    float fovy=45.0f,
                    int projection=CAMERA_PERSPECTIVE);

            /**
             * @brief Destroy the Camera 3 D object
             * 
             */
            ~Camera3D() = default;

            // todo getters and setters

            /**
             * @brief Set the Camera Mode
             * 
             * @param mode 
             */
            void SetCameraMode(int mode);

            /**
             * @brief Begin 3D mode
             * 
             */
            void BeginMode(void);

            /**
             * @brief End 3D mode
             * 
             */
            void EndMode(void);

            /**
             * @brief Update the camera based on mode
             * 
             */
            void Update(void);

            /**
             * @brief Get the a ray pointing from camera to mouseposition
             * 
             * @param mousePos 
             * @return Ray 
             */
            Ray GetMouseRay(Vector2<float> mousePos);

            /**
             * @brief Get the camera structure
             * 
             * @return ::Camera3D 
             */
            ::Camera3D GetCamera();

            /**
             * @brief Set the Position of camera
             * 
             * @param position 
             */
            void SetPosition(Vector3 position);

            /**
             * @brief Get the Position
             * 
             * @return const Vector3& 
             */
            const Vector3 GetPosition();

            /**
             * @brief Get the Target
             * 
             * @return const Vector3
             */
            const Vector3 GetTarget();

            /**
             * @brief Set the Target of camera
             * 
             * @param targetPosition 
             */
            void SetTarget(Vector3 targetPosition);

            /**
             * @brief Convert world position to screen position
             * 
             * @param position 
             * @return Vector2<int> 
             */
            Vector2<int> GetWorldToScreen(Vector3 position);



        protected:
        private:
            ::Camera3D _camera;
    };
}

#endif /* !CAMERA3D_HPP_ */

