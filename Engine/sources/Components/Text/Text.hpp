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

namespace Component
{
    class Text : public ECS::IComponent {
        public:
            Text(std::string str="", 
                RayLib::Font font=RayLib::Font(), 
                RayLib::Color color=RayLib::Color(), 
                unsigned int size = 10);
            ~Text() override = default;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            std::string string;
            RayLib::Font font;
            RayLib::Color color;
            unsigned int size;

        protected:
        private:
    };
}

#endif /* !TEXT_HPP_ */
