/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AudioDevice
*/

#ifndef AUDIODEVICE_HPP_
#define AUDIODEVICE_HPP_

#include <raylib.h>

namespace RayLib
{
    class AudioDevice {
        public:
            AudioDevice() = default;
            ~AudioDevice() = default;

        static void InitAudioDevice(void);
        static void CloseAudioDevice(void);
        static void SetMasterVolume(float volume);

        protected:
        private:
    };
}

#endif /* !AUDIODEVICE_HPP_ */
