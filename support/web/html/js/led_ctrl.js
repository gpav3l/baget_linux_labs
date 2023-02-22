var led_list = [{gpio: "0", label: "Led 1"}, {gpio: "1", label: "Led 2"}, {gpio: "3", label: "Led 3"}, {gpio: "4", label: "Led 4"},];

/**
 * Handler called by button
 */
function btn_click(gpio) {
    var val;
    if(document.getElementById(gpio).style.background == "red") {
        document.getElementById(gpio).style.background = "green";
        val = 0;
    } else {
        document.getElementById(gpio).style.background = "red";
        val = 1;    
    }
    init_request = new XMLHttpRequest();
    init_request.open("GET", './cgi-bin/leds.py');
    init_request.send("gpio=" + gpio + "&val=" + val);    
};

/**
 * Handler, called by menu
 */
function led_handler() {
    document.getElementById("page_header").innerHTML = "Blinky page";

    led_list.forEach(function(item){
        var btn = document.createElement('button'); 
        var link = document.createTextNode(item.label);  
        btn.appendChild(link); 
        btn.id = item.gpio;
        btn.style="background: red;"
        btn.onclick= function(){btn_click(item.gpio)};
        document.getElementById("content").appendChild(btn);
    });
    
    init_request = new XMLHttpRequest();
    init_request.open("GET", './cgi-bin/leds.py');
    init_request.send("init=1");

    return "leds.py";
};
