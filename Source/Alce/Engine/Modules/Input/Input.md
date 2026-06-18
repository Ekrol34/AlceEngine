# 📦 Input

The ```Input``` module provides a unified system to handle user input from the keyboard, mouse, and joystick devices. It simplifies checking for pressed, held, or released states of keys and buttons, as well as retrieving mouse position and joystick axes.  

It is built around the singleton ```INPUT``` class, with helper namespaces for ```Keyboard```, ```Mouse```, and ```Joystick```.

# Behaviour

* ```Keyboard``` defines a complete set of key codes.  
* ```Mouse``` defines mouse button codes.  
* ```Joystick``` defines common controller buttons and exposes axis values.  

The ```INPUT``` class manages all states and provides functions to query them.

# Methods

## Keyboard

### IsKeyPressed
```cpp
bool IsKeyPressed(Keyboard::Key key)
```
Checks if a key is currently being pressed.  

__Parameters:__  
* ```key```: Key code.  

__Returns:__ True if the key is pressed.

---

### IsKeyDown
```cpp
bool IsKeyDown(Keyboard::Key key)
```
Checks if a key was just pressed down (triggers once per press).  

__Parameters:__  
* ```key```: Key code.  

__Returns:__ True if the key was pressed in the current frame.

---

## Mouse

### IsMouseButtonPressed
```cpp
bool IsMouseButtonPressed(Mouse::Button button)
```
Checks if a mouse button is currently being pressed.  

__Parameters:__  
* ```button```: Mouse button.  

__Returns:__ True if pressed.

---

### IsMouseButtonDown
```cpp
bool IsMouseButtonDown(Mouse::Button button)
```
Checks if a mouse button was just pressed down (triggers once per press).  

__Parameters:__  
* ```button```: Mouse button.  

__Returns:__ True if pressed in the current frame.

---

### GetMousePosition
```cpp
Vector2 GetMousePosition()
```
Retrieves the mouse position in world coordinates relative to the active window.  

__Returns:__ A ```Vector2``` with the mouse coordinates.

---

### GetMousePositionOnWindow
```cpp
Vector2 GetMousePositionOnWindow()
```
Retrieves the mouse position in window pixel coordinates.  

__Returns:__ A ```Vector2``` with the raw mouse position on the window.

---

## Joystick

### IsButtonPressed
```cpp
bool IsButtonPressed(Joystick::Button button)
```
Checks if a joystick button is currently pressed.  

__Parameters:__  
* ```button```: Joystick button.  

__Returns:__ True if pressed.

---

### IsButtonDown
```cpp
bool IsButtonDown(Joystick::Button button)
```
Checks if a joystick button was just pressed down (triggers once per press).  

__Parameters:__  
* ```button```: Joystick button.  

__Returns:__ True if pressed in the current frame.

---

### GetXYAxis
```cpp
Vector2 GetXYAxis()
```
Gets the X/Y axis values of the joystick.  

__Returns:__ A ```Vector2``` with axis data.

---

### GetZRAxis
```cpp
Vector2 GetZRAxis()
```
Gets the Z/R axis values of the joystick.  

__Returns:__ A ```Vector2``` with axis data.

---

### GetUVAxis
```cpp
Vector2 GetUVAxis()
```
Gets the U/V axis values of the joystick.  

__Returns:__ A ```Vector2``` with axis data.

---

### GetPovAxis
```cpp
Vector2 GetPovAxis()
```
Gets the POV hat axis values of the joystick.  

__Returns:__ A ```Vector2``` with axis data.

---

### GetJoystick
```cpp
Joystick::JoystickPtr GetJoystick(int joystick)
```
Retrieves a joystick object by index.  

__Parameters:__  
* ```joystick```: Joystick ID (0–7).  

__Returns:__ A pointer to the joystick, or nullptr if not connected.

---

### IsJoystickConnected
```cpp
bool IsJoystickConnected(int joystick)
```
Checks if a joystick is connected.  

__Parameters:__  
* ```joystick```: Joystick ID (0–7).  

__Returns:__ True if connected.
