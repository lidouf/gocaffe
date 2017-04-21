package gocaffe

/*
#cgo CXXFLAGS: -I/usr/local/include/ -I./deps/ -O3 -Wall
#cgo LDFLAGS: -lcaffe -lboost_system -lstdc++ -lopencv_core -lopencv_highgui -lopencv_imgproc -lboost_filesystem -lopencv_imgcodecs
#include <stdlib.h>
#include "classification.h"
*/
import "C"

import (
	"sync"
	"unsafe"
)

type Classifier struct {
	predictor C.Classifier
	lock      *sync.Mutex
}

func NewClassifier(model, trained, mean, label string) *Classifier {
	modelpath := C.CString(model)
	defer C.free(unsafe.Pointer(modelpath))

	trainedpath := C.CString(trained)
	defer C.free(unsafe.Pointer(trainedpath))

	meanpath := C.CString(mean)
	defer C.free(unsafe.Pointer(meanpath))

	labelpath := C.CString(label)
	defer C.free(unsafe.Pointer(labelpath))

	return &Classifier{
		predictor: C.Classifier(modelpath, trainedpath, mean, label),
		lock:      &sync.Mutex{},
	}
}

func (p *Classifier) Predict(imgfile string) []string {
	p.lock.Lock()
	defer p.lock.Unlock()
	imgpath := C.CString(imgfile)
	defer C.free(unsafe.Pointer(imgpath))

	ret := C.Predict(p.predictor, imgpath)
	if ret == nil {
		return nil
	}
	//return doubleToFloats(ret, p.NClass())
	//TODO
	return []string{"url", "abc"}
}