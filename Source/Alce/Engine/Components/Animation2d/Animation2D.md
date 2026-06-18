# 🧩 Component: Animation2D

The ```Animation2D``` component handles 2D sprite animations for a ```GameObject```. It supports multiple animations from spritesheets, various playback modes, and adjustable origin points. Animations can loop, play once, or show only the first frame.

It is useful for character animations or any 2D sprite-based motion.

# Behaviour

The ```Animation2D``` component updates the current frame of the animation based on elapsed time (```TimePerFrame```) and the selected ```AnimationMode```. It automatically updates the sprite’s position, scale, and rotation to match the ```GameObject```’s transform. The origin point of the sprite can be set to any corner or the center to control rotation and positioning behavior. The component also tracks the corners of the animation frame in world coordinates via the cardinals dictionary.

# Fields

* ```Vector2 scale```: Additional scale applied to the sprite on top of the GameObject’s transform. Default is (1,1).

* ```String currentAnimation```: Name of the currently playing animation.

* ```AnimationMode currentMode```: Current playback mode of the animation.

* ```bool isPlaying```: Indicates whether the animation is currently active.

* ```OriginMode originMode```: Origin point of the sprite for positioning and rotation. Default is Center.

* ```int msPerFrame```: Duration of each frame in milliseconds. Default is 100ms.

* ```bool paused```: Whether the animation is currently paused.

* ```bool flipHorizontal```: Whether the sprite is flipped horizontally.

* ```bool flipVertical```: Whether the sprite is flipped vertically.

* ```Vector2 offset```: positional adjustment that shifts an element (or group of elements) by a specified distance from its original location without altering its alignment.

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

* ```LoopForwards```: Plays the animation from first to last frame repeatedly.

* ```LoopBackwards```: Plays the animation from last to first frame repeatedly.

* ```OnceForwards```: Plays the animation from first to last frame once.

* ```OnceBackwards```: Plays the animation from last to first frame once.

* ```FirstFrameOnly```: Displays only the first frame.

# Origin Modes
```cpp
enum OriginMode
{
    TopLeft, TopMiddle, TopRight,
    MiddleLeft, Center, MiddleRight,
    BottomLeft, BottomMiddle, BottomRight
};
```

Specifies the origin of the sprite for rotation, scaling, and positioning.

# Constructors

```cpp
Animation2D()
```

Creates a new ```Animation2D``` instance. Initializes the cardinal points for tracking sprite corners.

# Methods

## AddAnimation
```cpp
bool AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight)
```

Adds an animation from a spritesheet, specifying the number of rows and columns and frame dimensions.

Returns true if the process completed successfully.

## DeleteAnimation
```cpp
bool DeleteAnimation(String name)
```

Removes an animation by its name.

Returns true if the process completed successfully.

## SetOriginMode
```cpp
void SetOriginMode(OriginMode originMode)
```

Sets the origin point of the sprite for positioning and rotation.

## PlayAnimation
```cpp
void PlayAnimation(String name, AnimationMode mode = AnimationMode::LoopForwards)
```

Plays the specified animation with the given playback mode.

## SetAnimationMode
```cpp
void SetAnimationMode(AnimationMode mode)
```

Changes the playback mode of the current animation.

## SetTimePerFrame
```cpp
void SetTimePerFrame(Time timePerFrame)
bool SetTimePerFrame(float ms)
```

Sets the duration of each frame in milliseconds.

Returns true if the process completed successfully.

## Pause
```cpp
void Pause(bool flag = true)
```

Pauses or resumes the animation.

## IsPlaying
```cpp
bool IsPlaying()
```

Returns whether the animation is currently playing.

## GetCardinals
```cpp
Dictionary<String, Vector2Ptr> GetCardinals()
```

Returns the world positions of the four corners of the current frame.

## GetCurrentAnimation
```cpp
String GetCurrentAnimation()
```

Returns the name of the currently active animation.