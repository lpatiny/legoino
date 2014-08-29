
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

function processStatusLine(line) {
	// this line contains the 26 parameters as well as the check digit. We should
	// only consider the line if the check digit is ok
  console.log(line);
  var entry={};
  if (line.length!=26*4+2) {
    console.log("Not correct length: "+line);
  } else {
    if (checkDigit(line)) {
      for (var j=0; j<26; j++) {
        var value=convertSignedIntHexa(line.substring((j*4),4+(j*4)));
        if (value==-32768) value=null;
        entry[String.fromCharCode(65+j)]=value;
      }
      //  entry.mac=line.substring(128,132);
    } else {
      console.log("Check digit error: "+line);
    }
  }
  console.log(entry);

  function checkDigit(line) {
    var checkDigit=0;
    for (var i=0; i<line.length; i=i+2) {
      checkDigit^=parseInt("0x"+line[i]+line[i+1]);
    }
    if (checkDigit==0) return true;
    return false;
  }

  function convertSignedIntHexa(hexa) {
    var value=parseInt("0x"+hexa);
    if (value>32767) {
      return (65536-value)*-1;
    } 
    return value;
  }
}

var delay=250;	// delay in ms
var sendEvent=function() {
    serialPort.write("$Ac\n", function(err, results) {
	console.log(i++);
	if (err) {
		console.log('err ' + err);
		console.log('Write results ' + results);
	}
    });
}

setInterval(sendEvent, delay);


