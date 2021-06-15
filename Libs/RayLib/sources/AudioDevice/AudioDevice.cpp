/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AudioDevice
*/

#include "AudioDevice.hpp"

namespace RayLib
{
    void AudioDevice::InitAudioDevice(void)
    {
        ::InitAudioDevice();
        if (!::IsAudioDeviceReady()) {
            //throw
        }
    }

    void AudioDevice::CloseAudioDevice(void)
    {
        ::CloseAudioDevice();
    }

    void AudioDevice::SetMasterVolume(float volume)
    {
        ::SetMasterVolume(volume);
    }
}