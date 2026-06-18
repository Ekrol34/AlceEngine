# 📦 Chrono

The ```Chrono``` module provides a utility for handling and measuring time within an application. It allows you to represent time spans, perform arithmetic operations, convert between different time units, and compare durations. It also offers a singleton class that maintains a global ```deltaTime``` reference.

# Behaviour

The module revolves around the ```Time``` class, which stores a duration internally in milliseconds (ms). It supports construction from raw milliseconds or from a dictionary of time measures (hours, minutes, seconds, milliseconds). It includes arithmetic operators for adding and subtracting time, as well as comparison operators.

The ```Chrono``` class acts as a singleton container that holds a ```deltaTime``` property, typically used to represent frame-to-frame time differences in game loops.

> ### ⚠️ Important Notes:

> Negative values for any measure (hours, minutes, seconds, milliseconds) are not allowed; passing them will throw an exception.

> Subtraction never produces negative results — if the result would be less than zero, it is clamped to zero.

> All comparisons and arithmetic are based on the internal millisecond representation.

# Constructors
```cpp
Time();
Time(float miliseconds);
Time(Dictionary<String, float> measures);
```

Creates a new Time object.

__Parameters:__

* ```miliseconds```: Initializes with a given number of milliseconds (must be non-negative).

* ```measures```: Initializes using a dictionary with possible keys "hours", "minutes", "seconds", "miliseconds".


# Fields

* ```Time deltaTime```: Represents the global frame-to-frame delta time. Typically updated each frame in a game loop.


# Methods

## Add
```cpp
Time& Add(Dictionary<String, float> measures);
```

Adds a set of time measures to the current instance.

__Parameters:__

* ```measures```: Dictionary with keys for "hours", "minutes", "seconds", "miliseconds".

## AddHours / AddMinutes / AddSeconds / AddMiliseconds
```cpp
Time& AddHours(float hours);
Time& AddMinutes(float minutes);
Time& AddSeconds(float seconds);
Time& AddMiliseconds(float miliseconds);
```

Adds a specific unit of time to the current instance.

__Parameters:__

* hours, minutes, seconds, miliseconds: Value to add (must be non-negative).

## ToHours / ToMinutes / ToSeconds / ToMiliseconds
```cpp
float ToHours();
float ToMinutes();
float ToSeconds();
float ToMiliseconds();
```

Converts the stored time to the specified unit.

__Returns:__ Time value expressed in the chosen unit.

## ToString
```cpp
String ToString(String format = "{h}{m}{s}{ms}");
```

Formats the stored time into a human-readable string according to the specified pattern.

The format string may include the following placeholders:

* ```{h}``` → Hours component

* ```{m}``` → Minutes component

* ```{s}``` → Seconds component

* ```{ms}``` → Milliseconds component

Any placeholder not included will be omitted from the output. Components are separated by ```:``` automatically, except if the last placeholder would produce a trailing colon (which is removed).

__Parameters:__

* ```format``` (optional): A string specifying which time units to include. Default is ```"{h}{m}{s}{ms}"```.

__Returns:__ A string representing the formatted time.

## Reset
```cpp
Time& Reset();
```

Resets the stored time to zero.


