/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TextBox
*/

#ifndef TextBox_HPP_
#define TextBox_HPP_

#include <string>
#include "IUIObject.hpp"
#include "IBehaviour.hpp"
#include "Color.hpp"
#include "Font.hpp"
#include "AssetCache.hpp"

namespace Component
{
    /**
     * @brief Component where it's possible to enter text and show it
     * 
     */
	class TextBox : public IUIObject
	{
        public:
            /**
             * @brief Construct a new Text Box object
             * 
             * @param lengthMax 
             * @param font 
             * @param size 
             * @param spacing 
             * @param color 
             * @param isAlpha 
             * @param isNum 
             */
		    TextBox(int lengthMax,
                const std::string& font,
                float size = 10.0,
                float spacing = 0.0f,
                RayLib::Color color = BLACK, 
                bool isAlpha = true,
                bool isNum = true);
            /**
             * @brief Destroy the Text Box object
             * 
             */
            ~TextBox() override = default;
            /**
             * @brief Construct a new copy Text Box object
             * 
             * @param other 
             */
            TextBox(const TextBox& other) = default;
            /**
             * @brief Construct a new assigned Text Box object
             * 
             * @param other 
             * @return TextBox& 
             */
            TextBox& operator=(const TextBox& other) = default;

            /**
            * @brief Draw the texture at given position and scale
            *
            * @param position
            * @param scale
            */
            void Draw(RayLib::Vector2<float> position,
                RayLib::Vector2<float> scale = RayLib::Vector2<float>(1.0f, 1.0f)) override;
            /**
             * @brief Get the IsAlpha object
             * 
             * @return true 
             * @return false 
             */
            bool GetIsAlpha() const;
            /**
             * @brief Get the IsNum object
             * 
             * @return true 
             * @return false 
             */
            bool GetIsNum() const;
            /**
             * @brief Get the Value object
             * 
             * @return const std::string& 
             */
            const std::string& GetValue() const;
            /**
             * @brief Get the Rectangle object
             * 
             * @return RayLib::Rectangle 
             */
            RayLib::Rectangle GetRectangle() const;
            /**
             * @brief Remove a char from the current value
             * 
             */
            void RemoveChar();
            /**
             * @brief Append a char to the current value
             * 
             * @param value 
             */
            void AppendChar(char value);
        private:
            /**
             * @brief Length maximum of the value
             * 
             */
            int _max;
            /**
             * @brief Font used to display the value
             * 
             */
            std::shared_ptr<RayLib::Font> _font;
            /**
             * @brief Color used to display the value
             * 
             */
            RayLib::Color _color;
            /**
             * @brief Size of the font
             * 
             */
            float _size;
            /**
             * @brief Spacing of the chars
             * 
             */
            float _spacing;
            /**
             * @brief Current value of the TextBox
             * 
             */
            std::string _value;
            /**
             * @brief Is the TextBox accepting Alpha chars
             * 
             */
            bool _isAlpha;
            /**
             * @brief Is the TextBox acceptins Numerical chars
             * 
             */
            bool _isNum;
            /**
             * @brief Rectangle used to delimit the TextBox
             * 
             */
            RayLib::Rectangle _rect;
            std::ostream& operator<<(std::ostream& os) override { return os; };
            std::istream& operator>>(std::istream& is) override { return is; };
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree& ptree) override { return ptree; };
	};
}

#endif /* !TextBox_HPP_ */
