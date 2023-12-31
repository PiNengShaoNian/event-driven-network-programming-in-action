package main

import (
	"signaling/framework"
)

func main() {
	err := framework.StartHttp()
	if err != nil {
		panic(err)
	}
}
