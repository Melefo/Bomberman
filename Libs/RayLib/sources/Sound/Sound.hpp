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
#include "IAsset.hpp"

namespace RayLib
{
    class Sound : public IAsset {
        public:
            /**
             * @brief Construct a new Sound object
             * 
             * @param assetName 
             */
            Sound(const std::string& assetName);
            /**
             * @brief Construct a new Sound object
             * 
             * @param other 
             */
            Sound(const Sound& other) = default;
            /**
             * @brief Assign a new Sound object
             * 
             * @param assetName 
             */
            Sound& operator=(const Sound& other) = default;

            /**
             * @brief Destroy the Sound object
             * 
             */
            ~Sound();

            /**
             * @brief Play sound
             * 
             */
            void Play();

            /**
             * @brief Set the Volume
             * 
             * @param vol 
             */
            void SetVolume(float vol);
            /**
             * @brief Set the Pitch
             * 
             * @param pitch 
             */
            void SetPitch(float pitch);

            /**
             * @brief Get the Sound
             * 
             * @return ::Sound 
             */
            ::Sound GetSound();

        protected:
        private:
            /**
             * @brief Sound struct
             * 
             */
            ::Sound _sound;
            /**
             * @brief Pitch
             * 
             */
            float _pitch;
            /**
             * @brief Volume
             * 
             */
            float _volume;
    };
}

#endif /* !SOUND_HPP_ */
