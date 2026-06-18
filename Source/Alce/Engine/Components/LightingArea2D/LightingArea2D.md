# 🧩 Component: LightingArea2D 

> <img src="https://raw.githubusercontent.com/MiguelMJ/Candle/master/doc/logo.svg" style="width: 19px; position: relative; top: 2px"> [Built using the Candle library.](https://github.com/MiguelMJ/Candle)


The ```LightingArea2D``` component defines a 2D lighting area that can be attached to a ```GameObject```. It allows controlling the size, position offset, opacity, and color of the lighting area, and manages a set of light sources within it.

This component is useful for 2D lighting systems, fog effects, localized illumination, and dynamic light areas that follow objects in the scene.

# Behaviour

The ```LightingArea2D``` automatically updates its internal lighting area based on the ```GameObject```’s transform combined with the configured offset and size. When size or offset is changed, the component recomputes the internal lighting area. Opacity and color can be modified at any time, immediately affecting the visual representation of the lighting. Lights added to the area are drawn within the bounds of the component, allowing dynamic and localized illumination effects.

# Constructors

```cpp
LightingArea2D()
```

Creates a new ```LightingArea2D``` instance with default size (100, 100), full opacity, and black color.

# Fields

* ```Color color```: The base color of the lighting area. Default is black.

# Methods

## SetSize
```cpp
void SetSize(Vector2 size)
void SetSize(float width, float height)
```

Sets the size of the lighting area. Changes mark the component for recomputation so the internal lighting area is updated.

## SetOffset
```cpp
void SetOffset(Vector2 offset)
void SetOffset(float x, float y)
```

Sets a relative offset for the lighting area position relative to the GameObject it is attached to.

## GetOffset
```cpp
Vector2 GetOffset()
```

Returns the current offset of the lighting area relative to the GameObject.

## SetOpacity
```cpp
void SetOpacity(float opacity)
```

Sets the opacity of the lighting area. Value must be between 0.0f (fully transparent) and 1.0f (fully opaque). Values outside this range are ignored.

## GetOpacity
```cpp
float GetOpacity()
```

Returns the current opacity of the lighting area.

