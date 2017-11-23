ssid="YOUR_WIFI_SSID"
pwd="YOUR_WIFI_PASSWORD"
wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pwd)

hdr="HTTP/1.1 200 OK"..
"\r\nContent-Type: text/html"..
"\r\nConnection: Closed"..
"\r\n\r\n"

html="<p style=\"text-align: center;\"><span style=\"text-align: center;"..
"color: #0000ff;\">"..
"<strong>Hello from NodeMCU</strong></span></p>"

resp=hdr..html

tmr.alarm(0, 1000, 1, function()
   if wifi.sta.getip() == nil then
      print("Connecting to AP...\n")
   else
      ip=wifi.sta.getip()
      print("IP Address: ",ip)
      tmr.stop(0)
   end
end)

sv = net.createServer(net.TCP,80)

function receiver(sck, data)
  print(data)
  sck:close()
end

if sv then
  sv:listen(80, function(conn)
    conn:on("receive", receiver)
    conn:send(resp)
  end)
end
