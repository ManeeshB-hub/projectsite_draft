var bar_status = true;
var msg;

client = new Paho.MQTT.Client("broker.mqttdashboard.com", Number("8000"), "clientId-Y5IcOSSr2J");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({onSuccess:onConnect});


// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("World");
  message = new Paho.MQTT.Message("on 1");
  message.destinationName = "World";
  client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
    console.log(message.destinationName)
    console.log(message.payloadString);
    if(message.destinationName==="/test"){

         x=message.payloadString;
         x=Number(x)+5
         $(".no_cars").text(x);
    }else if(message.destinationName==="/test2"){
        y=message.payloadString;
        $("#one_1").text(y);
    }

}

function toggleSidebar() {
    if (bar_status) {
        $("#mySidebar").css('width', '16vmax')
        $("#main").css('marginLeft', '20vmax')
        this.bar_status = false;
    } else {
        $("#mySidebar").css('width', '4.5vmax')
        $("#main").css('marginLeft', '5.5vmax')
        this.bar_status = true;
    }
}

function ss(event){
    var ev=event.path[1].id.split("");
    var lane=ev[1];
    var light=ev[3];

    var msgid="l"+lane+"_"+light;
    var k;
    console.log(document.getElementById(msgid).querySelector(".status").innerText);
    if(document.getElementById(msgid).querySelector(".status").innerText=="OFF"){
        k=light+"O";
        console.log(k);
        msg=new Paho.MQTT.Message(k);
    }else if(document.getElementById(msgid).querySelector(".status").innerText=="ON"){
        k=light+"F";
        console.log(k);
        msg=new Paho.MQTT.Message(k);
    }
    msg.destinationName="Lane1";
    client.send(msg);
}

$(document).ready(function() {

    // $("#l1_1").click(function(){
    //     if($(this).text=="ON"){
    //         msg=new Paho.MQTT.Message("1O");
    //     }else if($(this).text=="OFF"){
    //         msg=new Paho.MQTT.Message("1F");
    //     }
    //     msg.destinationName="lane1";
    //     client.send(msg);
    // })



    $(".status").click(function() {
        $(this).toggleClass("clicked");
        if($(this).hasClass("clicked")){
            $(this).text("OFF");
        }else{
            $(this).text("ON");
        }
    });

    function randomScalingFactor() {
        return (Math.random());
    }

    function onRefresh(chart) {
        chart.config.data.datasets[0].data.push({
            x: Date.now(),
            y: randomScalingFactor()
        });
    }

    function onRefresh2(chart) {
        chart.config.data.datasets[0].data.push({
            x: Date.now(),
            y: randomScalingFactor()
        });
    }

    var ctx = document.getElementById("sens-1").getContext('2d')
    var ctx2 = document.getElementById("sens-2").getContext('2d')

    var chart = new Chart(ctx, {
        // The type of chart we want to create
        type: 'line',

        // The data for our dataset
        data: {
            datasets: [{
                backgroundColor: '#ec250d',
                borderColor: '#ec250d',
                lineTension: 0,
                fill: false,
                // borderDash:[8,4],
                data: []
            }]
        },

        // Configuration options go here
        options: {
            // title:{
            //     display:true,
            //     text:'Charrt'
            // },

            scales: {
                xAxes: [{
                    type: 'realtime',
                    realtime: {
                        duration: 20000,
                        refresh: 1000,
                        delay: 2000,
                        onRefresh: onRefresh
                    },
                    gridLines: {
                        drawOnChartArea: true
                    }
                }],

                yAxes: [{
                    scaleLabel: {
                        display: false,
                        labelString: 'value'
                    },
                    gridLines: {
                        drawOnChartArea: true
                    }
                }]
            },
            legend: {
                display: false
            },
            tooltips: {
                mode: 'nearest',
                intersect: false
            },
            hover: {
                mode: 'nearest',
                intersect: false
            },
            maintainAspectRatio: false
        }
    });

    var chart2 = new Chart(ctx2, {
        // The type of chart we want to create
        type: 'line',

        // The data for our dataset
        data: {
            datasets: [{
                backgroundColor: '#ec250d',
                borderColor: '#ec250d',
                lineTension: 0,
                fill: false,
                // borderDash:[8,4],
                data: []
            }]
        },

        // Configuration options go here
        options: {
            // title:{
            //     display:true,
            //     text:'Charrt'
            // },

            scales: {
                xAxes: [{
                    type: 'realtime',
                    realtime: {
                        duration: 20000,
                        refresh: 1000,
                        delay: 2000,
                        onRefresh: onRefresh
                    },
                    gridLines: {
                        drawOnChartArea: true
                    }
                }],

                yAxes: [{
                    scaleLabel: {
                        display: false,
                        labelString: 'value'
                    },
                    gridLines: {
                        drawOnChartArea: true
                    }
                }]
            },
            legend: {
                display: false
            },
            tooltips: {
                mode: 'nearest',
                intersect: false
            },
            hover: {
                mode: 'nearest',
                intersect: false
            },
            maintainAspectRatio: false
        }
    });

})
