const socket = io("http://localhost:5000");
const messageContainer = document.getElementById("message-container");
const messageForm = document.getElementById("send-container");
const messageInput = document.getElementById("message-input");

const namePrompt = prompt("what is your name?");
appendMessage("You joined");
socket.emit("new-user", namePrompt);

socket.on("chat-message", data => {
  appendMessage(`${data.name}: ${data.message}`);
});

socket.on("user-connected", name => {
  appendMessage(`${name} connected`);
})

socket.on("user-disconnected", name => {
  appendMessage(`${name} disconnected`);
})

messageForm.addEventListener("submit", e => {
  e.preventDefault();
  const msg =messageInput.value;
  appendMessage(`You: ${msg}`);
  socket.emit("send-chat-message", msg);
  messageInput.value = "";
});

function appendMessage(message) {
  const messageELemtn = document.createElement("div");
  messageELemtn.innerText = message;
  messageContainer.append(messageELemtn);
}