var mainApp = angular.module('mainApp', []);

mainApp.controller("mainController", mainController);
mainController.$injec = ["$scope", "$http"]

function mainController($scope, $http) {
    $scope.usertweet = "";
    $scope.accountID;
    $scope.getTweet = function(accountID) {
        $scope.accountID = accountID;
        $http({
            // url: "http://localhost:3000/tweet/" + accountID,
            url: "https://cpeg476-markov-sflomenb.c9users.io/tweet/" + accountID,
            method: "GET",
            // data: { account_id: '1' }
        }).then(function(data, status, headers, config) {
            $scope.usertweet = data.data;
            console.log($scope.usertweet);
            console.log("connected");

 
            var array = tokenizeString($scope.usertweet);
            var frequencyTable = buildFrequencyTable(array);
            var startWord = getStartWord(array);
            $scope.markovTweet = generate(frequencyTable, startWord);

        }, function(response) {
            console.log("fucked");
        });


    };
    var tokenizeString = function(string) {
        var arrayofString = string.split(/[ ,.!]+/).filter(Boolean);
        return arrayofString;
    };
    var buildFrequencyTable = function(arrayofString) {
        var map = {

        };
        for (var i = 0; i < arrayofString.length; i++) {
            if (arrayofString[i] in map) {
                map[arrayofString[i]].push(arrayofString[i + 1]);
            } else {
                map[arrayofString[i]] = [arrayofString[i + 1]];
            }
        }
        return map;
    };

    var getStartWord = function(arrayofString) {
        return arrayofString[Math.floor(Math.random() * (arrayofString.length))];
    };
    var generate = function(frequencyTable, startWord) {
        var length = Object.keys(frequencyTable).length;
        console.log("length is: ", length);
        var markovTweet = startWord;

        for (var i = 0; i < length; i++) {
            if (startWord in frequencyTable) {
                var followWord = frequencyTable[startWord];
                var randomInt = Math.floor(Math.random() * (followWord.length));

                startWord = followWord[randomInt];
                if (startWord === undefined) {
                    break;
                }
                markovTweet += " " + startWord + " ";
                if(markovTweet.length >= 140){
                    return markovTweet;
                }
            }
        }
        return markovTweet;
    };
};
