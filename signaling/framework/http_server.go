package framework

import (
	"fmt"
	"net/http"
)

func init() {
	http.HandleFunc("/", entry)
}

type ActionInterface interface {
	Execute(w http.ResponseWriter, r *http.Request)
}

var GActionRouter map[string]ActionInterface = make(map[string]ActionInterface)

func responseError(w http.ResponseWriter, r *http.Request, status int, err string) {
	w.WriteHeader(status)
	w.Write([]byte(fmt.Sprintf("%d - %s", status, err)))
}

func entry(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path == "/favicon.ico" {
		w.WriteHeader(http.StatusOK)
		w.Write([]byte(""))
		return
	}
	fmt.Println("========", r.URL.Path)

	if action, ok := GActionRouter[r.URL.Path]; ok {
		if action != nil {
			action.Execute(w, r)
		} else {
			responseError(w, r, http.StatusInternalServerError, "Internal server error")
		}
	} else {
		responseError(w, r, http.StatusNotFound, "Not found")
	}
}

func StartHttp() error {
	fmt.Println("start http...")
	return http.ListenAndServe(":8080", nil)
}
