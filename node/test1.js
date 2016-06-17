// npm install sleep-async

var ws = require('websocket.io');
var server = ws.listen(8126);
 
server.on('connection', function(socket) {
        console.log('Connection started');
        console.log(socket.constructor);

		var sleep = require('sleep-async')();
 
        socket.on('message', function(data) {
                console.log('Message received:' + data);
 
                server.clients.forEach(function(client) {
                        client && client.send(data);
                });
        });
});