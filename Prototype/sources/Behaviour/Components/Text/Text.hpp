/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "IComponent.hpp"
#include "Font.hpp"
#include "Color.hpp"

namespace Prototype
{
    class Text : public ECS::IComponent {
        public:
            Text(std::string str="", 
                 Raylib::Font font=Raylib::Font(), 
                 Raylib::Color color=Raylib::Color(), 
                 unsigned int size = 10);
            ~Text() override = default;

            std::string string;
            Raylib::Font font;
            Raylib::Color color;
            unsigned int size;
        protected:
        private:
    };
}

#endif /* !TEXT_HPP_ */
