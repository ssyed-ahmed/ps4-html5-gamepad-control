const express = require('express')
const app = express()
const http = require('http').Server(app)
const io = require('socket.io')(http)
var serialPort = require('serialport')

// Listen to web GET requests with the index.html file
app.get('/', (request, response) => {
  response.sendFile(__dirname + '/index.html')
})

// open the USB serial port
var myPort = new serialPort("COM3", {
	baudRate: 9600,
    // look for return and newline at the end of each data packet
    parser: new serialPort.parsers.Readline("\r\n")
})

myPort.on('open', () => {
  console.log('serial port opened')
})

myPort.on('data', (data) => {
  console.log('Serial data: ' + data)
})

io.on('connection', (socket) => {
  console.log('A user connected');
  socket.on('message', (data) => {
    // Data sent from the browser
    //console.log(data)

    myPort.write(data, (err) => {
      if (err) {
        return console.log('Error on write: ', err.message)
      }
      console.log('serial port message written')
    })

    myPort.on('error', (err) => {
      console.log('Error: ', err.message)
    })
  })
})

http.listen(3000, () => {
  console.log('listening on port 3000')
})
