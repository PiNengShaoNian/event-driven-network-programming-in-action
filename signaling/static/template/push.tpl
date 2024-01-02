<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <title>1v1屏幕共享-推流端</title>
</head>

<body>
    <h3>1v1屏幕共享-推流端</h3>
    <div>
        推流端基本信息
        <span>
            uid={{.uid}}
            streamName={{.streamName}}
            audio={{.audio}}
            video={{.video}}
        </span>
    </div>
    <div>
        <video id="localVideo" controls autoplay></video>
    </div>
    <button id="pushBtn">开始推流</button>
    <button id="stopPushBtn">停止推流</button>
</body>

</html>