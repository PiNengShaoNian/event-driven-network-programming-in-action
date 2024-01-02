package main

import (
	"signaling/action"
	"signaling/framework"
)

func init() {
	framework.GActionRouter["/xrtcclient/push"] = action.NewXrtcClientPushAction()
	framework.GActionRouter["/signaling/push"] = action.NewPushAction()
}
