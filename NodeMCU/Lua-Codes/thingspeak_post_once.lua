ssid="YOUR_WIFI_SSID"
pwd="YOUR_WIFI_PASSWORD"
wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pwd)

flag=0
apikey="YOUR_THINGSPEAK_API_KEY"
data="123"
url="/update?api_key="..apikey.."&field1="..data


pst="GET "..url.." HTTP/1.1"..
"\r\nHost: api.thingspeak.com"..
"\r\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:45.0) Gecko/20100101 Firefox/45.0"..
"\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"..
"\r\nAccept-Language: en-US,en;q=0.5"..
"\r\nAccept-Encoding: gzip, deflate"..
"\r\nConnection: keep-alive"..
"\r\n\r\n"


tmr.alarm(0, 1000, 1, function()
   if wifi.sta.getip() == nil then
      print("Connecting to AP...\n")
   else
		cli = net.createConnection(net.TCP, 0)
		cli:on("receive", function(sck, c) print("PacketReceived") end)				
		cli:on("connection", function(sck, c) print("DomainConnected") sck:send(pst) end)
		cli:on("sent",function(sck,py) print("PacketSent") flag=1 end)
		cli:connect(80,"52.7.7.190")
		if flag==1 then    
			tmr.stop(0)
		end
   end
end)







