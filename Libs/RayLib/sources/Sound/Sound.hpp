/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <string>
#include <raylib.h>

namespace RayLib
{
    class Sound {
        public:
            Sound(const std::string assetName);
            ~Sound();

            void Play();

            void SetVolume(float vol);
            void SetPitch(float pitch);

            ::Sound GetSound();

        protected:
        private:
            ::Sound _sound;
            float _pitch;
            float _volume;
    };
}

#endif /* !SOUND_HPP_ */
