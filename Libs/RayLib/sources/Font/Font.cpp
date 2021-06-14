/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Font
*/

#include "Font.hpp"

namespace RayLib
{
    Font::Font()
    {
        font = GetFontDefault();
    }

    Font::Font(const std::string &fileName)
    {
        font = LoadFont(fileName.c_str());
    }

    Font::Font(const Font &newFont)
    {
        font.baseSize = newFont.font.baseSize;
        font.chars = newFont.font.chars;
        font.charsCount = newFont.font.charsCount;
        font.recs = newFont.font.recs;
        font.texture = newFont.font.texture;
    }

    Font::Font(const ::Font &newFont)
    {
        font.baseSize = newFont.baseSize;
        font.chars = newFont.chars;
        font.charsCount = newFont.charsCount;
        font.recs = newFont.recs;
        font.texture = newFont.texture;
    }

    Font& Font::operator=(const Font &newFont)
    {
        font.baseSize = newFont.font.baseSize;
        font.chars = newFont.font.chars;
        font.charsCount = newFont.font.charsCount;
        font.recs = newFont.font.recs;
        font.texture = newFont.font.texture;
        return (*this);
    }

    void Font::DrawText(const std::string &text, Vector2<float> position, float fontSize, float spacing, Color tint)
    {
        ::DrawTextEx(font, text.c_str(), position.getVector2(), fontSize, spacing, tint.getColor());
    }

    Vector2<float> Font::MeasureText(std::string& text, float fontSize, float spacing)
    {
        return (::MeasureTextEx(font, text.c_str(), fontSize, spacing));
    }

    Font::~Font()
    {
        UnloadFont(font);
    }
}
