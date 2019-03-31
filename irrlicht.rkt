#lang racket

(require 
	ffi/unsafe)

(define libirr (ffi-lib "libirr"))
(define _callback (_fun _int -> _void))

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

; Device

(define _IrrlichtDevice (_cpointer 'IrrlichtDevice))
(define newDevice 
	(get-ffi-obj "newDevice" libirr
							 (_fun _Vec2 -> _IrrlichtDevice)))

(define deviceRun
	(get-ffi-obj "deviceRun" libirr
							 (_fun _IrrlichtDevice -> _int)))

; Video Driver 

(define _IVideoDriver (_cpointer 'IVideoDriver))

(define getVideoDriver
	(get-ffi-obj "getVideoDriver" libirr
							 (_fun _IrrlichtDevice -> _IVideoDriver)))

(define beginScene
	(get-ffi-obj "beginScene" libirr
							 (_fun _IVideoDriver _int _int _Color -> _void)))

(define endScene
	(get-ffi-obj "endScene" libirr
							 (_fun _IVideoDriver -> _void)))

; Scene Manager

(define _ISceneManager (_cpointer 'ISceneManager))

(define getSceneManager
	(get-ffi-obj "getSceneManager" libirr
							 (_fun _IrrlichtDevice -> _ISceneManager)))

#|
(define doCallback
	(get-ffi-obj "doCallback" libirr
							 (_fun _callback _int -> _void)))
(define fnc 
	(lambda (n) 
		(displayln (format "value: ~a" n))))
(doCallback fnc 1)
|#

(define (test)
	(define device (newDevice (make-Vec2 640.0 480.0)))
	(define video (getVideoDriver device))
	(define scene (getSceneManager device))
	(define clr (make-Color 255 0 100 0))
	(define (loop)
		(cond
			[(eq? 1 (deviceRun device))
		 	(let () 
				(beginScene video 1 1 clr)
				(endScene video)
				(sleep 1)
				(loop))]))
	(loop))

(module+ main (test))

