package action

import (
	"fmt"
	"net/http"
	"signaling/comerrors"
	"signaling/framework"
	"strconv"
)

type pushAction struct{}

func NewPushAction() *pushAction {
	return &pushAction{}
}

func (*pushAction) Execute(w http.ResponseWriter, cr *framework.ComRequest) {
	r := cr.R

	var strUid string
	if values, ok := r.Form["uid"]; ok {
		strUid = values[0]
	}

	uid, err := strconv.ParseUint(strUid, 10, 64)
	if err != nil || uid <= 0 {
		cerr := comerrors.New(comerrors.ParamErr, "parse uid error: "+err.Error())
		writeJsonErrorResponse(cerr, w, cr)
		return
	}

	var streamName string
	if values, ok := r.Form["streamName"]; ok {
		streamName = values[0]
	}

	if streamName == "" {
		cerr := comerrors.New(comerrors.ParamErr, "streamName is null")
		writeJsonErrorResponse(cerr, w, cr)
		return
	}

	var strAudio, strVideo string
	var audio, video int

	if values, ok := r.Form["audio"]; ok {
		strAudio = values[0]
	}
	if strAudio == "" || strAudio == "0" {
		audio = 0
	} else {
		audio = 1
	}

	if values, ok := r.Form["video"]; ok {
		strVideo = values[0]
	}
	if strVideo == "" || strVideo == "0" {
		video = 0
	} else {
		video = 1
	}

	fmt.Println(uid, streamName, audio, video)
}
