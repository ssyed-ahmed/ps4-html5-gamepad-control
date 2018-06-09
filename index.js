const express = require('express')
const app = express()
const http = require('http').Server(app)
const io = require('socket.io')(http)

// Listen to web GET requests with the index.html file
app.get('/', (request, response) => {
  response.sendFile(__dirname + '/index.html')
})

io.on('connection', (socket) => {
  console.log('A user connected');
})

http.listen(3000, () => {
  console.log('listening on port 3000');
})
