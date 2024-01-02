package comerrors

const (
	NoErr      = 0
	ParamErr   = -1
	NetworkErr = -2
)

type Errors struct {
	errno int
	err   string
}

func New(erron int, err string) *Errors {
	return &Errors{
		errno: erron,
		err:   err,
	}
}

func (e *Errors) Errno() int {
	return e.errno
}

func (e *Errors) Error() string {
	return e.err
}
