# Binary

```bash
yacht init PROJECT_NAME --bin OUTPUT_NAME
```

* **File Layout**:
  ```
  PROJECT_NAME
  ├── build 
  │   └── compile_commands.json
  ├── external
  │   └── acutest
  │       └── acutest.h
  ├── include
  ├── src
  │   └── PROJECT_NAME.cpp
  ├── tests
  └── Yacht.toml
  ```


* **Yacht.toml**: 
  ```toml
  [project]
  name = "PROJECT_NAME"
  version = "0.1.0"

  [bin]
  name = "OUTPUT_NAME"
  entry = "src/hello.cpp"
  ```


# Library

Static Library:
```bash
yacht init PROJECT_NAME --lib static
```

Dynamic Library
```bash
yacht init PROJECT_NAME --lib dynamic
```

**File Layout**:
  ```
  PROJECT_NAME
  ├── build 
  │   └── compile_commands.json
  ├── external
  │   └── acutest
  │       └── acutest.h
  ├── include
  ├── src
  │   └── PROJECT_NAME.hpp
  ├── tests
  └── Yacht.toml
  ```

**Yacht.toml**: 
  ```toml
  [project]
  name = "PROJECT_NAME"
  version = "0.1.0"

  [lib]
  name = "OUTPUT_NAME"
  type = "static" # or "dynamic"
  ```


# Modules/Relative Headers

Add `mod.yacht` file inside subdirs to specify a module:
  ```
  PROJECT_NAME
  ├── build 
  │   └── compile_commands.json
  ├── external
  │   └── acutest
  │       └── acutest.h
  ├── include
  ├── src
  │   ├── core
  │       ├── core_header.hpp
  │       └── mod.yacht                     <-----
  │   ├── utils
  │       ├── some_header.hpp
  │       ├── some_other_header.hpp
  │       └── mod.yacht                     <-----
  │   └── PROJECT_NAME.hpp
  ├── tests
  └── Yacht.toml
  ```

This allows you to include `core_header.hpp`, `some_header.hpp`, and `some_other_header.hpp` headers relatively inside other files:

PROJECT_NAME.hpp:
```cpp
#include "core_header.hpp"
#include "some_header.hpp"
#include "some_other_header.hpp"
```
