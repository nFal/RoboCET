ssid="YOUR_WIFI_SSID"
pwd="YOUR_WIFI_PASSWORD"

wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pwd)


function conct()
    if wifi.sta.getip() == nil then
      print("Connecting to AP...\n")
   else
      ip=wifi.sta.getip()
      print("IP Address: ",ip)      
      tmr.stop(0)
   end
end

tmr.alarm(0, 1000, 1,conct)

