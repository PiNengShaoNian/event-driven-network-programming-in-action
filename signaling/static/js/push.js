'use strict';

const pushBtn = document.getElementById("pushBtn");

const uid = $("#uid").val();
const streamName = $("#streamName").val();
const video = $("#video").val();
const audio = $("#audio").val();


const startPush = () => {
  console.log("send push: /signaling/push");

  $.post("/signaling/push",
    {
      uid,
      streamName,
      video,
      audio,
    },
    (data, textStatus) => {
      
    },
    "json");
}

pushBtn.addEventListener("click", startPush);