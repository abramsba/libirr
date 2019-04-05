# libirr

C Wrapper for Irrlicht with use in Racket

## Compiling

### Arch Linux

```
pacman -S premake4 irrlicht
premake4 gmake
make
```

### OSX

```
brew install premake4 irrlicht
premake4 gmake
make
```

### Windows

Download premake4: https://premake.github.io/
Download irrlicht: http://irrlicht.sourceforge.net/?page_id=10

Set the following environment variables:

* `IRR_INCLUDE_DIR`: The folder that has `irrlicht.h`
* `IRR_LIBRARY_DIR`: The folder that has `Irrlicht.lib`
	* 32-bit: `<path\to\irrlicht\dir>\irrlicht-1.8.4\lib\Win32-visualstudio`
	* 64-bit: `<path\to\irrlicht\dir>\irrlicht-1.8.4\lib\Win64-visualStudio`

Open `libirr.sln`. If compiling 64-bit create a new configuration. Afterwards, hit build.
 
