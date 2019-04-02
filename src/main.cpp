#include <iostream>
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

extern "C" {
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

  typedef struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
  } Rect;

  void doCallback(callback func, int num) {
    func(num);
  }

  // Device Related

  IrrlichtDevice * newDevice(Vec2 size) {
    IrrlichtDevice * device = createDevice(EDT_OPENGL, dimension2d<u32>((int)size.x, (int)size.y));
    device->setEventReceiver(new EventHandler());
    return device;
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

  void setKeyboardCallback(IrrlichtDevice * device, KeyboardEvent ev) {
    ((EventHandler*)device->getEventReceiver())->setKeyboardEvent(ev);
  }

  void setMouseCallback(IrrlichtDevice * device, MouseEvent ev) {
    ((EventHandler*)device->getEventReceiver())->setMouseEvent(ev);
  }

  // Video Driver

  IVideoDriver * getVideoDriver(IrrlichtDevice * device) {
    return device->getVideoDriver();
  }

  void beginScene(IVideoDriver * driver, int backBuffer, int zBuffer, Color color) {
    driver->beginScene(backBuffer, zBuffer, SColor(color.a, color.r, color.g, color.b));
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

  // GUI

  IGUIEnvironment * getGUIEnvironment(IrrlichtDevice * device) {
    return device->getGUIEnvironment();
  }

  IGUIFont * getDefaultFont(IGUIEnvironment * gui) {
    return gui->getBuiltInFont();
  }

  IGUIFont * getFont(IGUIEnvironment * gui, char * filepath) {
    return gui->getFont(filepath);
  }

  void drawText(IGUIFont * font, char * text, Rect rct, Color color) {
    std::string textString(text);
    std::wstring wText(textString.length(), L' ');
    std::copy(textString.begin(), textString.end(), wText.begin());
    font->draw(wText.c_str(), rect<s32>(rct.x1, rct.y1, rct.x2, rct.y2), SColor(color.a, color.r, color.g, color.b));
  }

}


