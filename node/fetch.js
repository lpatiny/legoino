
var port="/dev/tty.SLAB_USBtoUART";
var i=0;

var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort(port, {
  baudrate: 38400
}, true); // this is the openImmediately flag [default is true]

var buffer="";
serialPort.open(function (error) {
  if ( error ) {
    console.log('failed to open: '+error);
  } else {
    console.log('The connection is open');
    // we add a listener when data are received
    serialPort.on('data', function(data) {
	buffer+=data.toString();

	var lines=buffer.split(/[\r\n]+/);
	buffer=lines[lines.length-1];
	processLines(lines.slice(0,lines.length-1));
    });
  }
});

function processLines(lines) {
	for (var i=0; i<lines.length; i++) {
		var line=lines[i];
		processStatusLine(line);
	}
}

function processStatusLine(statusLine) {
	// this line contains the 26 parameters as well as the check digit. We should
	// only consider the line if the check digit is ok
	
}

var delay=1000;	// delay in ms
var sendEvent=function() {
    serialPort.write("c\n", function(err, results) {
	console.log(i++);
	if (err) {
		console.log('err ' + err);
		console.log('Write results ' + results);
	}
    });
}

setInterval(sendEvent, delay);


