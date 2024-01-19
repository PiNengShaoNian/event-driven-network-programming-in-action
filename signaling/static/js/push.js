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
      console.log("push response: " + JSON.stringify(data))
      if (textStatus === "success" && data.errNo == 0) {
        $("#tips1").html('<span style="color:blue">推流请求成功!</span>')
      } else {
        $("#tips1").html('<span style="color:red">推流请求失败!</span>')
      }
    },
    "json");
}

pushBtn.addEventListener("click", startPush);