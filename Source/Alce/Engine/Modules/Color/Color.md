# 📦 Color

The ```Color``` module provides a simple system to manage colors within the application. It is based on the sf::Color class from the SFML library, but adds utilities to create, convert, blend, and serialize colors in different formats (RGB, RGBA, Hexadecimal, Strings).

It also includes the namespace ```Colors``` with predefined commonly used colors.

# Behaviour

The module revolves around the ```Color``` class, which acts as a wrapper around ```sf::Color```.

It allows you to construct a color from numeric values, hexadecimal codes, or strings; modify its channels; retrieve its components; blend it with other colors; and convert it to SFML or string format.

Additionally, the Colors namespace provides a set of predefined constant colors (red, green, blue, etc.) ready to use.

# Constructors
```cpp
Color()
Color(sf::Color sfColor)
Color(int red, int green, int blue)
Color(int red, int green, int blue, int alpha)
Color(unsigned int hexValue)
Color(String str)
Color(const char* cstr)
```


# Fields:

* ```red, green, blue```: Integer values (0–255).

* ```alpha```: Optional transparency channel (default 255).

* ```hexValue```: Hexadecimal value (0xRRGGBB).

* ```str```: String in hexadecimal format (e.g. ```"#FF0000"```) or CSV format (e.g. ```"255,0,0,128"```).

* ```sfColor```: SFML color instance.

# Methods

## FromString
```cpp
void FromString(String str)
```

Parses a color from a string in either hex (#RRGGBB) or CSV format (R,G,B[,A]).

__Parameters:__

* ```str```: Input string.

## SetRGB
```cpp
void SetRGB(int red, int green, int blue)
```

Sets the RGB channels of the color.

## SetRGBA
```cpp
void SetRGBA(int red, int green, int blue, int alpha)
```

Sets all RGBA channels of the color.

## SetHex
```cpp
bool SetHex(unsigned int hexValue)
```

Sets the color channels from a hexadecimal value.

__Returns:__ True if successful, false if parsing failed.

## SetAlpha
```cpp
void SetAlpha(int alpha)
```

Sets the alpha (transparency) channel.

## GetRed / GetGreen / GetBlue / GetAlpha
```cpp
int GetRed()
int GetGreen()
int GetBlue()
int GetAlpha()
```

Retrieve the individual color channels.

## Blend
```cpp
Color Blend(Color color)
```

Blends the current color with another one by averaging their channels.

__Parameters:__

* ```color```: The color to blend with.

__Returns:__ New blended color.

## ToSFMLColor
```cpp
sf::Color ToSFMLColor()
```

Converts the object back to sf::Color.

## ToString
```cpp
String ToString()
```

Returns a hexadecimal string representation of the color (e.g. ```"#FFA07A"```).

## Predefined Colors

The Colors namespace provides a set of predefined constants:

```cpp
namespace Colors
{
    const Color Red = Color(255, 0, 0);
    const Color Green = Color(0, 255, 0);
    const Color Blue = Color(0, 0, 255);
    const Color White = Color(255, 255, 255);
    const Color Black = Color(0, 0, 0);
    const Color Yellow = Color(255, 255, 0);
    const Color Cyan = Color(0, 255, 255);
    const Color Magenta = Color(255, 0, 255);
    const Color Orange = Color(255, 165, 0);
    const Color Purple = Color(128, 0, 128);
    const Color Pink = Color(255, 192, 203);
    const Color Transparent = Color(0, 0, 0, 0);

};
```