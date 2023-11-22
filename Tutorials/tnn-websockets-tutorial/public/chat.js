var socket = io.connect('http://localhost:3000');

var message = document.getElementById("message");
var handle = document.getElementById("handle");
var send = document.getElementById("send");
var output = document.getElementById("output");
var feedback = document.getElementById("feedback");

send.addEventListener('click', function(){
  socket.emit('chat', {
    message: message.value,
    handle: handle.value
  });
});

message.addEventListener('keypress', function() {
  socket.emit('typing', handle.value);
})

socket.on('chat', function(data){
  output.innerHTML += "<p>" + data.handle + ": " + data.message + "</p>";
  feedback.innerHTML = "";
});

socket.on('typing', function (data) {
  feedback.innerHTML = "<p>" + data + " is typing..</p>";
});