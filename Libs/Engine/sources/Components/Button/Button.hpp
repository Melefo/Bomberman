/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "IComponent.hpp"
#include <functional>
#include <vector>
#include "Texture.hpp"
#include "IUIObject.hpp"
#include "Rectangle.hpp"
#include "Mouse.hpp"
#include "BoundingBox.hpp"

namespace Component
{
    /**
     * @brief Button class
     * 
     */
    class Button : public IUIObject {
        public:
            /**
             * @brief Construct a new Button object
             * 
             */
            Button(const std::string& path);
            /**
             * @brief Destroy the Button object
             * 
             */
            ~Button() override = default;
            /**
             * @brief Construct a new Button object
             * 
             * @param other 
             */
            Button(const Button& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Button& 
             */
            Button& operator=(const Button& other) = default;

            /**
             * @brief Draw the texture at given position and scale
             * 
             * @param position 
             * @param scale 
             */
            void Draw(RayLib::Vector2<float> position,
                      RayLib::Vector2<float> scale=RayLib::Vector2<float>(1.0f, 1.0f)) override;

            /**
             * @brief Returns true if the mouse is in button bounds
             * 
             * @return true 
             * @return false 
             */
            bool IsMouseOver(void);
            /**
             * @brief Add a function with the form void() to the list of callbacks
             * Use std::bind to send a function (static or other)
             * If it is a non-static member function, pass this as the second argument
             * _button.AddCallback(std::bind(&ButtonCallbacks::SayHello, this));
             *  button.AddCallback(std::bind(&Component::ButtonCallbacks::StaticCallback));
             * @param callBack 
             */
            void AddCallback(std::function<void()> callBack);
            /**
             * @brief Execute all the _callbacks
             * 
             */
            void OnClick(void);

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            // todo getrect

        protected:
        private:
            /**
             * @brief rectangle containing size and position
             * 
             */
            RayLib::Rectangle _rect;
            /**
             * @brief Functions to call onclick
             * 
             */
            std::vector<std::function<void()>> _callbacks;

            RayLib::Color _tint;

            std::shared_ptr<RayLib::Texture> _texture;
    };
}

#endif /* !BUTTON_HPP_ */
