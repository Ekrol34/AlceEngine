# 🛠️ FileSystem

The ```FileSystem``` module provides classes to manage files and folders through an intuitive and object-oriented interface. It simplifies common operations such as creating, deleting, reading, writing, and checking the existence of files and directories. The module leverages the native filesystem capabilities of C++ while providing higher-level abstractions with custom error handling.

## Behaviour

The module revolves around two primary classes: ```File``` and ```Folder```.
Both handle absolute path resolution upon initialization and provide safety checks to prevent invalid operations such as reading a non-existent file or deleting a missing folder.

The ```File``` class offers methods to read, write, append, clear, create, and delete files, while also allowing path retrieval.
The ```Folder``` class supports creating and deleting directories, checking their existence, and retrieving full paths.

Additionally, utility functions ```FileExists``` and ```FolderExists``` are provided for quick existence checks.

---

# 📄 File

Represents a single file on disk and provides operations for creation, manipulation, and content access.

## Constructor
```cpp
File(String path)
```

Initializes the file using an absolute path.

# Methods

## Exists
```cpp
bool Exists()
```

Checks whether the file exists in the filesystem.

## Create
```cpp
void Create()
```

Creates a new empty file.
Throws if the file already exists or cannot be created.

## Delete
```cpp
void Delete()
```

Removes the file from disk.
Throws if the file does not exist.

## Read
```cpp
String Read()
```

Reads and returns the full content of the file.
Throws if the file does not exist.
If file cannot be opened, returns an empty string.

## Write
```cpp
void Write(String str)
```

Overwrites the file with the provided content.
Throws if the file does not exist.

## Append
```cpp
void Append(String str)
```

Adds content to the end of the file without removing existing content.
Throws if the file does not exist.

## Clear
```cpp
void Clear()
```

Removes all content from the file.

## GetFullPath
```cpp
String GetFullPath()
```

Returns the absolute file path.

--- 

# 📂 Folder

Represents a directory on disk and provides basic management features.

## Constructor
```cpp
Folder(String path)
```

Initializes the folder using an absolute path.

# Methods

## Exists
```cpp
bool Exists()
```

Checks whether the directory exists.

## Create
```cpp
void Create()
```

Creates the directory at the specified path.

## Delete
```cpp
void Delete()
```

Deletes the folder and all its content recursively.
Throws if the folder does not exist.

## GetFullPath
```cpp
String GetFullPath()
```

Returns the absolute folder path.


## FolderExists
```cpp
bool FolderExists(String path)
```

Returns true if the specified folder exists.

## FileExists
```cpp
bool FileExists(String path)
```

Returns true if the specified file exists.