'use strict';

const localVideo = document.getElementById('localVideo');
const remoteVideo = document.getElementById('remoteVideo');
const startPushBtn = document.getElementById('btnStartPush');
const stopPushBtn = document.getElementById('btnStopPush');
const startPullBtn = document.getElementById('btnStartPull');
const stopPullBtn = document.getElementById('btnStopPull');

const config = {};
const offerOptions = {
  offerToReceiveAudio: false,
  offerToReceiveVideo: false,
};
let pc1 = new RTCPeerConnection(config); // local pc
let pc2 = new RTCPeerConnection(config); // remote pc
let remoteStream;

const getPc = (pc) => {
  return pc === pc1 ? 'pc1' : 'pc2';
}

const onIceStateChange = (pc, e) => {
  console.log(`${getPc(pc)} ice state change: ${pc.iceConnectionState}`);
}

const getOther = (pc) => {
  return pc === pc1 ? pc2 : pc1;
}

const onIceCandidate = (pc, e) => {
  console.log(`${getPc(pc)}  get new ice candidate: ${e.candidate ?
    e.candidate.candidate : '(null)'}`);

  getOther(pc).addIceCandidate(e.candidate).then(() => {
    console.log(getPc(getOther()) + ' add ice candidate success');
  }, (err) => {
    console.log(getPc(getOther()) + ' add ice candidate error: ' + err.toString());
  });
}

const onSetLocalSuccess = (pc) => {
  console.log(getPc(pc) + ' set local success');
}

const onSetRemoteSuccess = (pc) => {
  console.log(getPc(pc) + ' set remote success');
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

  // sdp交换
  pc2.oniceconnectionstatechange = (e) => {
    onIceStateChange(pc2, e);
  }

  pc2.onicecandidate = (e) => {
    onIceCandidate(pc2, e);
  }

  pc2.onaddstream = (e) => {
    console.log("pc2 receive stream, stream_id: " + e.stream.id);
    remoteStream = e.stream;
  }

  pc2.setRemoteDescription(desc)
    .then(() => {
      onSetRemoteSuccess(pc2);
    }, onSetSessionDescriptionError)
}

function onCreateSessionDescriptionError(err) {
  console.log("create session description error: " + err.toString());
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

const onCreateAnswerSuccess = (desc) => {
  console.log(`answer from pc2: \n ${desc.sdp}`);

  console.log("pc2 set local description start");
  pc2.setLocalDescription(desc).then(() => {
    onSetLocalSuccess(pc2);
  }, onSetSessionDescriptionError);

  pc1.setRemoteDescription(desc).then(() => {
    onSetRemoteSuccess(pc1);
  }, onSetSessionDescriptionError)
}

const startPull = () => {
  console.log("start pull stream");

  remoteVideo.srcObject = remoteStream;
  pc2.createAnswer().then(onCreateAnswerSuccess, onCreateSessionDescriptionError)
}

const stopPull = () => {
  console.log("pc2 stop pull stream");

  if (pc2) {
    pc2.close();
    pc2 = null;
  }

  remoteVideo.srcObject = null;
}

startPushBtn.addEventListener('click', startPush);
stopPushBtn.addEventListener('click', stopPush);
startPullBtn.addEventListener('click', startPull);
stopPullBtn.addEventListener('click', stopPull);