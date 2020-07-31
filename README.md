# BoostLogger
Simple logger implementation using boost lib

## Requirements
* Boost >= 1.65

## Usage
Just include the file after adding it to the include path.

## Example
```cpp

#include "BoostLogger.h"

using namespace SimpleLogger;

int main() {

  LOG(GET_LOGGER, TRACE) << "This is trace log";
  LOG(GET_LOGGER, DEBUG) << "This is debug log";
  LOG(GET_LOGGER, WARNING) << "This is warning log";
  LOG(GET_LOGGER, INFO) << "This is info log";

  return 0;
}
```

## Log Output
```Text
20200731-18:43:49 [test.cpp : 007] <trace> : This is trace log
20200731-18:43:49 [test.cpp : 008] <debug> : This is debug log
20200731-18:43:49 [test.cpp : 009] <warning> : This is warning log
20200731-18:43:49 [test.cpp : 010] <info> : This is info log
```

## Build (example)
```Bash
mkdir build
cd build
cmake ../example && make
```
