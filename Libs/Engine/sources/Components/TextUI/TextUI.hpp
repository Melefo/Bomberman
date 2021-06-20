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
            /**
             * @brief Construct a new TextUI object
             * 
             * @param str 
             * @param font 
             * @param size 
             * @param spacing 
             * @param color 
             */
            TextUI(std::string str,
                   const std::string& font,
                   float size = 10.0,
                   float spacing = 0.0f,
                   RayLib::Color color=BLACK);
            /**
            * @brief Destroy the TextUI object
            * 
            */
            ~TextUI() override = default;
            /**
             * @brief Construct a new TextUI object
             * 
             * @param other 
             */
            TextUI(const TextUI& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return TextUI& 
             */
            TextUI& operator=(const TextUI& other) = default;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            /**
             * @brief Draw text
             * 
             * @param position 
             * @param scale 
             */
            void Draw(RayLib::Vector2<float> position,
                              RayLib::Vector2<float> scale=RayLib::Vector2<float>(1.0f, 1.0f)) override;

            /**
             * @brief Get the Content object
             * 
             * @return std::string& 
             */
            std::string& GetContent(void);
            /**
             * @brief Set the String object
             * 
             * @param newString 
             */
            void SetString(const std::string& newString);

            /**
             * @brief Get the Spacing object
             * 
             * @return float 
             */
            float GetSpacing(void);
            /**
             * @brief Set the Spacing object
             * 
             * @param spacing 
             */
            void SetSpacing(float spacing);

            /**
             * @brief Get the Size object
             * 
             * @return float 
             */
            float GetSize(void);
            /**
             * @brief Set the Size object
             * 
             * @param size 
             */
            void SetSize(float size);

            /**
             * @brief Return the size of the text
             * 
             * @return RayLib::Vector2<float> 
             */
            RayLib::Vector2<float> MeasureText();


        protected:
        private:
            std::string _string;
            std::shared_ptr<RayLib::Font> _font;
            RayLib::Color _color;
            float _size;
            float _spacing;
    };
}

#endif /* !TextUI_HPP_ */
