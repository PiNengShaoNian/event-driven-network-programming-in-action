package framework

func init() {
	GActionRouter["/xrtcclient/push"] = NewXrtcClientPushAction()
}
