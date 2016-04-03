var server = require('http').createServer(),
		express = require('express'),
		app = express(),
		port = 80;
var app = express();
const CHARACTER_SIZE = 4;
var data = {bytes:[7,1,13,1,1,13,1,7,0,0,0,0,"Jackie"], length:0};
for(var i=0;i<data.bytes.length;i++)
	data.length += parseInt(data.bytes[i])===data.bytes[i] ? 1 : data.bytes[i].length*CHARACTER_SIZE;

app.set('view engine', 'ejs');
app.use(express.static('static'));

app.get('/', function(req, res) {
    res.render('drawImage');
});

app.get('/data', function(req, res) {
	res.setHeader('Content-Type', 'application/json');
    res.send(JSON.stringify(data));
});

server.on('request', app);
server.listen(port, function () { console.log('Listening on ' + server.address().port) });
