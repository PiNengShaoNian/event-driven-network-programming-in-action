package framework

import "signaling/glog"

func Init() error {
	glog.SetLogDir("./log")
	glog.SetLogFileName("signaling")
	return nil
}
