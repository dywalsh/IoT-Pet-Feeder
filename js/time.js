// Customize for your thingsboard instance
var TB_ADDRESS = "127.0.0.1"
var TB_PORT = 8080
var INTERVAL = 10000
//
// You need to replace `token` below with a JWT_TOKEN obtained from your
// thingsboard instance. Follow the instructions at the URL below, specifically
// the command at the end of the page beginning `curl -X POST ...`, which you
// must modify as appropriate (thingsboard IP address in particular):
//
//   https://thingsboard.io/docs/reference/rest-api/
//
var TB_TOKEN = "eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJ2dWh1QHRjZC5pZSIsInNjb3BlcyI6WyJURU5BTlRfQURNSU4iXSwidXNlcklkIjoiMjlkNWRmMTAtZTI4NS0xMWU4LWEwYjUtMDFjMGJmMDNhNWI4IiwiZW5hYmxlZCI6dHJ1ZSwiaXNQdWJsaWMiOmZhbHNlLCJ0ZW5hbnRJZCI6IjBmNTI0ZGUwLWUyODUtMTFlOC1hMGI1LTAxYzBiZjAzYTViOCIsImN1c3RvbWVySWQiOiIxMzgxNDAwMC0xZGQyLTExYjItODA4MC04MDgwODA4MDgwODAiLCJpc3MiOiJ0aGluZ3Nib2FyZC5pbyIsImlhdCI6MTU0MzA3NDg2OCwiZXhwIjoxNTUyMDc0ODY4fQ.i6lkU0zTIUvIDsKvbr-0EHEmhLsiGBNHzkRcvucOC2bxC_JonnzIHxDu_OHO3JSdGpiBkKQgKb7amUQHVkvKUA";

// Create an array of thingsboard DEVICE IDs corresponding to your nRF52-DKs
// You can obtain these using COPY DEVICE ID in the thingsboard web UI
var DEVICE_IDS = [
    "f05cdc40-e287-11e8-a0b5-01c0bf03a5b8"
];

// You might want to declare some constants to make it easier to identify
// your devices
var MY_BTN_DEVICE = 0;
var MY_LED_DEVICE = 0;

// Send the provided time to the device
function sendTime(deviceId, time) {
	console.log("Sending time " + time + " to device: " + deviceId)
    // Use the server-side device RPC API to cause thingsboard to issue a device
    // RPC to a device that we identify by `buttonEntityId`
    // See: https://thingsboard.io/docs/user-guide/rpc/

    var request = require("request");
    var url = "http://" + TB_ADDRESS+":" + TB_PORT + "/api/plugins/rpc/oneway/" + deviceId;

    // The JSON RPC description must match that expected in tb_pubsub.c
    var req = {
        "method" : "time",
        "params" : {
            "time" : time,
            "s1" : 0932,
            "s2" : 1456,
            "s3" : 1942
        }
    };

    console.log("RPC Request: " + url + ": " + JSON.stringify(req));

    // Issue the HTTP POST request
    request({
        url: url,
        method: "POST",
        json: req,
        headers: {
            "X-Authorization": "Bearer " + TB_TOKEN,
            // Note the error in the TB docs: `Bearer` is missing from
            // `X-Authorization`, causing a 401 error response
        }
    }, function (error, response, body) {
        if (!error && response.statusCode === 200) {
            console.log("OK" + ((typeof body != 'undefined') ? ": " + body : ""));
        }
        else {
            console.log("error: " + error)
            console.log("response.statusCode: " + response.statusCode)
            console.log("response.statusText: " + response.statusText)
        }
    });
}

function sendTimeToDevices() {
  console.log('Sending time to devices...');
  var time = Math.round((new Date()).getTime() / 1000);

  DEVICE_IDS.forEach(function(deviceId){
  	sendTime(deviceId, time);
  })

}

setInterval(sendTimeToDevices, INTERVAL);
