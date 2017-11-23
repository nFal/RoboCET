ssid="YOUR_WIFI_SSID"
pass = "YOUR_WIFI_PASSWORD"
broker_ip="YOR_BROKER_IP"
broker_port=1883
client_id="nodemcu"

tog=0
ledpin=8
gpio.mode(ledpin,gpio.OUTPUT)
wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pass)

tmr.alarm(0, 1000, 1, function()
   if wifi.sta.getip() == nil then
      print("Connecting to AP...\n")
   else
      ip, nm, gw=wifi.sta.getip()
      print("IP Address: ",ip)
      tmr.stop(0)
		mqtt_conf()
   end
end)

function mqtt_conf()
	m = mqtt.Client(client_id, 120)
	tmr.alarm(0, 2000, 1, function()
		print("connecting to broker...")
		m:connect(broker_ip, broker_port, 0, function(client)
		print("connected to broker") 
		tmr.stop(0)
		mqtt_run()		
		end, function(client, reason) 
		print("connect to broker failed reason: "..reason) 
		tmr.stop(0)
		end)
	end)
end

function mqtt_run()
	m:on("offline", function(client) print ("offline") end)
	m:on("message", function(client, topic, data) 
		if tog==0 then
			gpio.write(ledpin, gpio.HIGH)
			tog=1
		else
			gpio.write(ledpin,gpio.LOW)
			tog=0
		end  		
	end)
	m:subscribe("led",0, function(client) print("subscribe success") end)
end

