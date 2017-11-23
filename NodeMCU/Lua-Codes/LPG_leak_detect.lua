ssid = "YOUR_WIFI_SSID"
pass = "YOUR_WIFI_PASSWORD"

wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pass)

tog=0

blink=5
pwr=7
wif=6
calib=0
buz=1

cnt=0
flag=0
thresh=90

gpio.mode(buz,gpio.OUTPUT)
gpio.write(buz,gpio.LOW)

gpio.mode(wif,gpio.OUTPUT)
gpio.write(wif,gpio.LOW)

gpio.mode(pwr,gpio.OUTPUT)
gpio.write(pwr,gpio.HIGH)

gpio.mode(blink,gpio.OUTPUT)
gpio.write(blink,gpio.LOW)

gpio.mode(calib,gpio.OUTPUT)
gpio.write(calib,gpio.LOW)

pst="GET /apps/thinghttp/send_request?api_key=YOURAPIKEY HTTP/1.1"..
"\r\nHost: api.thingspeak.com"..
"\r\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:45.0) Gecko/20100101 Firefox/45.0"..
"\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"..
"\r\nAccept-Language: en-US,en;q=0.5"..
"\r\nAccept-Encoding: gzip, deflate"..
"\r\nConnection: keep-alive"..
"\r\n\r\n"


tmr.alarm(0, 1000, tmr.ALARM_AUTO, function()
	wi=1  
	if wifi.sta.getip()==nil then 
		if cnt<4 then
			cnt=cnt+1			
		else
			wifi.sta.config(ssid,pass)
			cnt=0
		end
		gpio.write(wif,gpio.LOW)
		print('No Wifi So Far') 
		wi=0
	else
		gpio.write(wif,gpio.HIGH)
	end
	sensor=0
	for i=1,5 do 
  		sensor=sensor+adc.read(0)
	end
	sensor=sensor/5
	--print(sensor)
	if sensor>thresh then
		tmr.stop(0)
		tog=1
		flag=0
		tmr.alarm(1,500,tmr.ALARM_AUTO,function()
			if tog==1 then
				gpio.write(buz,gpio.HIGH)
				gpio.write(blink,gpio.HIGH)
			else
				gpio.write(buz,gpio.LOW)
				gpio.write(blink,gpio.LOW)
			end
			if wi==1 then
				if flag==0 then
					srv = net.createConnection(net.TCP, 0)
					srv:on("receive", function(sck, c) print("PacketReceived") flag=1 end)			
					srv:on("connection", function(sck, c) print("DomainConnected") sck:send(pst) end)
					srv:on("sent",function(sck,py) print("PacketSent") end)
					srv:connect(80,"54.88.155.198")
				end
			end
			sensor=0
			for i=1,5 do 
  				sensor=sensor+adc.read(0)
			end
			sensor=sensor/5
			if sensor<thresh then
				tog=0
				gpio.write(buz,gpio.LOW)
				gpio.write(blink,gpio.LOW)
				if wi==1 then
					if flag==1 then
						tmr.stop(1)
						tmr.start(0)
					end
				end
				if wi==0 then
					tmr.stop(1)
					tmr.start(0)
				end
			else
				if tog==0 then
					tog=1
				else
					tog=0
				end
			end	
		end)
	end
end)



