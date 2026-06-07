# 🧩 Component: Camera

The ```Camera``` component represents a 2D camera that can be attached to a ```GameObject```. It manages the visible area of the scene, allowing control over zoom, viewport, and smoothing of camera movement.

It is useful for following GameObjects, creating dynamic views, and controlling the portion of the scene visible to the player.

# Behaviour

The ```Camera``` automatically updates its view based on the ```GameObject```’s transform. The camera smoothly interpolates its position towards the target using the ```smoothFactor``` property, allowing for smooth following of moving objects. Zoom and viewport settings immediately affect how the scene is rendered. The camera size and bounds are recalculated whenever the window size or viewport changes.

# Fields

* ```float smoothFactor```: Controls how smoothly the camera follows its target. 1.0 is fully smooth, 0.0 is instant.

* ```float zoom```: Zoom level of the camera. Must be greater than 0.

* ```RectShape viewport```: Portion of the window that the camera renders to. Default covers the entire window.

* ```Vector2 size```: Size of the camera view in pixels, calculated from the window size and viewport.

# Constructors

```cpp
Camera()
```

Creates a new ```Camera``` instance. The initial viewport is set to cover the entire window, with no zoom applied.

# Methods

## GetViewport
```cpp
RectShape GetViewport()
```

Returns the current camera viewport as a rectangle relative to the window.

## SetViewport
```cpp
void SetViewport(RectShape viewport)
```

Sets the camera viewport. The viewport defines which portion of the window the camera renders to.

## Zoom
```cpp
void Zoom(float zoom)
```

Sets the camera zoom level. Values must be greater than 0. Zooming in increases the size of objects on screen, while zooming out decreases it.

## GetZoom
```cpp
float GetZoom()
```

Returns the current zoom level of the camera.

## GetBounds
```cpp
RectShape GetBounds()
```

Returns the current world bounds of the camera as a rectangle, based on its position and viewport size.

## GetSize
```cpp
Vector2 GetSize()
```

Returns the size of the camera’s view in pixels, taking the viewport and zoom into account.