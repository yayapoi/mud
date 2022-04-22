# mud
mud client for for mud server, example: pkuxkx,   address: mud.pkuxkx.net   port:8081

## mud-client是什么?
本源码使用了 GPL-3.0。GPL-3.0。GPL-3.0。
只是一个使用 QT 制作的 mud client。

## mud-client功能?
本源码只制作了简单的架构，开启mccp2，接收与发送消息，组装消息，将消息过滤给各个窗口、剩下消息显示于界面，将消息匹配触发，通过TcpSocket将触发的消息以指定格式传输给用户。
而用户可以使用任何开发语言，只用通过TcpSocket来同此软件通信。
