var bar_status=true;

function toggleSidebar(){
    if(bar_status){
        $("#mySidebar").css('width','15vw')
        $("#main").css('marginLeft','15vw')
        this.bar_status=false;
    }else{
        $("#mySidebar").css('width','5vw')
        $("#main").css('marginLeft','5vw')
        this.bar_status=true;
    }
}
