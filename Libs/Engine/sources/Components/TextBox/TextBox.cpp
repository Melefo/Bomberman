/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TextBox
*/

#include "TextBox.hpp"

namespace Component
{
    TextBox::TextBox(int lengthMax, const std::string& fontPath, float size, float spacing, RayLib::Color color, bool isAlpha, bool isNum)
        : _max(lengthMax), _font(AssetCache::GetAsset<RayLib::Font>(fontPath)), _color(color), _size(size), _spacing(spacing), _value(), _isAlpha(isAlpha), _isNum(isNum), _rect(0.0f, 0.0f, this->_font->MeasureText(std::string(_max, '0'), _size, _spacing).x, _size)
	{}

	void TextBox::Draw(RayLib::Vector2<float> position, RayLib::Vector2<float> scale)
	{
        float width = _rect.width;
        float height = _rect.height;

        _rect.x = position.x;
        _rect.y = position.y;
        _rect.width *= scale.x;
        _rect.height *= scale.y;

        this->_rect.DrawRectangle();
        this->_rect.DrawRectangleLines();

        _rect.width = width;
        _rect.height = height;

        this->_font->DrawText(this->_value, position, this->_size * scale.x, this->_spacing, this->_color);
	}

    bool TextBox::GetIsAlpha() const
    {
        return this->_isAlpha;
    }

    bool TextBox::GetIsNum() const
    {
        return this->_isNum;
    }

    const std::string& TextBox::GetValue() const
    {
        return this->_value;
    }

    RayLib::Rectangle TextBox::GetRectangle() const
    {
        return this->_rect;
    }

    void TextBox::AppendChar(char value)
    {
        if (static_cast<int>(this->_value.size()) < this->_max)
            this->_value += value;
    }

    void TextBox::RemoveChar()
    {
        if (this->_value.size() > 0)
            this->_value.pop_back();
    }
}