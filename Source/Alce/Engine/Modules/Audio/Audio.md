# 📦 Audio

The ```Audio``` module provides a simple system to manage and play sounds within an application. It allows you to organize sounds into channels, control playback, volume, pitch, looping, and other properties, all in a structured and easy-to-use manner.

# Behaviour

The module is built around two main classes: ```Audio``` and ```AudioChannel```. 

```Audio``` is a singleton that manages multiple ```AudioChannel``` instances. Each ```AudioChannel``` holds a collection of sounds, represented by ```sf::Sound``` objects from the SFML library, stored in a dictionary keyed by their name. The module handles loading, playing, pausing, stopping, and adjusting sound properties such as attenuation, pitch, volume, and whether the sound is relative to the listener.

# Methods
## Add
```cpp
void Add(String name, String file)
```

Adds a new sound to the channel.

__Fields:__

* ```name```: Unique identifier for the sound.

* ```file```: Path to the sound file to load.

## Delete
```cpp
void Delete(String name)
```

Removes a sound from the channel.

__Parameters:__

* ```name```: Name of the sound to remove.

## Play
```cpp
void Play(String name)
```

Plays a sound.

__Parameters:__

* ```name```: Name of the sound to play.

## Pause
```cpp
void Pause(String name)
```

Pauses a sound.

__Parameters:__

* ```name```: Name of the sound to pause.
 
## Stop
```cpp
void Stop(String name)
```

Stops a sound completely, reseting the sound’s position to the start.

__Parameters:__

* ```name```: Name of the sound to stop.
 
## SetAttenuation
```cpp
void SetAttenuation(String name, float attenuation)
```

Sets how sound diminishes over distance.

__Parameters:__

* ```name```: Name of the sound.

* ```attenuation```: Attenuation factor (SFML standard).
 
## SetLoop
```cpp
void SetLoop(String name, bool flag = true)
```

Enables or disables looping of a sound.

__Parameters:__

* ```name```: Name of the sound.

* ```flag```: True to loop, false to play once.
 
## SetPitch
```cpp
void SetPitch(String name, float pitch)
```

Adjusts the pitch of the sound.

__Parameters:__

* ```name```: Name of the sound.

* ```pitch```: Pitch multiplier (1.0 is normal).
 
## SetRelativeToListener
```cpp
void SetRelativeToListener(String name, bool flag = true)
```

Determines if the sound’s position is relative to the listener.

__Parameters:__

* ```name```: Name of the sound.

* ```flag```: True if relative to listener, false otherwise.
 
## GetSound
```cpp
SoundPtr GetSound(String name)
```

Retrieves the sound object.

__Parameters:__

* ```name```: Name of the sound.

__ __Returns:____ Shared pointer to the sf::Sound object or nullptr if not found.
 
## IsPlaying / IsPaused / IsStopped
```cpp
bool IsPlaying(String name)
bool IsPaused(String name)
bool IsStopped(String name)
```

Checks the status of a sound.

__Parameters:__

* ```name```: Name of the sound.

 __Returns:__ True if the sound is in the corresponding state.

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

 __Returns:__ Corresponding value or default if the sound does not exist.

## GetVolume / SetVolume
```cpp
float GetVolume()
void SetVolume(float volume)
```

Gets or sets the volume for all sounds in the channel.

Parameters (```SetVolume```):

* ``volume```: Desired volume level (≥ 0).

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

__Returns:__ Shared pointer to the AudioChannel or nullptr if not found.