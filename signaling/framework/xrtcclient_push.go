package framework

import (
	"fmt"
	"net/http"
)

type xrtcClientPushAction struct{}

func NewXrtcClientPushAction() *xrtcClientPushAction {
	return &xrtcClientPushAction{}
}

func (*xrtcClientPushAction) Execute(w http.ResponseWriter, r *ComRequest) {
	fmt.Println("hello xrtcClient push action")
}
