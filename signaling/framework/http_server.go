package framework

import (
	"fmt"
	"net/http"
)

func init() {
	http.HandleFunc("/", entry)
}

func entry(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path == "/favicon.ico" {
		w.WriteHeader(http.StatusOK)
		w.Write([]byte(""))
		return
	}
	fmt.Println("========", r.URL.Path)
}

func StartHttp() error {
	fmt.Println("start http...")
	return http.ListenAndServe(":8080", nil)
}
