#include <iostream>
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

#ifdef WINDOWS
#define EXPORT(X) __declspec(dllexport) X
#else
#define EXPORT(X) X
#endif

extern "C" {

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

  typedef struct Rect {
	  Vec2 p1;
	  Vec2 p2;
  } Rect;

  // 1. Key Code
  // 2. Pressed Down
  // 3. Shift held
  // 4. Control held
  typedef void (*KeyboardEvent)(int,int,int,int);

  // 1. X
  // 2. Y
  // 3. Wheel
  // 4. Shift
  // 5. Control
  // 6. Left
  // 7. Right
  // 8. Middle
  typedef void (*MouseEvent)(int,int,float,int,int,int,int,int);

}

class EventHandler : public IEventReceiver {
  public:

    bool OnEvent(const SEvent & event) {
      if (event.EventType == EET_KEY_INPUT_EVENT && _keyboardEvent) {
        _keyboardEvent(event.KeyInput.Key, event.KeyInput.PressedDown, event.KeyInput.Shift, event.KeyInput.Control);
      } 
      else if (event.EventType == EET_MOUSE_INPUT_EVENT && _mouseEvent) {
        _mouseEvent(
            event.MouseInput.X, 
            event.MouseInput.Y, 
            event.MouseInput.Wheel, 
            event.MouseInput.Shift, 
            event.MouseInput.Control, 
            event.MouseInput.isLeftPressed(),
            event.MouseInput.isRightPressed(),
            event.MouseInput.isMiddlePressed());
      }
      return false;
    }

    void setKeyboardEvent(KeyboardEvent ev) {
      _keyboardEvent = ev;
    }

    void setMouseEvent(MouseEvent ev) {
      _mouseEvent = ev;
    }

  private:
    KeyboardEvent _keyboardEvent;
    MouseEvent _mouseEvent;
    bool _keyDown[KEY_KEY_CODES_COUNT];
};

extern "C" {

  EXPORT(IrrlichtDevice * newDevice(Vec2 size)) {
    IrrlichtDevice * device = createDevice(EDT_OPENGL, dimension2d<u32>((int)size.x, (int)size.y));
    device->setEventReceiver(new EventHandler());
    return device;
  }

  EXPORT(int deviceRun(IrrlichtDevice * device)) {
    return device->run();
  }

  EXPORT(void setWindowCaption(IrrlichtDevice * device, char * title)) {
    std::string titleString(title);
    std::wstring wTitle(titleString.length(), L' ');
    std::copy(titleString.begin(), titleString.end(), wTitle.begin());
    device->setWindowCaption(wTitle.c_str());
  }

  EXPORT(void setKeyboardCallback(IrrlichtDevice * device, KeyboardEvent ev)) {
    ((EventHandler*)device->getEventReceiver())->setKeyboardEvent(ev);
  }

  EXPORT(void setMouseCallback(IrrlichtDevice * device, MouseEvent ev)) {
    ((EventHandler*)device->getEventReceiver())->setMouseEvent(ev);
  }

  // Video Driver

  EXPORT(IVideoDriver * getVideoDriver(IrrlichtDevice * device)) {
    return device->getVideoDriver();
  }

  EXPORT(void beginScene(IVideoDriver * driver, int backBuffer, int zBuffer, Color color)) {
    driver->beginScene(backBuffer, zBuffer, SColor(color.a, color.r, color.g, color.b));
  }

  EXPORT(void endScene(IVideoDriver * driver)) {
    driver->endScene();
  }

  EXPORT(int getFPS(IVideoDriver * driver)) {
    return driver->getFPS();
  }
  
  EXPORT(ITexture * getTexture(IVideoDriver * driver, char * filepath)) {
    return driver->getTexture(filepath);
  }

  // Scene Manager

  EXPORT(ISceneManager * getSceneManager(IrrlichtDevice * device)) {
    return device->getSceneManager();
  }

  EXPORT(void drawScene(ISceneManager * scene)) {
    scene->drawAll();
  }

  EXPORT(IAnimatedMesh * getAnimatedMesh(ISceneManager * scene, char * filepath)) {
    return scene->getMesh(filepath);
  }

  EXPORT(IMesh* getMesh(ISceneManager* scene, char* filepath)) {
    return scene->getMesh(filepath);
  }

  EXPORT(IAnimatedMeshSceneNode * addAnimatedMesh(ISceneManager * scene, IAnimatedMesh * mesh)) {
    return scene->addAnimatedMeshSceneNode(mesh);
  }

  EXPORT(IMeshSceneNode* addMesh(ISceneManager* scene, IMesh* mesh)) {
    return scene->addMeshSceneNode(mesh);
  }

  EXPORT(IBillboardSceneNode * addBillboard(ISceneManager * scene)) {
    return scene->addBillboardSceneNode();
  }

  EXPORT(ISceneNode * addNull(ISceneManager * scene)) {
    return scene->addEmptySceneNode();
  }

  EXPORT(ILightSceneNode * addLight(ISceneManager * scene)) {
    return scene->addLightSceneNode();
  }

  EXPORT(ISceneNode * addCube(ISceneManager * scene)) {
    return scene->addCubeSceneNode();
  }

  EXPORT(IMeshSceneNode * addOctree(ISceneManager * scene, IAnimatedMesh * mesh)) {
    return scene->addOctreeSceneNode(mesh);
  }

  EXPORT(ISceneNode * addSkyBox(ISceneManager * scene,
      ITexture * top,
      ITexture * bottom,
      ITexture * left,
      ITexture * right,
      ITexture * front,
      ITexture * back)) {
    return scene->addSkyBoxSceneNode(top, bottom, left, right, front, back);
  }

  EXPORT(ICameraSceneNode * addCamera(ISceneManager * scene)) {
    return scene->addCameraSceneNode();
  }

  EXPORT(void setTarget(ICameraSceneNode * camera, Vec3 target)) {
    camera->setTarget(vector3d<f32>(target.x, target.y, target.z));
  }

  EXPORT(void setPosition(ISceneNode * node, Vec3 position)) {
    node->setPosition(vector3d<f32>(position.x, position.y, position.z));
  }

  EXPORT(void setRotation(ISceneNode * node, Vec3 rotation)) {
    node->setRotation(vector3d<f32>(rotation.x, rotation.y, rotation.z));
  }

  EXPORT(void setScale(ISceneNode * node, Vec3 scale)) {
    node->setScale(vector3d<f32>(scale.x, scale.y, scale.z));
  }

  EXPORT(void setMaterialFlag(ISceneNode * node, E_MATERIAL_FLAG flag, int value)) {
    node->setMaterialFlag(flag, value);
  }

  EXPORT(void setMaterialTexture(ISceneNode * node, int layer, ITexture * texture)) {
    node->setMaterialTexture(layer, texture);
  }

  EXPORT(ITriangleSelector * createOctreeSelector(ISceneManager * scene, IMesh * mesh, ISceneNode * node, int polysPerNode)) {
    return scene->createOctreeTriangleSelector(mesh, node, polysPerNode);
  }

  EXPORT(IMetaTriangleSelector * createMetaSelector(ISceneManager * scene)) {
    return scene->createMetaTriangleSelector();
  }

  EXPORT(ISceneNodeAnimator * createStraightAnimator(ISceneManager * scene, Vec3 start, Vec3 end, int ms, int loop, int pingpong)) {
    return scene->createFlyStraightAnimator(vector3d<f32>(start.x, start.y, start.z), vector3d<f32>(end.x, end.y, end.z), ms, loop, pingpong);
  }

  EXPORT(ISceneNodeAnimator * createCircleAnimator(ISceneManager * scene, Vec3 center, float radius, float speed, Vec3 dir, float start, float radiusEllipsoid)) {
    return scene->createFlyCircleAnimator(vector3d<f32>(center.x, center.y, center.z), radius, speed, vector3d<f32>(dir.x, dir.y, dir.z), start, radiusEllipsoid);
  }

  EXPORT(void addAnimator(ISceneNode * node, ISceneNodeAnimator * animator)) {
    node->addAnimator(animator);
  }

  EXPORT(void dropAnimator(ISceneNodeAnimator * animator)) {
    animator->drop();
  }

  // GUI

  EXPORT(IGUIEnvironment * getGUIEnvironment(IrrlichtDevice * device)) {
    return device->getGUIEnvironment();
  }

  EXPORT(IGUIFont * getDefaultFont(IGUIEnvironment * gui)) {
    return gui->getBuiltInFont();
  }

  EXPORT(IGUIFont * getFont(IGUIEnvironment * gui, char * filepath)) {
    return gui->getFont(filepath);
  }

  EXPORT(void drawText(IGUIFont * font, char * text, Rect rct, Color color)) {
    std::string textString(text);
    std::wstring wText(textString.length(), L' ');
    std::copy(textString.begin(), textString.end(), wText.begin());
    font->draw(wText.c_str(), rect<s32>(rct.p1.x, rct.p1.y, rct.p2.x, rct.p2.y), SColor(color.a, color.r, color.g, color.b));
  }

}



