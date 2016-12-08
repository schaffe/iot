config = require("config")  

open = true

gpio.mode(config.DRIVER_A1, gpio.OUTPUT)
gpio.mode(config.DRIVER_A2, gpio.OUTPUT)

gpio.mode(6, gpio.OUTPUT)
gpio.write(6, gpio.LOW)
--gpio.write(config.DRIVER_A2, gpio.HIGH)

