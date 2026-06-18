# 🧩 Component: Light2D

> <img src="https://raw.githubusercontent.com/MiguelMJ/Candle/master/doc/logo.svg" style="width: 19px; position: relative; top: 2px"> [Built using the Candle library.](https://github.com/MiguelMJ/Candle)


The ```Light2D``` component represents a 2D light source that can be attached to a GameObject. It supports two types of lights: radial (omnidirectional) and directed (spotlight). The component allows controlling light color, intensity, range, beam angle, and fade behavior.

It is useful for 2D lighting systems, dynamic illumination, and visual effects in games or simulations.

# Behaviour

The ```Light2D``` automatically updates its internal light source based on the ```GameObject```’s transform, including position and rotation. Radial lights use the beam angle property, while directed lights use beam width. Changes to range, intensity, fade, and color are immediately reflected in the visual output. The light follows the ```GameObject``` in real time, providing dynamic and adjustable 2D illumination.


# Light Types
```cpp
enum class Type { Radial, Directed };
```
Defines the type of light:

* ```Radial```: Omnidirectional light, with a beam angle that can be adjusted.

* ```Directed```: Spotlight-like light, with adjustable beam width.

# Fields

* ```Light2D::Type type```: Determines the type of light: Radial (omnidirectional) or Directed (spotlight).

* ```bool fade```: Enables or disables smooth fading of the light over time. Default is true.
range	float	The maximum distance the light reaches.

* ```float beamWidth```: The width of the light beam, only used for Directed lights.
beamAngle	float	The angle of the light beam, only used for Radial lights.

* ```float intensity```: Brightness of the light. Value must be between 0.0 and 1.0.

* ```Color color```: The color of the light. Default is white.

# Constructors

```cpp
Light2D(Type type = Type::Radial)
```

Creates a new ```Light2D``` instance of the specified type. Default is radial. Initializes the internal light with default properties:

* ```range```: 100

* ```beam width```: 100

* ```beam angle```: 360

* ```intensity```: 1

* ```color```: white

# Methods

## SetFade
```cpp
void SetFade(bool fade = true)
```

Enables or disables fading of the light over time.

## IsFading
```cpp
bool IsFading()
```

Returns whether fading is enabled.

## SetRange
```cpp
void SetRange(float range)
```

Sets the effective range of the light.

## GetRange
```cpp
float GetRange()
```

Returns the current range of the light.

## SetBeamWidth
```cpp
void SetBeamWidth(float width)
```

Sets the width of the light beam (for directed lights only).

## GetBeamWidth
```cpp
float GetBeamWidth()
```

Returns the current beam width.

## SetBeamAngle
```cpp
void SetBeamAngle(float angle)
```

Sets the angle of the light beam (for radial lights only).

## GetBeamAngle
```cpp
float GetBeamAngle()
```

Returns the current beam angle.

## SetIntensity
```cpp
void SetIntensity(float intensity)
```

Sets the light intensity. Value must be between 0.0f (off) and 1.0f (full brightness). Values outside this range are ignored.

## GetIntensity
```cpp
float GetIntensity()
```

Returns the current light intensity.
