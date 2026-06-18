# 📦 Debug

The ```Debug``` module provides a lightweight logging and diagnostic system for applications. It allows printing colored log and warning messages to the console, as well as persisting them into files for later inspection.

The module is based on the singleton ```DEBUG``` class, which ensures centralized logging across the entire application.

# Behaviour

Messages are time-stamped and color-coded in the console, supporting both standard logs and warnings. Log persistence can be enabled to save entries to ```Debug/logFile.txt```, and internal methods are included for specialized ARL system logging.

# Methods
## Persist
```cpp
void Persist(bool flag = true)
```

Enables or disables persistent logging.

__Parameters:__

* ```flag```: True to enable persistence (logs are saved to file), false to disable.

## Log
```cpp
void Log(String str, List<String> values = {}, bool persist = false)
```

Prints a standard log message to the console. Optionally persists it to the log file.

__Parameters:__

* ```str```: Message template.

* ```values```: List of values to format into the message.

* ```persist```: True to force saving this log to file regardless of global settings.

## Warning
```cpp
void Warning(String str, List<String> values = {}, bool persist = false)
```

Prints a warning message to the console in yellow/orange. Optionally persists it to the log file.

__Parameters:__

* ```str```: Message template.

* ```values```: List of values to format into the message.

* ```persist```: True to force saving this warning to file regardless of global settings.

## SetWaitTime
```cpp
void SetWaitTime(int waitTime)
```

Sets the minimum delay between consecutive log outputs, avoiding message flooding.

__Parameters:__

* ```waitTime```: Time in milliseconds. Must be ≥ 0.

## ARLMessage (internal)
```cpp
void ARLMessage(String str, List<String> values = {})
```

Logs a system message under the ARL (Automated Runtime Layer).

## ARLError (internal)
```cpp
void ARLError(String str, List<String> values = {})
```

Logs an error message under the ARL system.