const express = require('express')
const app = express()
const server = require('http').createServer(app).listen(3000, () => {
  console.log('Example app listening on port 3000')
})

// Listen to web GET requests with the index.html file
app.get('/', (request, response) => {
  response.sendFile(__dirname + '/index.html')
})
