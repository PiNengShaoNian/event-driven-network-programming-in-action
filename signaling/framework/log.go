package framework

import (
	"fmt"
	"math/rand"
	"signaling/glog"
	"time"
)

func init() {
	rand.Seed(time.Now().Unix())
}

func GetLogId32() uint32 {
	return rand.Uint32()
}

type logItem struct {
	field string
	value string
}

type ComLog struct {
	mainLog []logItem
}

func (l *ComLog) AddNotice(field, value string) {
	item := logItem{
		field: field,
		value: value,
	}
	l.mainLog = append(l.mainLog, item)
}

func (l *ComLog) getPrefixLog() string {
	prefixLog := ""
	for _, item := range l.mainLog {
		prefixLog += fmt.Sprintf("%s[%s] ", item.field, item.value)
	}

	return prefixLog
}

func (l *ComLog) Debugf(format string, args ...interface{}) {
	totalLog := l.getPrefixLog() + format
	glog.Debugf(totalLog, args...)
}

func (l *ComLog) Infof(format string, args ...interface{}) {
	totalLog := l.getPrefixLog() + format
	glog.Infof(totalLog, args...)
}

func (l *ComLog) Warningf(format string, args ...interface{}) {
	totalLog := l.getPrefixLog() + format
	glog.Warningf(totalLog, args...)
}
