var server = require('http').createServer(),
		express = require('express'),
		app = express(),
		port = 80;
var app = express();
var data = {bytes:[7,1,13,1,1,13,1,7], length:8}

app.set('view engine', 'ejs');
app.use(express.static('static'));

app.get('/', function(req, res) {
    res.render('drawImage');
});

app.get('/data', function(req, res) {
    res.send(JSON.stringify(data));
});

server.on('request', app);
server.listen(port, function () { console.log('Listening on ' + server.address().port) });
