const sleep = ms => new Promise(res => setTimeout(res, ms));

function get_hw_info(){
      active_request = new XMLHttpRequest();
      active_request.onload = function() {
        if(cur_handler != "hw_handler") return;
        resp = JSON.parse(active_request.response);
        if(resp.length != 0) {
          msg = "<table>";
          resp.forEach(function(item){
            msg += "<tr><th>" + item.label + "</th><td>" + item.value + "</td></tr>"
          });
          msg += "</table>";
          document.getElementById("content").innerHTML = msg;
        } else {
          console.log("No response");
        }
        sleep(250).then(() => {get_hw_info(); });
      }
      active_request.open("GET", './cgi-bin/hw.py');
      active_request.send();
};


function hw_handler() {
    document.getElementById("page_header").innerHTML = "Why so hot is here?";
    get_hw_info();
}
