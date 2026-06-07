# 📇 UI: Text

The ```Text``` UI element provides styled text rendering for user interface screens.
It supports rich text formatting (bold, italic, underline, strike-through, and inline colors), optional background boxes with borders and rounded corners, fixed or auto-sized text boxes, word wrapping, and horizontal alignment inside its bounding box.

# Behaviour

Text parses its string for inline tags (```<bold>```, ```<italic>```, ```<underlined>```, ```<strikeThrough>```, ```<color>```) and applies the corresponding ```sf::Text::Style``` and ```sf::Color```.

It automatically computes the text bounds, adds padding, and draws an optional background box or texture.
If ```borderRadius``` > 0, the background is rendered as a rounded rectangle; otherwise a standard rectangle is drawn.
When a fixed box is enabled, the text is word-wrapped and aligned (left, center, or right) inside the specified box.

By default, Text ignores transform scaling (font size controls text size) and places the top-left corner of the box at transform.position.

> ## ⚠️ Important notes

> Text position is always the top-left corner of the text box.

> The background box size is automatically calculated unless a fixed box is enabled.

> Malformed tags (e.g. unclosed <bold>) may lead to incorrect styling.

# Fields

* ```String text```: UTF-8 encoded text to display. Supports inline formatting tags.

* ```Color color```: Default text color (before ```<color>``` tags).

* ```int fontSize```: Character size in pixels.

* ```String font```: Path or key of the font resource.

* ```float borderWidth```: Thickness of the box outline (0 = no outline).

* ```Color borderColor```: Color of the box outline.

* ```Color backgroundColor```: Fill color of the box.

* ```float borderRadius```: Corner roundness; if > 0 the box is drawn with rounded corners.

* ```bool wordWrap```: Enables word wrapping when a fixed box is active. Defaults to true.

* ```String horizontalAlign```: Horizontal alignment of text inside a fixed box ("left", "center", "right").

# Constructors
```cpp
Text()
```

Creates a new Text UI element. Font and text must be set before rendering.

Multiple overloads allow constructing from std::string, std::wstring, numbers, or booleans.

# Methods

## SetNewText
```cpp
void SetNewText(String str)
```

Replaces the current text with str.

## AddText
```cpp
void AddText(String str)
```

Appends str to the existing text.

## SetBackgroundTexture
```cpp
void SetBackgroundTexture(String path, bool keepAspect = true)
```

Sets a background texture from a file (relative to ./Assets/).
keepAspect controls whether the texture preserves its original aspect ratio.

## RemoveBackgroundTexture
```cpp
void RemoveBackgroundTexture()
```

Removes any assigned background texture.

## EnableFixedBox
```cpp
void EnableFixedBox(Vector2 boxSize)
```

Activates a fixed-size text box and sets its size.

## DisableFixedBox
```cpp
void DisableFixedBox()
```

Disables fixed-size mode and reverts to auto-sizing.

## IsUsingFixedBox
```cpp
bool IsUsingFixedBox()
```

Returns true if the text is currently constrained to a fixed box.

# Example Usage
```cpp
TextPtr uiText = std::make_shared<Text>();
uiText->font = "fonts/Basic-Regular/Basic-Regular.ttf";
uiText->fontSize = 20;
uiText->color = Colors::White;
uiText->padding = Vector2(8, 4);
uiText->backgroundColor = Colors::Black;
uiText->borderWidth = 2;
uiText->borderColor = Colors::Yellow;

// Rich text styling
*uiText += "Welcome <bold>User</bold>! <color='red'>Error</color> message.";

// Fixed box with center alignment
uiText->EnableFixedBox(Vector2(300, 100));
uiText->horizontalAlign = "center";
```


This example draws:

* A black rectangle with yellow border.

* The word User in bold.

* The word Error in red.

* Text centered and word-wrapped inside a 300×100 box at the UI element’s transform.position.