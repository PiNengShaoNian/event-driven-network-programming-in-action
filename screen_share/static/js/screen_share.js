'use strict';

const localVideo = document.getElementById('localVideo');
const startPushBtn = document.getElementById('btnStartPush');

const startPush = () => {
    console.log('start push stream');

    navigator.mediaDevices.getDisplayMedia({
        audio: false,
        video: true,
    }).then((stream) => {
        console.log("get screen stream success");

        localVideo.srcObject = stream;
    }).catch(() => {
        console.log("get screen stream failed, err: " + err);
    });
}
startPushBtn.addEventListener('click', startPush)