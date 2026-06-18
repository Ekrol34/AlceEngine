# 🧩 Component: TextRenderer
The ```TextRenderer``` component provides styled text rendering capabilities for a GameObject.
It supports rich text formatting (bold, italic, underline, strike-through, and inline colors), optional background boxes with borders and rounded corners, fixed or auto-sized text boxes, word wrapping, and automatic alignment inside its bounding box.

Unlike raw SFML ```sf::Text```, ```TextRenderer``` integrates directly with the engine’s component system and synchronizes its position with the owning ```GameObject```’s Transform.

# Behaviour

The ```TextRenderer``` component handles the full pipeline of displaying text inside the game window:

It parses the assigned string for inline tags (```<bold>```, ```<italic>```, ```<underlined>```, ```<strikeThrough>```, ```<color>```), applying the appropriate ```sf::Text::Style``` and ```sf::Color```.

It automatically calculates the text bounds, adds padding, and computes the final size of the background box.

If ```borderRadius > 0```, the background is drawn as a rounded rectangle; otherwise, a standard rectangle with optional border thickness is drawn.

The text is then centered inside this box, positioned relative to the ```GameObject```’s transform.

By default, TextRenderer does not apply scaling from the Transform, since text size is controlled by the font size.

### ⚠️ Important notes:

> TextRenderer ignores transform scaling.

> The background box always uses the calculated size (text width + padding). If you want transparent backgrounds, set backgroundColor to transparent.

> If tags are malformed (e.g., unclosed ```<bold>```), text may render partially without the intended style.

# Fields

* ```String text```: The UTF-8 encoded text to display. Supports inline formatting tags.

* ```Color color```: Default text color (before applying <color> tags).

* ```int fontSize```: Character size in pixels.

* ```String font```: The font resource key used to retrieve the SFML font from the engine.

* ```Vector2 padding```: Horizontal and vertical padding around the text inside the background box.

* ```float borderWidth```: Thickness of the box outline (0 = no outline).

* ```Color borderColor```: Outline color of the box.

* ```Color backgroundColor```: Fill color of the box.

* ```float borderRadius```: Corner roundness. If > 0, the box is drawn with rounded corners.

* ```Vector2 size```: Final computed size of the text box (auto-updated each frame).

* ```Vector2 offset```: positional adjustment that shifts an element (or group of elements) by a specified distance from its original location without altering its alignment.

* ```bool wordWrap```: Enables wrapping text by words within a fixed-size box. Defaults to true.

## Constructors

```cpp
TextRenderer()
```

Creates a new ```TextRenderer``` component. Font and text must be assigned before rendering.


# Methods

## SetNewText
```cpp
void SetNewText(String str)
```

Replaces the current text with the given string.

## AddText
```cpp
void AddText(String str)
```
Appends the given string to the existing text.

## SetBackgroundTexture
```cpp
void SetBackgroundTexture(String path, bool keepAspect = false)
```

Sets a background texture from a file path (relative to ./Assets/).
keepAspect determines whether the texture preserves its original aspect ratio.

## RemoveBackgroundTexture
```cpp
void RemoveBackgroundTexture()
```

Removes any assigned background texture.

## EnableFixedBox
```cpp
void EnableFixedBox(Vector2 boxSize)
```

Activates a fixed-size box and sets its size.

## DisableFixedBox
```cpp
void DisableFixedBox()
```

Disables fixed-size mode, returning to auto-size mode.

## IsUsingFixedBox
```cpp
bool IsUsingFixedBox()
```

Returns whether the text box is currently fixed-size.## 

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

## Example Usage
```cpp
TextRendererPtr text = std::make_shared<TextRenderer>();
text->font = "fonts/Merriweather/Merriweather-Black.ttf";
text->fontSize = 24;
text->color = Colors::White;
text->padding = Vector2(8, 4);
text->backgroundColor = Colors::Black;
text->borderWidth = 2;
text->borderColor = Colors::Yellow;

// Supports inline styling
*text +="Hello <bold>World</bold>! <color='red'>Red text</color>";
```


This will render:

* A black box with yellow outline.

* The word "World" in bold.

* The words "Red text" in red.