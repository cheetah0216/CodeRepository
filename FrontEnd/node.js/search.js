var http = require('http'),
    querystring = require('querystring');

function search() {
  var url = "http://10.8.33.86/phones/phone.cfm?ShowName=yes&name=fei&submit=go";
  var req = http.get(url, function(res) {
    console.log('STATUS: ' + res.statusCode);
    console.log('HEADERS: ' + JSON.stringify(res.headers));
    res.setEncoding('utf8');
    res.on('data', function (chunk) {
      console.log('BODY: ' + chunk);
    });
  });
  req.on('error',function(e) {
    console.log("Got error: " + e.message);
  });
}
search();
