/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_

#include <raylib.h>
#include <string>

namespace RayLib
{
    class Font {
        public:
            Font();
            Font(const std::string &fileName);
            Font(const Font &font);
            Font(const ::Font &font);
            Font& operator=(const Font &font);

            void DrawText(const std::string &text, Vector2 position, float fontSize, float spacing=0, Color tint=Color(WHITE));

            ~Font();


            ::Font font;
        protected:
        private:
    };
}

#endif /* !FONT_HPP_ */
