# 🛠️ Json

The ```Json``` module provides a structured system to parse, manipulate, and serialize JSON data. It serves as a wrapper around the RapidJSON library, making it easier to load JSON from strings or files, access values, modify structures, and save them back to disk in a clean and readable format.

# Behaviour

The module is centered around the Json class. It manages a RapidJSON document internally and exposes simple methods to work with JSON objects, arrays, and primitive values. The class supports both reading and writing operations, including nested JSON handling, lists of strings, and lists of JSON objects.

Additionally, the module offers serialization methods to export JSON content as compact or pretty-printed strings, as well as file saving.

# Methods

## FromString
```cpp
bool FromString(String json)
```

Parses a JSON document from a string.

__Parameters:__

* ```json```: The JSON content as a string.

__Returns:__ True if parsing was successful, false otherwise.

## FromFile
```cpp
bool FromFile(String path)
```

Parses a JSON document from a file.

__Parameters:__

* ```path```: Path to the file.

__Returns:__ True if parsing was successful, false otherwise.

## Get
```cpp
String Get(String key)
```

Retrieves the value of a given key as a string. Automatically converts numeric and boolean values.

__Parameters:__

* ```key```: Name of the key.

__Returns:__ The value as a string.

__Throws:__ Exception if the key is null or the type is unsupported.

## GetJson
```cpp
Json GetJson(String key)
```

Retrieves a nested JSON object.

__Parameters:__

* ```key```: Name of the key.

__Returns:__ A Json object containing the nested data.

## GetStringList
```cpp
List<String> GetStringList(String key)
```

Retrieves a JSON array of strings.

__Parameters:__

* ```key```: Name of the key.

__Returns:__ A list of strings.

__Throws:__ Exception if the key is missing or contains non-string elements.

## GetJsonList
```cpp
List<Json> GetJsonList(String key)
```

Retrieves a JSON array of objects.

__Parameters:__

* ```key```: Name of the key.

__Returns:__ A list of Json objects.

__Throws:__ Exception if the key is missing or contains non-object elements.

## Set
```cpp
void Set(String key, String value)
void Set(String key, Json value)
void Set(String key, List<String> value)
void Set(String key, List<Json> value)
```


Adds or updates a value inside the JSON object.

__Parameters:__

* ```key```: Name of the key.

* ```value```: Value to assign (string, nested Json, list of strings, or list of Json objects).

## Has
```cpp
bool Has(String key)
```

Checks if the JSON object contains a given key.

__Parameters:__

* ```key```: Name of the key.

__Returns:__ True if the key exists, false otherwise.

## Delete
```cpp
void Delete(String key)
```

Removes a key-value pair from the JSON object.

__Parameters:__

* ```key```: Name of the key.

__Throws:__ Exception if the key is not found.

## Clear
```cpp
void Clear()
```

Removes all members from the JSON object.

## IsValid
```cpp
bool IsValid()
```

Checks if the JSON document is valid.

__Returns:__ True if no parse errors were detected.

## ToString
```cpp
String ToString()
```

Serializes the JSON document into a compact string.

__Returns:__ The JSON as a single-line string.

## ToPrettyString
```cpp
String ToPrettyString()
```

Serializes the JSON document into a formatted string with indentation.

__Returns:__ The JSON as a human-readable string.

## SaveAsFile
```cpp
File SaveAsFile(String name, String path = "./")
```

Saves the JSON document to a file in pretty-printed format.

__Parameters:__

* ```name```: File name (without extension).

* ```path```: Destination directory (defaults to current).

__Returns:__ A File object representing the saved file.