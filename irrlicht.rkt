#lang racket

(require 
  ffi/unsafe)

(define libirr (ffi-lib "libirr"))

; Structures

(define-cstruct _Color
                ([a _int]
                 [r _int]
                 [g _int]
                 [b _int]))

(define-cstruct _Vec2 
                ([x _float]
                 [y _float]))

(define-cstruct _Vec3 ([x _float]
                       [y _float]
                       [z _float]))

(define-cstruct _Rect ([x1 _int]
                       [y1 _int]
                       [x2 _int]
                       [y2 _int]))

; Device

(define _IrrlichtDevice (_cpointer 'IrrlichtDevice))
(define newDevice 
  (get-ffi-obj "newDevice" libirr
               (_fun _Vec2 -> _IrrlichtDevice)))

(define deviceRun
  (get-ffi-obj "deviceRun" libirr
               (_fun _IrrlichtDevice -> _int)))

(define setWindowCaption
  (get-ffi-obj "setWindowCaption" libirr
               (_fun _IrrlichtDevice _string -> _void)))

(define _keyboardEvent (_fun _int _int _int _int -> _void))
(define setKeyboardCallback
  (get-ffi-obj "setKeyboardCallback" libirr
               (_fun _IrrlichtDevice _keyboardEvent -> _void)))

(define _mouseEvent (_fun _int _int _float _int _int _int _int _int -> _void))
(define setMouseCallback
  (get-ffi-obj "setMouseCallback" libirr
               (_fun _IrrlichtDevice _mouseEvent -> _void)))

; Video Driver 

(define _IVideoDriver (_cpointer 'IVideoDriver))
(define _ITexture (_cpointer 'ITexture))

(define getVideoDriver
  (get-ffi-obj "getVideoDriver" libirr
               (_fun _IrrlichtDevice -> _IVideoDriver)))

(define beginScene
  (get-ffi-obj "beginScene" libirr
               (_fun _IVideoDriver _int _int _Color -> _void)))

(define endScene
  (get-ffi-obj "endScene" libirr
               (_fun _IVideoDriver -> _void)))

(define getFPS
  (get-ffi-obj "getFPS" libirr
               (_fun _IVideoDriver -> _int)))

(define getTexture
  (get-ffi-obj "getTexture" libirr
               (_fun _IVideoDriver _string -> _ITexture)))

(define _E_MATERIAL_FLAG
  (_enum
    '(Wireframe          = #x1
      Pointcloud         = #x2
      Gouraud_Shading    = #x4
      Lighting           = #x8
      Zbuffer            = #x10
      Zwrite_Enable      = #x20
      Back_Face_Culling  = #x40
      Front_Face_Culling = #x80
      Bilinear_Filter    = #x100
      Trilinear_Filter   = #x200
      Anisotropic_Filter = #x400
      Fog_Enable         = #x800
      Normalize_Normals  = #x1000
      Texture_Wrap       = #x2000
      Anti_Aliasing      = #x4000
      Color_Mask         = #x8000
      Color_Material     = #x10000
      Use_Mip_Maps       = #x20000
      Blend_Operation    = #x40000
      Polygon_Offset     = #x80000)))

(define _E_MATERIAL_TYPE
  (_enum
    '(Solid = 0
      Solid_2_Layer
      Lightmap
      Lightmap_Add
      Lightmap_M2
      Lightmap_M4
      Lightmap_Lighting
      Lightmap_Lighting_M2
      Lightmap_Lighting_M4
      Detail_Map
      Sphere_Map
      Reflection_2_Layer
      Transparent_Add_Color
      Transparent_Alpha_Channel
      Transparent_Alpha_Channel_Ref
      Transparent_Vertex_Alpha
      Transparent_Reflection_2_Layer
      Normal_Map_Solid
      Normal_Map_Transparent_Add_Color
      Normal_Map_Transparent_Vertex_Alpha
      Parallax_Map_Solid
      Parallax_Map_Transparent_Add_Color
      Parallax_Map_Transparent_Vertex_Alpha
      Onetexture_Blender
      Force_32bit = #x7fffffff)))

; Scene Manager

(define _ISceneManager (_cpointer 'ISceneManager))
(define _ISceneNode (_cpointer 'ISceneNode))
(define _IAnimatedMesh (_cpointer 'IAnimatedMesh))

(define getSceneManager
  (get-ffi-obj "getSceneManager" libirr
               (_fun _IrrlichtDevice -> _ISceneManager)))

(define drawScene
  (get-ffi-obj "drawScene" libirr
               (_fun _ISceneManager -> _void)))

(define getMesh
  (get-ffi-obj "getMesh" libirr
               (_fun _ISceneManager _string -> _IAnimatedMesh)))

(define addAnimatedMesh
  (get-ffi-obj "addAnimatedMesh" libirr
               (_fun _ISceneManager _IAnimatedMesh -> _ISceneNode)))

(define addBillboard
  (get-ffi-obj "addBillboard" libirr
               (_fun _ISceneManager -> _ISceneNode)))

(define addNull
  (get-ffi-obj "addNull" libirr
               (_fun _ISceneManager -> _ISceneNode)))

(define addLight
  (get-ffi-obj "addLight" libirr
               (_fun _ISceneManager -> _ISceneNode)))

(define addCube
  (get-ffi-obj "addCube" libirr
               (_fun _ISceneManager -> _ISceneNode)))

(define addOctree
  (get-ffi-obj "addOctree" libirr
               (_fun _ISceneManager _IAnimatedMesh -> _ISceneNode)))

(define addCamera
  (get-ffi-obj "addCamera" libirr
               (_fun _ISceneManager -> _ISceneNode)))

(define setTarget
  (get-ffi-obj "setTarget" libirr
               (_fun _ISceneNode _Vec3 -> _void)))

(define setPosition
  (get-ffi-obj "setPosition" libirr
               (_fun _ISceneNode _Vec3 -> _void)))

(define setRotation
  (get-ffi-obj "setRotation" libirr
               (_fun _ISceneNode _Vec3 -> _void)))

(define setScale
  (get-ffi-obj "setScale" libirr
               (_fun _ISceneNode _Vec3 -> _void)))

(define setMaterialFlag
  (get-ffi-obj "setMaterialFlag" libirr
               (_fun _ISceneNode _E_MATERIAL_FLAG _int -> _void)))

(define setMaterialTexture
  (get-ffi-obj "setMaterialTexture" libirr
               (_fun _ISceneNode _int _ITexture -> _void)))

; GUI

(define _IGUIEnvironment (_cpointer 'IGUIEnvironment))
(define _IGUIFont (_cpointer 'IGUIFont))

(define getGUIEnvironment
  (get-ffi-obj "getGUIEnvironment" libirr
               (_fun _IrrlichtDevice -> _IGUIEnvironment)))

(define getDefaultFont
  (get-ffi-obj "getDefaultFont" libirr
               (_fun _IGUIEnvironment -> _IGUIFont)))

(define getFont
  (get-ffi-obj "getFont" libirr
               (_fun _IGUIEnvironment _string -> _IGUIFont)))

(define drawText
  (get-ffi-obj "drawText" libirr
               (_fun _IGUIFont _string _Rect _Color -> _void)))

; Testing Module 

(define (test)
  (let* ([resolution (make-Vec2 640.0 480.0)]
         [device (newDevice resolution)]
         [video (getVideoDriver device)]
         [scene (getSceneManager device)]
         [gui (getGUIEnvironment device)]
         [black (make-Color 255 0 100 0)]
         [camera (addCamera scene)]
         [cube1 (addCube scene)]
         [cube2 (addCube scene)]
         [cube3 (addCube scene)])
    (setMaterialFlag cube1 'Wireframe 1)
    (setMaterialFlag cube2 'Lighting 0)
    (setPosition cube2 (make-Vec3 25.0 0.0 0.0))
    (setRotation cube2 (make-Vec3 45.0 0.0 0.0))
    (setPosition cube3 (make-Vec3 -25.0 0.0 0.0))
    (setRotation cube3 (make-Vec3 0.0 45.0 0.0))
    (setScale cube3 (make-Vec3 1.0 1.0 2.0))
    (setPosition camera (make-Vec3 30.0 30.0 30.0))
    (setTarget camera (make-Vec3 0.0 0.0 0.0))
    (setWindowCaption device "Hello World. FPS: -1")
    (setKeyboardCallback device 
      (lambda (key down shift ctrl) 
        (displayln (format "Keyboard: ~a ~a ~a ~a" key down shift ctrl))))
    (setMouseCallback device
      (lambda (x y wheel shift ctrl left right middle)
        (displayln (format "Mouse: ~a ~a ~a ~a ~a ~a ~a ~a" x y wheel shift ctrl left right middle))))
    (define (loop)
      (cond [(eq? 1 (deviceRun device))
             (let () 
               (beginScene video 1 1 black)
               (drawScene scene)
               (endScene video)
               (setWindowCaption device (format "Hello World. FPS: ~a" (getFPS video)))
               (drawText (getDefaultFont gui) "Testing writing text" (make-Rect 25 25 200 200) (make-Color 255 255 255 255))
               (sleep 0.0165)
               (loop))]))
    (loop)))

(module+ main (test))

(provide
  ; Structures
  _Vec2
  _Vec3
  _Color
  ; Device
  newDevice
  deviceRun
  setWindowCaption
  setKeyboardCallback
  setMouseCallback
  ; Video
  getVideoDriver
  beginScene
  endScene
  getFPS
  getTexture
  ; Scene
  getSceneManager
  drawScene
  getMesh
  addAnimatedMesh
  addBillboard
  addNull
  addLight
  addCube
  addOctree
  addCamera
  setTarget
  setPosition
  setRotation
  setScale
  setMaterialFlag
  setMaterialTexture
  ; GUI
  getGUIEnvironment
  getDefaultFont
  getFont
  drawText)



