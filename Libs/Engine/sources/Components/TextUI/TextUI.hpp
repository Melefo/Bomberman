/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TextUI
*/

#ifndef TextUI_HPP_
#define TextUI_HPP_

#include "IComponent.hpp"
#include "IUIObject.hpp"
#include "Font.hpp"
#include "Color.hpp"

namespace Component
{
    class TextUI : public IUIObject {
        public:
            TextUI(std::string str,
                   const std::string& font,
                   float size = 10.0,
                   float spacing = 0.0f,
                   RayLib::Color color=BLACK);
            ~TextUI() override = default;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};


            void Draw(RayLib::Vector2<float> position,
                              RayLib::Vector2<float> scale=RayLib::Vector2<float>(1.0f, 1.0f)) override;

            std::string& GetContent(void);
            void SetString(const std::string& newString);

            float GetSpacing(void);
            void SetSpacing(float spacing);

            float GetSize(void);
            void SetSize(float size);

            RayLib::Vector2<float> MeasureText();


        protected:
        private:
            std::string _string;
            RayLib::Font _font;
            RayLib::Color _color;
            float _size;
            float _spacing;
    };
}

#endif /* !TextUI_HPP_ */
