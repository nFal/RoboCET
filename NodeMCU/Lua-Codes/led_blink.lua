led_pin=8
count=0
gpio.mode(led_pin,gpio.OUTPUT)

while count<10 do
gpio.write(led_pin, gpio.HIGH)
tmr.delay(500000)
gpio.write(led_pin, gpio.LOW)
tmr.delay(500000)
count=count+1
end
