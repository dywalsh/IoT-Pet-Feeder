// Customize for your thingsboard instance
var TB_ADDRESS = "192.168.137.226"
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
var TB_TOKEN = "eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJqb2UuaXMub2hhcmFAZ21haWwuY29tIiwic2NvcGVzIjpbIlRFTkFOVF9BRE1JTiJdLCJ1c2VySWQiOiIyOGIwZGI1MC1lNGRiLTExZTgtOTEzYi0wZDNiMzY3YWY1N2MiLCJmaXJzdE5hbWUiOiJKb2UiLCJsYXN0TmFtZSI6Ik8nSGFyYSIsImVuYWJsZWQiOnRydWUsImlzUHVibGljIjpmYWxzZSwidGVuYW50SWQiOiJkMDgyZGU3MC1lMWMzLTExZTgtYTM1MS05NzYwYjNhZDk0NjUiLCJjdXN0b21lcklkIjoiMTM4MTQwMDAtMWRkMi0xMWIyLTgwODAtODA4MDgwODA4MDgwIiwiaXNzIjoidGhpbmdzYm9hcmQuaW8iLCJpYXQiOjE1NDI5OTI3MjIsImV4cCI6MTU1MTk5MjcyMn0.EQ9_LThS0LAxUZDyx1JSqbSWtlMAzD9MfjxYiYaBBB3vK5jWi6RUe-QX3Di_RFmPibVkO-uhX1_q1Ep8UrIPJg";

// Create an array of thingsboard DEVICE IDs corresponding to your nRF52-DKs
// You can obtain these using COPY DEVICE ID in the thingsboard web UI
var DEVICE_IDS = [
    "c2039fe0-e23d-11e8-97c1-55cfd1a5b57a"
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
        "params" : time
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
