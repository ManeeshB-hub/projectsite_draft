var bar_status=true;

function toggleSidebar(){
    if(bar_status){
        $("#mySidebar").css('width','16vmax')
        $("#main").css('marginLeft','16vmax')
        this.bar_status=false;
    }else{
        $("#mySidebar").css('width','4.5vmax')
        $("#main").css('marginLeft','4.5vmax')
        this.bar_status=true;
    }
}
