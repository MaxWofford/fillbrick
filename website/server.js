var server = require('http').createServer(),
		express = require('express'),
		app = express(),
		port = 80;
var app = express();

app.set('view engine', 'ejs');
app.use(express.static('static'));

app.get('/', function(req, res) {
    res.render('drawImage');
});

server.on('request', app);
server.listen(port, function () { console.log('Listening on ' + server.address().port) });
