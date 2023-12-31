package main

import (
	"flag"
	"signaling/framework"
	"signaling/glog"
)

func main() {
	flag.Parse()
	framework.Init()

	glog.Info("hello world")

	err := framework.StartHttp()

	if err != nil {
		panic(err)
	}
}
