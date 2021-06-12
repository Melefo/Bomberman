/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** IUIObject
*/

#ifndef IUIOBJECT_HPP_
#define IUIOBJECT_HPP_

#include "IComponent.hpp"
#include "Vector2.hpp"
#include "Asset.hpp"

namespace Component
{
    /**
     * @brief Base class for UI objects
     * 
     */
    class IUIObject : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new IUIObject object
             * 
             */
            IUIObject() = default;
            /**
             * @brief Destroy the IUIObject object
             * 
             */
            ~IUIObject() override = default;
            /**
             * @brief Construct a new IUIObject object
             * 
             * @param other 
             */
            IUIObject(const IUIObject& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return IUIObject& 
             */
            IUIObject& operator=(const IUIObject& other) = default;

            /**
             * @brief Draw UI object to window at position and scale
             * 
             * @param position 
             * @param scale 
             */
            virtual void Draw(RayLib::Vector2<float> position,
                              Asset& asset,
                              RayLib::Vector2<float> scale=RayLib::Vector2<float>(1.0f, 1.0f)) = 0;

        protected:
        private:
    };
}

#endif /* !IUIOBJECT_HPP_ */
