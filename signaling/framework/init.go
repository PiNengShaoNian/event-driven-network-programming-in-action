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

	glog.SetLogDir(gconf.logDir)
	glog.SetLogFileName(gconf.logFile)
	glog.SetLogLevel(gconf.logLevel)
	glog.SetLogToStderr(gconf.logToStderr)

	err = loadXrpc()
	if err != nil {
		return err
	}
	return nil
}
