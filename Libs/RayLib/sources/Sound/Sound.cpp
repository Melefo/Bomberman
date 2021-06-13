/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Sound
*/

#include "Sound.hpp"

namespace RayLib
{
    Sound::Sound(const std::string assetName) :
    _sound(::LoadSound(assetName.c_str())), _pitch(1.0f), _volume(1.0f)
    {
    }

    void Sound::Play()
    {
        ::PlaySound(_sound);
    }

    void Sound::SetVolume(float vol)
    {
        if (vol > 1.0f)
            vol = 1.0f;
        _volume = vol;
        ::SetSoundVolume(_sound, _volume);
    }

    void Sound::SetPitch(float pitch)
    {
        _pitch = pitch;
        ::SetSoundPitch(_sound, _pitch);
    }

    ::Sound Sound::GetSound()
    {
        return (_sound);
    }

    Sound::~Sound()
    {
        ::UnloadSound(_sound);
    }
}