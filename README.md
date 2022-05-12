# LAN-Pong
A LAN Pong Game made with Qt and sockets.

<p align="center">
<img width=400 src="https://github.com/luisaras/LAN-Pong/blob/master/client.jpg?raw=true">
</p>

## How To Run

* Enter PongServer directory and execute ```make ; ./main```;
* Install Qt Creator;
* Open PongClient's project file;
* Build and Run two client windows and connect to the server.

To run on different PCs, change the "127.0.0.1" inside the function ```connectToServer``` in the ```PongClient/mainwindow.cpp``` file to the LAN IP of the PC hosting the server.
