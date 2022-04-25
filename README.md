# mud
mud client for for mud server, example: pkuxkx,   address: mud.pkuxkx.net   port:8081

## mud-client是什么?
本源码使用了 GPL-3.0。GPL-3.0。GPL-3.0。
只是一个使用 QT 制作的 mud client。

## mud-client功能?
本源码只制作了简单的架构，开启mccp2，接收与发送消息，组装消息，将消息过滤给各个窗口、剩下消息显示于界面，将消息匹配触发，通过TcpSocket将触发的消息以指定格式传输给用户。
而用户可以使用任何开发语言，只用通过TcpSocket来同此软件通信。

## 源码依赖
1、QT 5.14.2 - 6.3.0
2、zlib 128 - 1212

## 源码使用
1、下载zlib 源码
2、编译zlib
3、下载mud-client源码
4、拷贝zlib的 zconf.h  zlib.h libzlib.dll 至mud-client目录
5、使用QT打开pro文件，修改 pro 中关于 zlib 的部分
6、qt build

## 功能
1、tcpSocket连接mud server;
2、使用 mccp2 同mud server 通信；
3、使用正则表达式将消息组装
4、使用 qTextEdit 显示消息

## 软件架构
请看 mud-client.png

## 下载链接
https://github.com/yayapoi/mud
