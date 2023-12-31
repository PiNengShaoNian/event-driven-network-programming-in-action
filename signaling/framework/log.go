package framework

import (
	"math/rand"
	"signaling/glog"
	"time"
)

func init() {
	rand.Seed(time.Now().Unix())
}

func GetLogId32() uint32 {
	return rand.Uint32()
}

type ComLog struct {
}

func (l *ComLog) Debugf(format string, args ...interface{}) {
	glog.Debugf(format, args...)
}

func (l *ComLog) Infof(format string, args ...interface{}) {
	glog.Infof(format, args...)
}

func (l *ComLog) Warningf(format string, args ...interface{}) {
	glog.Warningf(format, args...)
}
