#pragma once

#include <SFML/Audio.hpp>
#include "../Core/Core.hpp"

#define Audio alce::AUDIO::Instance()

namespace alce
{
    typedef std::shared_ptr<sf::Sound> SoundPtr;

    class AudioChannel
    {
    public:

        bool Add(String name, String file);

        bool Delete(String name);

        bool Play(String name);

        bool Pause(String name);

        bool Stop(String name);

        bool SetAttenuation(String name, float attenuation);

        bool SetLoop(String name, bool flag = true);

        bool SetPitch(String name, float pitch);

        bool SetRelativeToListener(String name, bool flag = true);

        SoundPtr GetSound(String name);

        bool IsPlaying(String name);

        bool IsPaused(String name);

        bool IsStopped(String name);

        float GetAttenuation(String name);

        bool IsLooping(String name);

        float GetPitch(String name);

        bool IsRelativeToListener(String name);

        float GetVolume();

        bool SetVolume(float volume);

        bool IsPlaying();

        void Clear();

    private:

        friend class AUDIO;

        void ApplyVolume();

        void SetMasterVolume(float masterVolume);

        Dictionary<String, SoundPtr> sounds;
        float volume = 15.0f;
        float masterVolume = 100.0f;
    };

    typedef std::shared_ptr<AudioChannel> AudioChannelPtr;

    class AUDIO
    {
    public:

        static AUDIO& Instance()
	    {
		    static AUDIO ap;
		    return ap;
	    }

        void AddChannel(String name);

        void DeleteChannel(String name);

        AudioChannelPtr GetChannel(String name);

        float GetMasterVolume();

        bool SetMasterVolume(float masterVolume);

    private:

        Dictionary<String, AudioChannelPtr> channels;
        float masterVolume = 100.0f;

        AUDIO() { };
    };
}