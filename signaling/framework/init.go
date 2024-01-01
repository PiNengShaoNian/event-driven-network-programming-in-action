package framework

import (
	"fmt"
	"signaling/glog"
)

var gconf *FrameworkConf

func Init(confFile string) error {
	var err error
	gconf, err = loadConf(confFile)
	if err != nil {
		return err
	}
	fmt.Printf("%+v", gconf)
	glog.SetLogDir("./log")
	glog.SetLogFileName("signaling")
	glog.SetLogLevel("DEBUG")
	glog.SetLogToStderr(true)
	return nil
}
