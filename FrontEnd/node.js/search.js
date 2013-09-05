var http = require('http'),
    querystring = require('querystring');

function search() {

    var options = {
      hostname: '10.8.33.86',
     // path: '/phones/phone.cfm?',
      path: '/phones/phone.cfm?ShowName=yes',
      method: 'PUT'
      //headers: {
        //Connection: 'keep-alive',
        //Accept: 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        //Origin: 'http://10.8.33.86',
        //Referer: 'http://10.8.33.86/phones/phone.cfm?CFID=3304492&CFTOKEN=94824512'
     // }
    };
    

    console.log('http.request');
    var req = http.request(options, function(res) {
        var resData = "";
        console.log("statusCode: ", res.statusCode);
        res.on('data', function (chunk){
            console.log('res.on');
            resData += chunk;
            console.log(querystring.parse(resData));
        });

        req.on('end', function(e) {
            console.log('req.end');
            console.log(querystring.parse(resData));
        });
                
        });

   req.on('error', function (e) {
        console.log('problem with request: ' + e.message)
        });

    var contents =  querystring.stringify({
       name: 'fei',
        submit: 'go'
    });
    req.write(contents);
    req.end();

}

search();
