package action

import (
	"fmt"
	"net/http"
	"signaling/framework"
	"text/template"
)

type xrtcClientPushAction struct{}

func NewXrtcClientPushAction() *xrtcClientPushAction {
	return &xrtcClientPushAction{}
}

func writeHttpErrorResponse(w http.ResponseWriter, status int, err string) {
	w.WriteHeader(status)
	w.Write([]byte(err))
}

func (*xrtcClientPushAction) Execute(w http.ResponseWriter, r *framework.ComRequest) {
	t, err := template.ParseFiles(fmt.Sprintf("%s/template/push.tpl", framework.GetHttpStaticDir()))

	if err != nil {
		fmt.Println(err)
		writeHttpErrorResponse(w, http.StatusNotFound, "404 - Not Found")
		return
	}

	request := make(map[string]string)

	for k, v := range r.R.Form {
		request[k] = v[0]
	}

	t.Execute(w, request)
	if err != nil {
		fmt.Println(err)
		writeHttpErrorResponse(w, http.StatusNotFound, "404 - Not found")
		return
	}
}
