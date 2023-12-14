package src

import (
	"fmt"
	"net/http"
)

func Test() {
	staticUrl := "/static/"

	fs := http.FileServer(http.Dir("./static"))

	http.Handle(staticUrl, http.StripPrefix(staticUrl, fs))

	err := http.ListenAndServe(":8080", nil)

	if err != nil {
		fmt.Println(err)
	}
}
