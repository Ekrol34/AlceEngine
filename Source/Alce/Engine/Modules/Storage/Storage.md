# 📦 Storage

The ```Storage``` module provides a persistent key-value storage system built on top of the ```Json``` module. It allows storing and retrieving JSON objects, strings, and lists across sessions by saving data into files located in the ```./Storage/``` directory.  

The system automatically manages file rotation with size limits, keeping an index file (```index.json```) to map keys to file identifiers. This ensures efficient storage even for large datasets.

# Behaviour

The module revolves around the singleton class ```STORAGE```.  
It provides methods to insert, update, retrieve, and delete data. Internally, data is distributed across multiple JSON files, with an index file maintaining the mapping between keys and files.  

The module supports strings, JSON objects, lists of strings, and lists of JSON objects.

# Methods

## SetJson
```cpp
void SetJson(String name, Json data)
```
Stores a JSON object under the given key.  

__Parameters:__  
* ```name```: Key name.  
* ```data```: JSON object to store.



## SetString
```cpp
void SetString(String name, String data)
```
Stores a string under the given key.  

__Parameters:__  
* ```name```: Key name.  
* ```data```: String value to store.



## SetStringList
```cpp
void SetStringList(String name, List<String> data)
```
Stores a list of strings under the given key.  

__Parameters:__  
* ```name```: Key name.  
* ```data```: List of strings to store.



## SetJsonList
```cpp
void SetJsonList(String name, List<Json> data)
```
Stores a list of JSON objects under the given key.  

__Parameters:__  
* ```name```: Key name.  
* ```data```: List of JSON objects to store.



## GetJson
```cpp
Json GetJson(String name)
```
Retrieves a JSON object by key.  

__Parameters:__  
* ```name```: Key name.  

__Returns:__ The stored JSON object.



## GetString
```cpp
String GetString(String name)
```
Retrieves a string by key.  

__Parameters:__  
* ```name```: Key name.  

__Returns:__ The stored string.



## GetStringList
```cpp
List<String> GetStringList(String name)
```
Retrieves a list of strings by key.  

__Parameters:__  
* ```name```: Key name.  

__Returns:__ The stored list of strings.



## GetJsonList
```cpp
List<Json> GetJsonList(String name)
```
Retrieves a list of JSON objects by key.  

__Parameters:__  
* ```name```: Key name.  

__Returns:__ The stored list of JSON objects.



## Delete
```cpp
void Delete(String name)
```
Removes a value from storage.  

__Parameters:__  
* ```name```: Key name.  

__Notes:__ If the key does not exist, no action is taken.



## Clear
```cpp
void Clear()
```
Removes all stored data, deletes all associated JSON files, and resets the index file.
