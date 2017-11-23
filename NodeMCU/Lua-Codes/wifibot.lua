ssid="YOUR_WIFI_SSID"
pwd="YOUR_WIFI_PASSWORD"

wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pass)

 tmr.alarm(0, 1000, 1, function()
   if wifi.sta.getip() == nil then       
      print("Connecting to AP...\n")
   else
      ip, nm, gw=wifi.sta.getip()
      print("IP Info: \nIP Address: ",ip)
      print("Netmask: ",nm)
      print("Gateway Addr: ",gw,'\n')
      tmr.stop(0)
   end
end)

ts=[[<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
 <title>ROBO</title>
</head>
<body>
<h1 style="text-align:center;color:darkorchid">WIFI_BOT</h1>
<p id="res"></p>
<script>
 var req;
 var data = {d: 'N',old:'N' };
 if (window.DeviceOrientationEvent == undefined) { 
 console.log("no accelerometer"); 
} else {
 console.log("accelerometer found");
 window.addEventListener("deviceorientation", accelerometerUpdate, true);}
function accelerometerUpdate(e) {
 var large = Math.abs(e.gamma) >= Math.abs(e.beta) ? e.gamma : e.beta;
 switch (large) {
 case 0:
  data.d = 'N'
  break;
 case e.beta:
  if (Math.abs(e.beta) > 10) {
   if (large > 0)
 data.d = 'B';
   else  data.d = 'F';} else {data.d = 'N';}
   break;
 case e.gamma:
  if (Math.abs(e.gamma) > 10) {
   if (large > 0) data.d = 'R';
   else data.d = 'L';
  } else data.d = 'N';
 break;
   }
   document.getElementById('res').innerHTML = '<h1 style ="font-size : 100px ;color:red;text-align:center">' + data.d + '</h1>';
   if(data.d != data.old){
 data.old = data.d;
 makeRequest();
}}
  function makeRequest() {
   var request = new XMLHttpRequest();
   request.open('POST', '', true);
   request.setRequestHeader('X-Requested-With', 'XMLHttpRequest'); 
   request.send("data="+data.d);
  }
 </script>
</body>
</html>
]]
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    i,j=string.find(payload,"data=")
    if i~=nil then 
           rcvd=string.sub(payload,j+1,j+1)
    print(rcvd) 
    if rcvd=='R' then
    gpio.write(0,gpio.HIGH)
    gpio.write(1,gpio.LOW)
    gpio.write(2,gpio.LOW)
    gpio.write(3,gpio.HIGH)
    elseif rcvd=='B' then
    gpio.write(0,gpio.LOW)
    gpio.write(1,gpio.HIGH)
    gpio.write(2,gpio.LOW)
    gpio.write(3,gpio.HIGH)
    elseif rcvd=='F' then
    gpio.write(0,gpio.HIGH)
    gpio.write(1,gpio.LOW)
    gpio.write(2,gpio.HIGH)
    gpio.write(3,gpio.LOW)
    elseif rcvd=='L' then
    gpio.write(0,gpio.LOW)
    gpio.write(1,gpio.HIGH)
    gpio.write(2,gpio.HIGH)
    gpio.write(3,gpio.LOW)
    else
    gpio.write(0,gpio.HIGH)
    gpio.write(1,gpio.HIGH)
    gpio.write(2,gpio.HIGH)
    gpio.write(3,gpio.HIGH)
    end
    end
    conn:send(ts)
  end)
  conn:on("sent",function(conn) conn:close() end)
end)
