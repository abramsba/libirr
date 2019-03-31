#include <iostream>
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

	void setWindowCaption(IrrlichtDevice * device, char * title) {
		std::string titleString(title);
		std::wstring wTitle(titleString.length(), L' ');
		std::copy(titleString.begin(), titleString.end(), wTitle.begin());
		device->setWindowCaption(wTitle.c_str());
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

	int getFPS(IVideoDriver * driver) {
		return driver->getFPS();
	}
	
	ITexture * getTexture(IVideoDriver * driver, char * filepath) {
		return driver->getTexture(filepath);
	}

	// Scene Manager

	ISceneManager * getSceneManager(IrrlichtDevice * device) {
		return device->getSceneManager();
	}

	void drawScene(ISceneManager * scene) {
		scene->drawAll();
	}

	IAnimatedMesh * getMesh(ISceneManager * scene, char * filepath) {
		return scene->getMesh(filepath);
	}

	IAnimatedMeshSceneNode * addAnimatedMesh(ISceneManager * scene, IAnimatedMesh * mesh) {
		return scene->addAnimatedMeshSceneNode(mesh);
	}

	IBillboardSceneNode * addBillboard(ISceneManager * scene) {
		return scene->addBillboardSceneNode();
	}

	ISceneNode * addNull(ISceneManager * scene) {
		return scene->addEmptySceneNode();
	}

	ILightSceneNode * addLight(ISceneManager * scene) {
		return scene->addLightSceneNode();
	}

	ISceneNode * addCube(ISceneManager * scene) {
		return scene->addCubeSceneNode();
	}

	IMeshSceneNode * addOctree(ISceneManager * scene, IAnimatedMesh * mesh) {
		return scene->addOctreeSceneNode(mesh);
	}

	ISceneNode * addSkyBox(ISceneManager * scene, 
			ITexture * top,
			ITexture * bottom,
			ITexture * left,
			ITexture * right,
			ITexture * front,
			ITexture * back) {
		return scene->addSkyBoxSceneNode(top, bottom, left, right, front, back);
	}

	ICameraSceneNode * addCamera(ISceneManager * scene) {
		return scene->addCameraSceneNode();
	}

	void setTarget(ICameraSceneNode * camera, Vec3 target) {
		camera->setTarget(vector3d<f32>(target.x, target.y, target.z));
	}

	void setPosition(ISceneNode * node, Vec3 position) {
		node->setPosition(vector3d<f32>(position.x, position.y, position.z));
	}

	void setRotation(ISceneNode * node, Vec3 rotation) {
		node->setRotation(vector3d<f32>(rotation.x, rotation.y, rotation.z));
	}

	void setScale(ISceneNode * node, Vec3 scale) {
		node->setScale(vector3d<f32>(scale.x, scale.y, scale.z));
	}

	void setMaterialFlag(ISceneNode * node, E_MATERIAL_FLAG flag, int value) {
		node->setMaterialFlag(flag, value);
	}

	void setMaterialTexture(ISceneNode * node, int layer, ITexture * texture) {
		node->setMaterialTexture(layer, texture);
	}

}


