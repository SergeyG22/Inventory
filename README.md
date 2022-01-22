### Inventory 

Inventory for the game using the drag'n'drop principle. When dragging, items are added to different cells, counted and deleted.
All items are stored in sqlite data base.

### Build from source
**MinGW compiler debug version:**

```
Select the compiler command line MinGW and go to the directory with the .pro file (example MinGW 7.3.0 64-bit command line)
Then enter the following commands:

mkdir build
cd build
qmake -makefile ..
mingw32-make debug

After entering the commands, an executable file will appear in the build folder.
```
**MinGW compiler release version:**

```
mkdir build
cd build
qmake -makefile ..
mingw32-make release
```
After entering the commands, an executable file will appear in the build folder.To add a DLL in the directory with Qt (not QtCreator, namely Qt of the desired version), there is a utility in the bin folder windeployqt.exe . Run it and it will copy the necessary files:
windeployqt.exe "the path to the application file." Choose it for your compiler (MinGW or MSVC).

---

**MSVC compiler debug version:**

```
Run vcvarsall.bat in directory vs19\VC\Auxiliary\Build
Select the compiler command line MSVC and go to the directory with the .pro file (example x64 Native Tools Command Promt)

Then enter the following commands:

mkdir build
cd build
qmake -makefile ..
nmake Debug

After entering the commands, an executable file will appear in the build folder.
```

**MSVC compiler release version:**

```
mkdir build
cd build
qmake -makefile ..
nmake Release
```

### Mouse control
```
[left mouse button] - drag item
[release the left mouse button] - drop item
[right mouse button] - use item
```

### Buttons control

```
[new game] - start a new game
[exit] - close game
[main menu] - block/unlock inventory

```

### Preview

![hippo](https://github.com/SergeyG22/Inventory/blob/master/resource/animaton.git/animation.gif)
