
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <string>
#include <vector>
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

vector3d<f32> v3(Vec3 v) {
  return vector3d<f32>(v.x, v.y, v.z);
}

btVector3 bv3(Vec3 v) {
  return btVector3(v.x, v.y, v.z);
}

btVector3 irrbv3(vector3d<f32> v) {
  return btVector3(v.X, v.Y, v.Z);
}

vector2d<f32> v2(Vec2 v) {
  return vector2d<f32>(v.x, v.y);
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

  EXPORT(IrrlichtDevice * newDevice(E_DRIVER_TYPE driverType, Vec2 size, int bits, int fullscreen, int stencilBuffer, int vsync)) {
    return createDevice(driverType, dimension2d<u32>((int)size.x, (int)size.y), bits, fullscreen, stencilBuffer, vsync, new EventHandler());
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

  EXPORT(ITimer * getTimer(IrrlichtDevice * device)) {
    return device->getTimer();
  }

  EXPORT(unsigned int getTime(ITimer * timer)) {
    return timer->getTime();
  }

  EXPORT(void startTimer(ITimer * timer)) {
      timer->start();
  }

  EXPORT(void stopTimer(ITimer * timer)) {
    timer->stop();
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
	std::cout << "Path: " << filepath << std::endl;
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

  EXPORT(IBillboardSceneNode * addBillboard(ISceneManager * scene, Vec2 size, Vec3 position)) {
    return scene->addBillboardSceneNode(NULL, v2(size), v3(position));
  }

  EXPORT(IBillboardSceneNode * addBillboardText(ISceneManager * scene, IGUIFont * font, char * text, Vec2 size, Vec3 position)) {
    std::string textString(text);
    std::wstring wText(textString.length(), L' ');
    std::copy(textString.begin(), textString.end(), wText.begin());
    return scene->addBillboardTextSceneNode(font, wText.c_str(), NULL, v2(size), v3(position));
  }

  EXPORT(ISceneNode * addNull(ISceneManager * scene)) {
    return scene->addEmptySceneNode();
  }

  EXPORT(ILightSceneNode * addLight(ISceneManager * scene, Vec3 position, Color color, float radius)) {
    return scene->addLightSceneNode(NULL, v3(position), SColorf(color.r / 255.0, color.g / 255.0, color.b / 255.0));
  }

  EXPORT(ISceneNode * addCube(ISceneManager * scene, float size, Vec3 position, Vec3 rotation, Vec3 scale)) {
    return scene->addCubeSceneNode(size, NULL, -1, v3(position), v3(rotation), v3(scale));
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

  EXPORT(ICameraSceneNode * addCamera(ISceneManager * scene, Vec3 position, Vec3 target, int active)) {
    return scene->addCameraSceneNode(NULL, v3(position), v3(target), -1, active);
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

  EXPORT(ICameraSceneNode * getActiveCamera(ISceneManager * manager)) {
    return manager->getActiveCamera();
  }

  EXPORT(void setActiveCamera(ISceneManager * manager, ICameraSceneNode * camera)) {
    manager->setActiveCamera(camera);
  }

  EXPORT(void setParent(ISceneNode * node, ISceneNode * child)) {
    child->setParent(node);
  }

  EXPORT(void addChild(ISceneNode * node, ISceneNode * child)) {
    node->addChild(child);
  }

  EXPORT(ISceneNode * getParent(ISceneNode * node)) {
    return node->getParent();
  }

  EXPORT(int getID(ISceneNode* node)) {
    return node->getID();
  }

  EXPORT(void setID(ISceneNode * node, int id)) {
    node->setID(id);
  }

  EXPORT(void removeNode(ISceneNode * node)) {
    node->remove();
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

  // Bullet physics
  
  EXPORT(btDefaultCollisionConfiguration * newCollisionConfiguration()) {
    return new btDefaultCollisionConfiguration();
  }

  EXPORT(btBroadphaseInterface * newAxisSweep(Vec3 min, Vec3 max)) {
    return new btAxisSweep3(bv3(min), bv3(max));
  }

  EXPORT(btCollisionDispatcher * newCollisionDispatcher(btDefaultCollisionConfiguration * config)) {
    return new btCollisionDispatcher(config);
  }

  EXPORT(btSequentialImpulseConstraintSolver * newSequentialConstraintSolver()) {
    return new btSequentialImpulseConstraintSolver();
  }

  EXPORT(btDiscreteDynamicsWorld * newDynamicsWorld(
          btCollisionDispatcher * dispatcher,
          btBroadphaseInterface * broadphase,
          btSequentialImpulseConstraintSolver * solver,
          btDefaultCollisionConfiguration * config)) {
    return new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
  }

  EXPORT(void deleteWorld(
          btCollisionDispatcher * dispatcher,
          btBroadphaseInterface * broadphase,
          btSequentialImpulseConstraintSolver * solver,
          btDefaultCollisionConfiguration * config,
          btDiscreteDynamicsWorld * world)) {
    delete world;
    delete config;
    delete solver;
    delete broadphase;
    delete dispatcher;
  }

  EXPORT(void stepSimulation(btDiscreteDynamicsWorld * world, float delta)) {
    world->stepSimulation(delta);
  }

  EXPORT(void addRigidBody(btDiscreteDynamicsWorld * world, btRigidBody * body)) {
    world->addRigidBody(body);
  }

  EXPORT(btRigidBody * cubeToRigidBody(ISceneNode * node, float mass=0.0f)) {
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(irrbv3(node->getPosition()));
    btDefaultMotionState * state = new btDefaultMotionState(transform);
    btVector3 half(node->getScale().X*0.5f, node->getScale().Y*0.5f, node->getScale().Z*0.5f);
    btCollisionShape * shape = new btBoxShape(half);
    btRigidBody * body;
    btVector3 inertia;
    shape->calculateLocalInertia(mass, inertia);
    body = new btRigidBody(mass, state, shape, inertia);
    body->setUserPointer((void*)node);
    return body;
  }

  EXPORT(void updateRigidBody(btRigidBody * object)) {
    ISceneNode * node = static_cast<ISceneNode*>(object->getUserPointer());
    btVector3 point = object->getCenterOfMassPosition();
    node->setPosition(vector3d<f32>((f32)point[0], (f32)point[1], (f32)point[2]));

    vector3d<f32> euler;
    const btQuaternion& quat = object->getOrientation();
    quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
    q.toEuler(euler);
    euler *= RADTODEG;
    node->setRotation(euler);
  }

  EXPORT(btRigidBody * meshToRigidBody(IMeshSceneNode * node)) {
    btRigidBody * body = NULL;
    if ( node->getType() == ESNT_ANIMATED_MESH || node->getType() == ESNT_MESH ) {
      vector3d<f32> nodeScale = node->getScale();
      IMesh * mesh = ((IMeshSceneNode*)node)->getMesh();
      size_t buffercount = mesh->getMeshBufferCount();
      btVector3 position = irrbv3(node->getPosition());
      
      std::vector<S3DVertex> vVertices;
      std::vector<int> vIndices;

      for( size_t i = 0; i < buffercount; ++i ) {
        IMeshBuffer * buffer = mesh->getMeshBuffer(i);
        E_VERTEX_TYPE vertexType = buffer->getVertexType();
        E_INDEX_TYPE indexType = buffer->getIndexType();
        size_t numVerts = buffer->getVertexCount();
        size_t numInd = buffer->getIndexCount();
        vVertices.resize(vVertices.size() + numVerts);
        vIndices.resize(vIndices.size() + numInd);

        void * vertices = buffer->getVertices();
        void * indices = buffer->getIndices();

        S3DVertex * standard = reinterpret_cast<S3DVertex*>(vertices);
        S3DVertex2TCoords * two2coords = reinterpret_cast<S3DVertex2TCoords*>(vertices);
        S3DVertexTangents * tangents = reinterpret_cast<S3DVertexTangents*>(vertices);
        
        int16_t * ind16 = reinterpret_cast<int16_t*>(indices);
        int32_t * ind32 = reinterpret_cast<int32_t*>(indices);

        for(size_t v = 0; v < numVerts; ++v) {
          auto & vert = vVertices[v];
          switch(vertexType) {
            case EVT_STANDARD:
              vert = standard[v];
              break;
          }
        }

        for(size_t n = 0; n < numInd; ++n) {
          auto & index = vIndices[n];
          switch(indexType) {
            case EIT_16BIT:
              index = ind16[n];
              break;
            case EIT_32BIT:
              index = ind32[n];
              break;
          }
        }

      }

      if (!vVertices.empty() && !vIndices.empty()) {
        const size_t numIndices = vIndices.size();
        const size_t numTriangles = numIndices / 3;
        btTriangleMesh * btmesh = new btTriangleMesh();
        for (size_t i = 0; i < numIndices; i += 3) {
          const btVector3 &A = irrbv3(vVertices[vIndices[i]].Pos);
          const btVector3 &B = irrbv3(vVertices[vIndices[i]].Pos);
          const btVector3 &C = irrbv3(vVertices[vIndices[i]].Pos);
          btmesh->addTriangle(A, B, C, true);
        }

        btTransform transform;
        transform.setIdentity();
        transform.setOrigin(position);
        btDefaultMotionState * motionState = new btDefaultMotionState(transform);

        btCollisionShape * btShape = new btBvhTriangleMeshShape(btmesh, true);
        btShape->setMargin(0.05f);

        btScalar mass = 0.0f;
        body = new btRigidBody(mass, motionState, btShape);
        body->setUserPointer((void*)node);
      }
    }
    return body;
  }

  EXPORT(void deleteRigidBody(btDiscreteDynamicsWorld * world, btRigidBody * body)) {
    world->removeCollisionObject(body);
    delete body->getCollisionShape();
    delete body;
  }

}



