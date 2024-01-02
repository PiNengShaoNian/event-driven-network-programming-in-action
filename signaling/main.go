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

	// 静态资源处理 /static
	framework.RegisterStaticUrl()

	go startHttp()

	startHttps()
}

func startHttp() {
	err := framework.StartHttp()

	if err != nil {
		panic(err)
	}
}

func startHttps() {
	err := framework.StartHttps()

	if err != nil {
		panic(err)
	}
}
