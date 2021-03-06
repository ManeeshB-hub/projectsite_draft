var bar_status = true;
var msg;
var x,y;
client = new Paho.MQTT.Client("broker.mqttdashboard.com", Number("8000"), "clientId-9UVbR10rzw");

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
  client.subscribe("/Sensors");
  client.subscribe("/Cars");
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
    if(message.destinationName==="/Sensors"){

        var sensorJSON=JSON.parse(message.payloadString);
        x=Number(sensorJSON.ldr1);

        y=Number(sensorJSON.ldr2);


    }
    else if(message.destinationName=="/Cars"){
        var no_cars=(message.payloadString.split(""));
        console.log(no_cars[2]);
        document.getElementById("cars").innerText=no_cars[2];
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
    var topic=String(event.target.baseURI);

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
    if(topic.includes("lane1")){
        msg.destinationName="/Lane1";
    }else if(topic.includes("lane2")){
        msg.destinationName="/Lane2";
    }
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

    function sensdata1(){
        return x;
    }

    function sensdata2(){
        return y;
    }

    function onRefresh(chart) {
        chart.config.data.datasets[0].data.push({
            x: Date.now(),
            y: sensdata1()
        });
    }

    function onRefresh2(chart) {
        chart.config.data.datasets[0].data.push({
            x: Date.now(),
            y: sensdata2()
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
                        onRefresh: onRefresh2
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
