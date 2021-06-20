/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TextUI
*/

#include "AssetCache.hpp"
#include "TextUI.hpp"

namespace Component
{
    TextUI::TextUI(std::string startStr, const std::string& fontPath, float startSize, float spacing, RayLib::Color startColor) :
    _string(startStr), _font(AssetCache::GetAsset<RayLib::Font>(fontPath)), _color(startColor), _size(startSize), _spacing(spacing)
    {
    }

    void TextUI::Draw(RayLib::Vector2<float> position, RayLib::Vector2<float>scale)
    {
        _font->DrawText(_string, position, _size * scale.x, _spacing, _color);
    }

    std::string& TextUI::GetContent(void)
    {
        return (_string);
    }

    void TextUI::SetString(const std::string& newString)
    {
        _string = newString;
    }

    float TextUI::GetSpacing(void)
    {
        return (_spacing);
    }

    void TextUI::SetSpacing(float spacing)
    {
        _spacing = spacing;
    }

    float TextUI::GetSize(void)
    {
        return (_size);
    }

    void TextUI::SetSize(float size)
    {
        _size = size;
    }

    RayLib::Vector2<float> TextUI::MeasureText()
    {
        return (_font->MeasureText(_string, _size, _spacing));
    }
}
