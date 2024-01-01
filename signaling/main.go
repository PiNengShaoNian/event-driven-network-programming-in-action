package main

import (
	"flag"
	"signaling/framework"
	"signaling/glog"
)

func main() {
	flag.Parse()
	framework.Init("./conf/framework.conf")

	glog.Info("hello world")

	err := framework.StartHttp()

	if err != nil {
		panic(err)
	}
}
