# 📦 Audio

The ```Audio``` module provides a simple system to manage and play sounds within an application. It allows you to organize sounds into channels, control playback, volume, pitch, looping, and other properties, all in a structured and easy-to-use manner.

# Behaviour

The module is built around two main classes: ```Audio``` and ```AudioChannel```.

````Audio``` is a singleton that manages multiple ```AudioChannel``` instances. Each ```AudioChannel``` holds a collection of sounds, represented by ```sf::Sound``` objects from the SFML library, stored in a dictionary keyed by their name. The module handles loading, playing, pausing, stopping, and adjusting sound properties such as attenuation, pitch, volume, and whether the sound is relative to the listener.

# ✳️ AudioChannel

# Fields

* ```float volume```: Current volume of the channel (0–100), independent of the master volume.

* ```float masterVolume```: Master volume factor applied on top of the channel volume (0–100), set internally by the parent ```Audio``` instance.

# Methods

## Add
```cpp
bool Add(String name, String file)
```

Adds a new sound to the channel.

__Parameters:__

* ```name```: Unique identifier for the sound.

* ```file```: Path to the sound file to load.

__Returns:__ True if the sound was added successfully, false if a sound with that name already exists or the file could not be loaded.

## Delete
```cpp
bool Delete(String name)
```

Removes a sound from the channel.

__Parameters:__

* ```name```: Name of the sound to remove.

__Returns:__ True if the sound was removed, false if it does not exist.

## Play
```cpp
bool Play(String name)
```

Plays a sound.

__Parameters:__

* ```name```: Name of the sound to play.

__Returns:__ True if the sound was found and played, false otherwise.

## Pause
```cpp
bool Pause(String name)
```

Pauses a sound.

__Parameters:__

* ```name```: Name of the sound to pause.

__Returns:__ True if the sound was found and paused, false otherwise.

## Stop
```cpp
bool Stop(String name)
```

Stops a sound completely, resetting the sound's position to the start.

__Parameters:__

* ```name```: Name of the sound to stop.

__Returns:__ True if the sound was found and stopped, false otherwise.

## SetAttenuation
```cpp
bool SetAttenuation(String name, float attenuation)
```

Sets how sound diminishes over distance.

__Parameters:__

* ```name```: Name of the sound.

* ```attenuation```: Attenuation factor (SFML standard).

__Returns:__ True if the sound was found and updated, false otherwise.

## SetLoop
```cpp
bool SetLoop(String name, bool flag = true)
```

Enables or disables looping of a sound.

__Parameters:__

* ```name```: Name of the sound.

* ```flag```: True to loop, false to play once.

__Returns:__ True if the sound was found and updated, false otherwise.

## SetPitch
```cpp
bool SetPitch(String name, float pitch)
```

Adjusts the pitch of the sound.

__Parameters:__

* ```name```: Name of the sound.

* ```pitch```: Pitch multiplier (1.0 is normal).

__Returns:__ True if the sound was found and updated, false otherwise.

## SetRelativeToListener
```cpp
bool SetRelativeToListener(String name, bool flag = true)
```

Determines if the sound's position is relative to the listener.

__Parameters:__

* ```name```: Name of the sound.

* ```flag```: True if relative to listener, false otherwise.

__Returns:__ True if the sound was found and updated, false otherwise.

## GetSound
```cpp
SoundPtr GetSound(String name)
```

Retrieves the sound object.

__Parameters:__

* ```name```: Name of the sound.

__Returns:__ Shared pointer to the ```sf::Sound``` object, or ```nullptr``` if not found.

## IsPlaying / IsPaused / IsStopped
```cpp
bool IsPlaying(String name)
bool IsPaused(String name)
bool IsStopped(String name)
```

Checks the status of a sound.

__Parameters:__

* ```name```: Name of the sound.

__Returns:__ True if the sound is in the corresponding state, false otherwise (including if the sound does not exist).

## GetAttenuation / GetPitch / IsLooping / IsRelativeToListener
```cpp
float GetAttenuation(String name)
float GetPitch(String name)
bool IsLooping(String name)
bool IsRelativeToListener(String name)
```

Retrieves sound properties.

__Parameters:__

* ```name```: Name of the sound.

__Returns:__ Corresponding value, or default (```0.0f``` / ```false```) if the sound does not exist.

## GetVolume / SetVolume
```cpp
float GetVolume()
bool SetVolume(float volume)
```

Gets or sets the volume for all sounds in the channel.

__Parameters (```SetVolume```):__

* ```volume```: Desired volume level (0–100).

__Returns (```SetVolume```):__ True if the volume was set successfully, false if out of range.

## IsPlaying
```cpp
bool IsPlaying()
```

Checks if any sound in the channel is currently playing.

__Returns:__ True if at least one sound is playing.

## Clear
```cpp
void Clear()
```

Removes all sounds from the channel.

# ✳️ Audio

# Fields

* ```float masterVolume```: Global volume factor (0–100) applied to every channel managed by the pipeline.

# Methods

## AddChannel
```cpp
void AddChannel(String name)
```

Adds a new audio channel to the system.

__Parameters:__

* ```name```: Unique channel identifier.

## DeleteChannel
```cpp
void DeleteChannel(String name)
```

Removes a channel.

__Parameters:__

* ```name```: Name of the channel to remove.

## GetChannel
```cpp
AudioChannelPtr GetChannel(String name)
```

Retrieves a channel object.

__Parameters:__

* ```name```: Name of the channel.

__Returns:__ Shared pointer to the ```AudioChannel```, or ```nullptr``` if not found.

## GetMasterVolume
```cpp
float GetMasterVolume()
```

Gets the global master volume.

__Returns:__ Current master volume (0–100).

## SetMasterVolume
```cpp
bool SetMasterVolume(float masterVolume)
```

Sets the global master volume, applying it to every existing channel.

__Parameters:__

* ```masterVolume```: Desired master volume level (0–100).

__Returns:__ True if the volume was set successfully, false if out of range.

## StopAll
```cpp
void StopAll()
```

Stops every sound across every channel managed by the pipeline.

