# 🧩 Component: SpriteRenderer

The ```SpriteRenderer``` component is responsible for drawing 2D images (sprites) in the scene. It serves as the link between a GameObject's transform (position, rotation, scale) and the visual representation displayed on screen.

A SpriteRenderer manages one or more textures, allows dynamically switching between them, and controls rendering details such as smoothing. It is typically used for any game entity that requires a visual appearance.

All transformations applied to the ```GameObject``` (movement, scaling, rotation) are automatically propagated to the sprite, ensuring that the rendered image always matches the logical state of the object in the game world.

# Constructors

```cpp
SpriteRenderer()
```
Creates a new ```SpriteRenderer``` instance. Initializes the internal sprite and allocates cardinal point references (top-left, top-right, bottom-left, bottom-right).

# Fields

* ```Vector2 originOffset```: Offset applied to the sprite’s origin, relative to its center.

# Methods

## AddTexture
```cpp
bool AddTexture(String file, String name)
```

Loads a texture from disk and registers it with a unique name.

Parameters:

* ```file```: Path to the texture file.

* ```name```: Identifier to reference the texture later.

> __Notes__: _If the name already exists, the method logs a warning and ignores the request._

Returns true if the process completed successfully.

## SetTexture
```cpp
bool SetTexture(String name)
```
Sets the current sprite texture by name.

Parameters:

* ```name```: The identifier of a previously added texture.

>__Notes__: _Logs a warning if the texture name does not exist._

Returns true if the process completed successfully.

## SetAlpha
```cpp
bool SetAlpha(int alpha)
```
Changes the transparency of the sprite by setting its alpha channel.

Returns true if the process completed successfully.

## GetAlpha
```cpp
int GetAlpha()
```
Returns the current alpha value (transparency) of the sprite.

## RemoveTexture
```cpp
bool RemoveTexture(String name)
```

Removes a texture from the component by its name.

Parameters:

* ```name```: The identifier of the texture to remove.

> __Notes__: _If the texture does not exist, a warning is logged._

Returns true if the process completed successfully.

## SetTextureSmooth
```cpp
bool SetTextureSmooth(String name, bool flag = true)
```

Enables or disables smoothing for a specific texture.

Parameters:

* ```name```: The identifier of the texture to modify.

* ```flag```: true to enable smoothing, false to disable.

> __Notes__: _Logs a warning if the texture does not exist._

Returns true if the process completed successfully.

## GetLocalCenter
```cpp
Vector2 GetLocalCenter()
```

Returns the local center of the sprite (relative to its own coordinate space).

## GetGlobalCenter
```cpp
Vector2 GetGlobalCenter()
```

Returns the global center of the sprite (taking into account the world transform).

## GetCardinals
```cpp
Dictionary<String, Vector2Ptr> GetCardinals()
```

Returns a dictionary with references to the sprite’s four cardinal points:

* ```top-left```

* ```top-right```

* ```bottom-left```

* ```bottom-right```

These points are updated automatically each frame based on the sprite’s transform and size.