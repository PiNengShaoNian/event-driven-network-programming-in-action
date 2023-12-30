'use strict';

const localVideo = document.getElementById('localVideo');
const startPushBtn = document.getElementById('btnStartPush');
const stopPushBtn = document.getElementById('btnStopPush');

const config = {};
const offerOptions = {
  offerToReceiveAudio: false,
  offerToReceiveVideo: false,
};
const pc1 = new RTCPeerConnection(config); // local pc
const pc2 = new RTCPeerConnection(config); // remote pc

const getPc = (pc) => {
  return pc === pc1 ? 'pc1' : 'pc2';
}

const onIceStateChange = (pc, e) => {
  console.log(`${getPc(pc)} ice state change: ${pc.iceConnectionState}`);
}

const onIceCandidate = (pc, e) => {
  console.log(`${getPc(pc)}  get new ice candidate: ${e.candidate ?
    e.candidate.candidate : '(null)'}`);
}

const onSetLocalSuccess = (pc) => {
  console.log(getPc(pc) + ' set local success');
}

const onSetSessionDescriptionError = (err) => {
  console.log('set session description error: ' + err.toString());
}

const onCreateOfferSuccess = (desc) => {
  console.log("offer from pc1: \n" + desc.sdp);

  console.log("pc1 set local description start");
  pc1.setLocalDescription(desc).then(() => {
    onSetLocalSuccess(pc1);
  }, onSetSessionDescriptionError);
}

function onCreateSessionDescriptionError() {
  console.log("create session description error: " + error.toString());
}

const startPush = () => {
  console.log('start push stream');

  navigator.mediaDevices.getDisplayMedia({
    audio: false,
    video: true,
  }).then((stream) => {
    console.log("get screen stream success");
    localVideo.srcObject = stream;

    pc1.oniceconnectionstatechange = (e) => {
      onIceStateChange(pc1, e);
    }

    pc1.onicecandidate = (e) => {
      onIceCandidate(pc1, e);
    }

    pc1.addStream(stream);

    pc1.createOffer(offerOptions)
      .then(onCreateOfferSuccess,
        onCreateSessionDescriptionError)
  }).catch((err) => {
    console.log("get screen stream failed, err: " + err);
  });
}

const stopPush = () => {
  console.log("pc1 stop push stream");

  if (pc1) {
    pc1.close();
    pc1 = null;
  }

  localVideo.srcObject = null;
}

startPushBtn.addEventListener('click', startPush)
stopPushBtn.addEventListener('click', stopPush);