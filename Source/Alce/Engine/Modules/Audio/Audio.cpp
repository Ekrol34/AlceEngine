#include "Audio.hpp"

#ifdef __linux__
    #undef Status
#endif

using namespace alce;

#pragma region AudioChannel

bool AudioChannel::Add(String name, String file)
{
    if(sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::Add -> Audio Channel already contain a sound named {}", {name});
        return false;
    }

    auto soundBuffer = Alce.GetSoundBuffer(file);

    if(soundBuffer == nullptr)
    {
        Debug.Warning("AudioChannel::Add -> Error loading file {}", {file});
        return false;
    }

    SoundPtr sound = std::make_shared<sf::Sound>();
    sound->setVolume(volume * (masterVolume / 100.0f));
    sound->setBuffer(*soundBuffer);
    sounds.Set(name, sound);

    return true;
}

bool AudioChannel::Delete(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::Delete -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    sounds.RemoveByKey(name);

    return true;
}

bool AudioChannel::Play(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::Play -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    Debug.Log("AudioChannel::Play -> Playing {}", {name});
    sounds[name]->play();

    return true;
}

bool AudioChannel::Pause(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::Pause -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    sounds[name]->pause();

    return true;
}

bool AudioChannel::Stop(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::Stop -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    sounds[name]->stop();

    return true;
}

bool AudioChannel::SetAttenuation(String name, float attenuation)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::SetAttenuation -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    sounds[name]->setAttenuation(attenuation);

    return true;
}
bool AudioChannel::SetLoop(String name, bool flag)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::SetLoop -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    sounds[name]->setLoop(flag);

    return true;
}

bool AudioChannel::SetPitch(String name, float pitch)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::SetPitch -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    sounds[name]->setPitch(pitch);

    return true;
}

bool AudioChannel::SetRelativeToListener(String name, bool flag)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::SetRelativeToListener -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    sounds[name]->setRelativeToListener(flag);

    return true;
}

SoundPtr AudioChannel::GetSound(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::GetSound -> Audio Channel does not contain sound {}", {name});
        return nullptr;
    }
    else
    {
        return sounds[name];
    }
}

bool AudioChannel::IsPlaying(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::IsPlaying -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getStatus() == sf::SoundSource::Status::Playing;
}

bool AudioChannel::IsPaused(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::IsPaused -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getStatus() == sf::SoundSource::Status::Paused;
}

bool AudioChannel::IsStopped(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::IsStopped -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getStatus() == sf::SoundSource::Status::Stopped;
}

float AudioChannel::GetAttenuation(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::GetAttenuation -> Audio Channel does not contain sound {}", {name});
        return 0.0f;
    }

    return sounds[name]->getAttenuation();
}

bool AudioChannel::IsLooping(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::IsLooping -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getLoop();
}

float AudioChannel::GetPitch(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::GetPitch -> Audio Channel does not contain sound {}", {name});
        return 0.0f;
    }

    return sounds[name]->getPitch();
}

bool AudioChannel::IsRelativeToListener(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("AudioChannel::IsRelativeToListener -> Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->isRelativeToListener();
}
float AudioChannel::GetVolume()
{
    return volume;
}

bool AudioChannel::SetVolume(float volume)
{
    if(volume < 0.0f || volume > 100.0f)
    {
        Debug.Warning("AudioChannel::SetVolume -> Volume must be between 0 and 100");
        return false;
    }

    this->volume = volume;
    ApplyVolume();

    return true;
}

void AudioChannel::ApplyVolume()
{
    for(auto& it: sounds)
    {
        it.second->setVolume(volume * (masterVolume / 100.0f));
    }
}

void AudioChannel::SetMasterVolume(float masterVolume)
{
    if(masterVolume < 0.0f || masterVolume > 100.0f)
    {
        Debug.Warning("AudioChannel::SetMasterVolume -> Volume must be between 0 and 100");
        return;
    }

    this->masterVolume = masterVolume;
    ApplyVolume();
}

bool AudioChannel::IsPlaying()
{
    return sounds.GetValueList().Filter([](SoundPtr sound) {
        return sound->getStatus() == sf::SoundSource::Status::Playing;
    }).Length() != 0;
}

void AudioChannel::Clear()
{
    sounds.Clear();
}

#pragma endregion

#pragma region AudioPipeline

void AUDIO::AddChannel(String name)
{
    if(channels.HasKey(name))
    {
        Debug.Warning("Audio::AddChannel -> Pipeline already contains channel {}", {name});
        return;
    }

    auto channel = std::make_shared<AudioChannel>();
    channel->SetMasterVolume(masterVolume);
    channels.Set(name, channel);
}

float AUDIO::GetMasterVolume()
{
    return masterVolume;
}

bool AUDIO::SetMasterVolume(float masterVolume)
{
    if(masterVolume < 0.0f || masterVolume > 100.0f)
    {
        Debug.Warning("Audio::SetMasterVolume -> Volume must be between 0 and 100");
        return false;
    }

    this->masterVolume = masterVolume;

    for(auto& it: channels)
    {
        it.second->SetMasterVolume(masterVolume);
    }

    return true;
}

void AUDIO::DeleteChannel(String name)
{
    if(!channels.HasKey(name))
    {
        Debug.Warning("Audio::DeleteChannel -> Pipeline does not contain channel {}", {name});
        return;
    }

    channels.RemoveByKey(name);
}

AudioChannelPtr AUDIO::GetChannel(String name)
{
    if(!channels.HasKey(name))
    {
        Debug.Warning("Audio::GetChannel -> Pipeline does not contain channel {}", {name});
        return nullptr;
    }

    return channels[name];
}

void AUDIO::StopAll()
{
    for(auto& it : channels)
    {
        for(auto& s : it.second->sounds)
        {
            s.second->stop();
        }
    }
}

#pragma endregion