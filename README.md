# fx-CG50DOOM
DOOM for the CASIO fx-CG50 graphical calculators. It is not supposed to be a 1-1 recreation or even feature complete, but I hope to have E1M1 partially recreated.

## Running it on your calculator

Connect your calculator to your computer using a Mini USB cable. A menu should appear on the calculator - press F1 and the calculator should appear in your computer like a removable drive. Drag and drop a compiled .g3a file into the root directory and eject (on Windows, right click on the drive in Explorer). It should be at the end of the main program menu.

.g3a files can be compiled from source yourself (see below) or downloaded from the [releases page](https://github.com/seckujdivad/fx-CG50DOOM/releases/latest).

## Compiling it yourself

Use [this](http://prizm.cemetech.net/index.php/PrizmSDK_Setup_Guide) setup guide and replace the include, lib/libc.a and lib/libfxcg.a with the latest versions at [the libfxcg repository](https://github.com/Jonimoose/libfxcg).

## Development notes

The absence of a standard library means that classes have to be initialised using `malloc` and deleted using `free`. `malloc` and `free` aren't part of the fxcg standard library, but including fxcg/heap.h gives you access to `sys_malloc` and `sys_free`.

To initalise a class Test, you would do 
```cpp
Test* obj = (Test*)sys_malloc(sizeof(Test));
```
You would also need to write your own constructor (I name them all Initialise) and call it yourself as this will not call the standard C++ constructor.

Freeing a class can be done by calling

```cpp
obj->~Test();
sys_free(obj);
```
Omit
```cpp
obj->~Test();
```
if no destructor has been defined.
