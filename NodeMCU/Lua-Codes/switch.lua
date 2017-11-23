switch=6
led=8
tog=0

gpio.mode(led,gpio.OUTPUT)
gpio.mode(switch,gpio.INT) 
gpio.write(led, gpio.LOW)

function callback(level,when)
	tmr.delay(50000)
	if tog==0 then	
		gpio.write(led, gpio.HIGH)
		tog=1
		print("high")
	else
		gpio.write(led, gpio.LOW)
		tog=0
		print("low")
	end
end
gpio.trig(switch,"up",callback)
	
