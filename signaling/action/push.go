package action

import (
	"net/http"
	"signaling/comerrors"
	"signaling/framework"
	"strconv"
)

type pushAction struct{}

func NewPushAction() *pushAction {
	return &pushAction{}
}

func writeJsonErrorResponse(err *comerrors.Errors, w http.ResponseWriter, cr *framework.ComRequest) {

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
}
