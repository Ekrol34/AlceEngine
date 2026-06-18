# 🧩 Component: LightMesh2D

> <img src="https://raw.githubusercontent.com/MiguelMJ/Candle/master/doc/logo.svg" style="width: 19px; position: relative; top: 2px"> [Built using the Candle library.](https://github.com/MiguelMJ/Candle)

The ```LightMesh2D``` component defines a 2D light mesh that can be attached to a ```GameObject```. It allows representing light areas using different shapes (rectangle, circle, or polygon), controlling their offset relative to the object, and managing the mesh configuration.

It is useful for 2D lighting systems, light masks, visual collision outlines, or any effect that requires a customizable light shape.

# Behaviour

The ```LightMesh2D``` automatically updates its shape’s position based on the ```GameObject```'s transform combined with the configured offset. This ensures that the light mesh moves consistently with the object while allowing independent adjustments. Changing the shape or offset immediately affects how the light is applied.

# Constructors

```cpp
LightMesh2D(ShapePtr shape)
```

Creates a new LightMesh2D with the provided shape. The shape can be a rectangle, circle, or polygon.

# Methods
## GetShape
```cpp
Shape GetShape()
```

Returns the current shape associated with the LightMesh2D.

## SetShape
```cpp
bool SetShape(ShapePtr shape)
```

Assigns a new shape to the LightMesh2D. If the shape is null, no changes are applied.

Returns true if the process completed successfully.

## SetOffset
```cpp
void SetOffset(Vector2 offset)
void SetOffset(float x, float y)
```

Sets a relative offset for the light's position with respect to the GameObject it is attached to.

## GetOffset
```cpp
Vector2 GetOffset()
```

Returns the current offset of the light relative to the GameObject.

