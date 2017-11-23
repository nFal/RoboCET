led_pin=8

duty=0
clock=500

while duty<1000 do
pwm.setup(led_pin,clock,duty)
pwm.start(led_pin)
tmr.delay(25000)
duty=duty+5
end
