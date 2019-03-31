
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

extern "C" {

	typedef void (*callback)(int);

	typedef struct Color {
		int a;
		int r;
		int g;
		int b; 
	} Color;

	typedef struct Vec2 {
		float x;
		float y;
	} Vec2;

	typedef struct Vec3 {
		float x;
		float y;
		float z;
	} Vec3;

	void doCallback(callback func, int num) {
		func(num);
	}

	// Device Related

	IrrlichtDevice * newDevice(Vec2 size) {
		return createDevice(EDT_OPENGL, dimension2d<u32>((int)size.x, (int)size.y));
	}

	int deviceRun(IrrlichtDevice * device) {
		return device->run();
	}

	// Video Driver

	IVideoDriver * getVideoDriver(IrrlichtDevice * device) {
		return device->getVideoDriver();
	}

	void beginScene(IVideoDriver * driver, int backBuffer, int zBuffer, Color color) {
		driver->beginScene(backBuffer, zBuffer, SColor(color.a, color.r, color.b, color.g));
	}

	void endScene(IVideoDriver * driver) {
		driver->endScene();
	}

	// Scene Manager

	ISceneManager * getSceneManager(IrrlichtDevice * device) {
		return device->getSceneManager();
	}

}


