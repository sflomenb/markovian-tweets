var express = require('express');
var app = express();
var bodyParser = require('body-parser');

// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.static('public'));

app.get('/', function(req, res) {
    res.sendFile(__dirname + "/public" + "index.html");
});


var Twitter = require('twitter');

var client = new Twitter({
    consumer_key: 'wqeRQRwLtFgDClSd59v94N9YG',
    consumer_secret: 'MK36z2C2R1sUBrBiF3fgil5J5e8oO5JqkVrmjLiUtVt6zKF9YJ',
    access_token_key: '494344455-QwyHE3jX6fVFbW9UAXEtgiLZXyoLLBJJWLKTtAsp',
    access_token_secret: 'YjdT5BiFbOJaq9S92PXAC98NxAF20PgbndcID1Ky0KLuH'
});

var params = {
    screen_name: 'BillGates'
};



app.get('/tweet/:account_id', function(req, res) {
    var params = {
        screen_name: req.params.account_id
    };

    console.log(params.screen_name);
    client.get('statuses/user_timeline', params, function(error, tweets, response) {
        if (!error) {
            var usertweet = "";
            JSON.stringify(tweets);
            for (var i = 0; i < tweets.length; i++) {
                // console.log(tweets[i].text);
                usertweet += tweets[i].text;

            }
            res.send(usertweet);
        }
        else{
        	res.send("no such user");
        }
    });
})

var server = app.listen(process.env.PORT || 3000, function() {
    var host = server.address.address;
    var port = server.address.port;
    console.log("app is listening at http://%s:%s", host, port);

})
