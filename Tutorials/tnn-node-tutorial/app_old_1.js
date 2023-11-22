var http = require('http');
var fs = require('fs');

var server = http.createServer(function(req,res) {
  console.log('request was made: ' + req.url);
  if(req.url === '/home' || req.url === '/') {
    res.writeHead(200, {'Content-Type': 'text/html'});
    fs.createReadStream(__dirname + '/index.html').pipe(res);
  } else if(req.url === '/contact-us') {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    fs.createReadStream(__dirname + '/contact.html').pipe(res);
  } else if(req.url === '/api/ninjas'){
    var ninjas = [{name: 'jukka', age: 27}, {name: 'kati', age: 27}];
    res.writeHead(200, {'Content-Type': 'application/json'});
    res.end(JSON.stringify(ninjas));
  } else {
    res.writeHead(404, {'Content-Type': 'text/html'});
    fs.createReadStream(__dirname + '/404.html').pipe(res);
  }

});

server.listen(3000, '127.0.0.1');
console.log('listening at 127.0.0.1:3000');
