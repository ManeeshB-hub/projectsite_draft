var bar_status = true;

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

$(document).ready(function() {

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
