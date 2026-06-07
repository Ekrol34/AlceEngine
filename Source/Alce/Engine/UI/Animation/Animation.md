# 📇 UI: Animation

The ```Animation``` component handles 2D spritesheet-based animations for a UI or game element. It supports multiple animations, configurable playback modes, origin adjustments, directional playback, and frame-based timing. Animations can loop, play only once, or remain on the first frame.

This component can used for character animations, interface effects, visual feedback elements, and any UI or gameplay element that requires frame-based motion.

# Behaviour

The ```Animation``` component advances animation frames based on elapsed time (```msPerFrame```) and the selected ```AnimationMode```. During each update cycle, it computes the next frame index, adjusts the sprite’s texture region, and applies the final world transform.

Position, scale, and rotation are derived from the component’s internal ```Transform2```, and padding is additionally applied to offset the final rendered position.

The sprite origin can be configured for different alignment needs (corners, edges, or center).

# Fields

* ```Vector2 size```: Additional scale applied to the sprite on top of the transform scale. Default is (1,1).

* ```String currentAnimation```: Name of the animation currently being played.

* ```AnimationMode currentMode```: Playback mode of the active animation.

* ```bool isPlaying```: Indicates whether an animation is currently running.

* ```OriginMode originMode```: Defines how the sprite origin is aligned during rendering. Default is ```Center```.

* ```int msPerFrame```: Time in milliseconds assigned to each frame. Default is 100ms.

* ```bool paused```: Whether the animation playback is currently paused.

* ```Vector2 padding```: Offset applied to the final rendered position, used to shift the animation without altering the element’s logical transform.

# Animation Modes
```cpp
enum AnimationMode
{
    LoopForwards,
    LoopBackwards,
    OnceForwards,
    OnceBackwards,
    FirstFrameOnly
};
```

* ```LoopForwards```: Plays frames from first to last, restarting when finished.

* ```LoopBackwards```: Plays frames from last to first, restarting when finished.

* ```OnceForwards```: Plays from first to last a single time, then stops.

* ```OnceBackwards```: Plays from last to first a single time, then stops.

* ```FirstFrameOnly```: Displays only the initial frame of the animation.

# Origin Modes
```cpp
enum OriginMode
{
    TopLeft, TopMiddle, TopRight,
    MiddleLeft, Center, MiddleRight,
    BottomLeft, BottomMiddle, BottomRight
};
```

Defines the pivot/origin used for rendering, rotation, and scaling.
This affects where the sprite is anchored relative to its world position.

# Constructors
```cpp
Animation()
```

Initializes a new Animation component. 

# Methods

## AddAnimation
```cpp
void AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight, int numFrames = -1);
```

Creates a new animation by slicing a spritesheet into evenly sized frames.
numFrames allows limiting the total frames used; -1 loads all available tiles.

## DeleteAnimation
```cpp
void DeleteAnimation(String name)
```

Removes an entire animation by name.

## SetOriginMode
```cpp
void SetOriginMode(OriginMode originMode)
```

Configures the origin point of the animation’s sprite for positioning, rotation, and scaling.

## PlayAnimation
```cpp
void PlayAnimation(String name, AnimationMode mode = AnimationMode::LoopForwards)
```

Begins playback of a specific animation in the selected playback mode.
Resets frame counters and timing.

## SetAnimationMode
```cpp
void SetAnimationMode(AnimationMode mode)
```

Changes the playback mode of the currently running animation.

## SetTimePerFrame
```cpp
void SetTimePerFrame(Time time)
void SetTimePerFrame(float ms)
```

Sets the time duration for each frame, either via a Time object or directly in milliseconds.

## Pause
```cpp
void Pause(bool flag = true)
```

Pauses or resumes the current animation.

## IsPlaying
```cpp
bool IsPlaying()
```

Returns whether the animation is actively playing.

## GetCurrentAnimation
```cpp
String GetCurrentAnimation()
```

Retrieves the name of the active animation.