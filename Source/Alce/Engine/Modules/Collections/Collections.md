# 🛠️ Collections

The ```Collections``` module provides generic container classes designed to manage dynamic collections of data efficiently. It offers custom implementations of lists, pairs, and maps that provide intuitive methods for insertion, removal, iteration, and element access. These structures aim to simplify working with collections while ensuring type safety and clean syntax.

## Behaviour

The module introduces three main template-based classes: ```List<T>```, ```Pair<K, V>```, and ```Map<K, V>```.
Each class encapsulates logic commonly found in standard containers, but with custom handling for exceptions, iterator support, functional operations, and simplified access.

The ```List<T>``` class wraps around a dynamic container for storing ordered elements. It supports iteration, filtering, sorting, insertion, removal, and functional operations such as ```ForEach``` and ```Any```.

The ```Pair<K, V>``` class holds a lightweight key–value pair, typically used internally in the ```Map<K, V>``` class.

The ```Map<K, V>``` class maintains a list of ```Pair<K, V>``` objects, providing key-based access, addition, deletion, search, and iteration.

---
# 🧾 List<T>

A dynamic array structure that stores a sequence of elements of ```type T```, offering access, manipulation, and utility methods.

# Constructors
```cpp
List()
List(std::initializer_list<T> values)
```


Creates an empty list or initializes it with given elements.

# Methods
## Add
```cpp
List<T>& Add(const T& value)
```

Appends an element to the end of the list.
Returns a reference to the list.

## AddFirst
```cpp
List<T>& AddFirst(const T& value)
```

Inserts an element at the beginning of the list.

## SetFirst
```cpp
List<T>& SetFirst(size_t index)
```

Moves the element at the specified index to the beginning of the list.
Throws if index is out of bounds.

## PopFirst
```cpp
List<T>& PopFirst()
```

Removes the first element from the list.
Throws if the list is empty.

## PopLast
```cpp
List<T>& PopLast()
```

Removes the last element from the list.
Throws if the list is empty.

## First
```cpp
T& First()
```

Returns a reference to the first element.
Throws if the list is empty.

## Last
```cpp
T& Last()
```

Returns a reference to the last element.
Throws if the list is empty.

## Get
```cpp
T& Get(size_t index)
```

Returns a reference to the element at the specified index.
Throws if the index is out of bounds.

## Set
```cpp
List<T>& Set(size_t index, const T& value)
```

Replaces the element at the given index with the provided value.
Throws if index is out of bounds.

## Length
```cpp
size_t Length() const
```

Returns the number of elements in the list.

## Empty
```cpp
bool Empty() const
```

Returns true if the list has no elements.

## Clear
```cpp
List<T>& Clear()
```

Removes all elements from the list.

## Contains
```cpp
bool Contains(const T& value) const
```

Checks whether an element exists in the list.

## FindIndex
```cpp
int FindIndex(const T& value) const
```

Returns the index of the first occurrence of the element.
Returns -1 if not found.

## FindAndRemove
```cpp
List<T>& FindAndRemove(const T& value)
```

Finds and removes the first occurrence of the given element.
Returns the list.

## RemoveIndex
```cpp
List<T>& RemoveIndex(size_t index)
```

Removes the element at the specified index.
Throws if the index is out of bounds.

## RemoveIf
```cpp
template<typename Predicate>
List<T>& RemoveIf(Predicate condition)
```

Removes all elements that satisfy the given condition.

## Filter
```cpp
template<typename Predicate>
List<T> Filter(Predicate condition) const
```

Returns a new list containing elements that satisfy the given condition.

## Sort
```cpp
List<T>& Sort(CompareFunction compare)
```

Sorts elements using a custom comparator function.

## Merge
```cpp
List<T>& Merge(List<T> other)
```

Appends elements from another list that are not already present.

## ForEach
```cpp
template<typename Func>
List<T>& ForEach(Func action)
```

Applies a function to each element of the list.

## ToStdVector
```cpp
std::vector<T> ToStdVector() const
```

Returns a copy of the internal std::vector.

## ToStdVectorPtr
```cpp
std::vector<T>* ToStdVectorPtr()
```

Returns a pointer to the internal std::vector.

---

# 🧾 Pair<F, S>

A lightweight structure that stores a pair of values, typically representing a key-value relationship or any two associated elements.

## Constructors
```cpp
Pair()
Pair(F first, S second)
```

Creates an empty pair or initializes it with the given first and second values.

## Fields
* ```F first```: The first element of the pair.
* ```S second```: The second element of the pair.

---

# 🧾 Dictionary<K, V>

A key-value collection that maps unique keys of type ```K``` to corresponding values of type ```V```.
Implemented internally using a ```List<Pair<K, V>>```.

## Constructors
```cpp
Dictionary()
Dictionary(std::initializer_list<std::pair<K, V>> map)
```


Creates an empty dictionary or initializes it with a list of key-value pairs.

# Methods

## Length
```cpp
size_t Length() const
```

Returns the number of key-value pairs stored in the dictionary.

## Empty
```cpp
bool Empty() const
```

Returns true if the dictionary contains no elements.

## Get
```cpp
V Get(K key) const
```

Returns the value associated with the specified key.
Throws if the key does not exist.

## Set
```cpp
void Set(K key, V value)
```

If the key already exists, updates its associated value.
If the key does not exist, inserts a new key-value pair.

## RemoveByKey
```cpp
void RemoveByKey(K key)
```

Removes the entry with the specified key, if it exists.

## RemoveByValue
```cpp
void RemoveByValue(V value)
```

Removes all entries that contain the specified value.

## Clear
```cpp
void Clear()
```

Removes all key-value pairs from the dictionary.

## HasKey
```cpp
bool HasKey(const K& key) const
```

Checks whether the given key exists in the dictionary.

## GetKeyList
```cpp
List<K> GetKeyList() const
```

Returns a List containing all keys in the dictionary.

## GetValueList
```cpp
List<V> GetValueList() const
```

Returns a List containing all values in the dictionary.

## FilterByValue
```cpp
Dictionary<K, V> FilterByValue(const V& value) const
```

Returns a new dictionary containing only entries with the specified value.

## std_vector
```cpp
std::vector<Pair<K, V>> std_vector() const
```

Returns a copy of the underlying list as a std::vector of pairs.