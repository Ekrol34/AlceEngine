# 📇 UI: Image

The ```Image``` UI element displays a 2D texture inside the UI system.
It allows loading multiple textures, switching between them dynamically, enabling or disabling smoothing, and applying transform-based positioning, scaling, and rotation inherited from UIElement.

This component is suitable for icons, decorative UI images, backgrounds, thumbnails, and any static or dynamic visual asset rendered as part of the user interface.

# Behaviour

The ```Image``` UI element stores a dictionary of available textures and renders the active one using an internal sf::Sprite. Each update synchronizes the sprite's position, scale, and rotation with the ```UIElement``` transform. Textures can be swapped at runtime by name, and smoothing can be individually configured per texture.

Because the component inherits all transform-related fields from ```UIElement```, it integrates seamlessly into layout systems and other UI controls.

# Fields

* ```Dictionary<String, TexturePtr> textures```: Internal storage for all textures associated with this image element.

* ```std::unique_ptr<sf::Sprite> sprite```: The sprite responsible for rendering the currently selected texture.

* ```String currentTexture```: Name of the texture currently applied to the sprite.

* ```Vector2 originOffset```: Optional position offset added to the sprite’s origin. Useful for fine-tuning alignment.

* ```float borderWidth```: Thickness of the box outline (0 = no outline).

* ```Color borderColor```: Color of the box outline.

* ```Color backgroundColor```: Fill color of the box.

* ```float borderRadius```: Corner roundness; if > 0 the box is drawn with rounded corners.

# Constructors
```cpp
Image()
```

Creates a new Image instance and initializes the internal sprite.

# Methods

## AddTexture
```cpp
void AddTexture(String file, String name)
```

Loads a texture from the specified file path and stores it under the provided name.

## SetTexture
```cpp
void SetTexture(String name)
```

Assigns the texture identified by name to the sprite.

## RemoveTexture
```cpp
void RemoveTexture(String name)
```

Removes the texture with the given name from the internal dictionary.

## SetTextureSmooth
```cpp
void SetTextureSmooth(String name, bool flag)
```

Enables or disables smoothing for the texture identified by name.
