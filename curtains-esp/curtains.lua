local module = {}

function module.start()
    app.publish("Curtains app started")
    print("Setting up interrupts at Open sensor on port " .. config.PIN_OPEN)
    gpio.mode(config.PIN_OPEN, gpio.INT)
    gpio.mode(config.PIN_CLOSE, gpio.INT)
    gpio.mode(config.DRIVER_A1, gpio.OUTPUT)
    gpio.mode(config.DRIVER_A2, gpio.OUTPUT)
end

function stopDrive()
    gpio.write(config.DRIVER_A1, gpio.LOW)
    gpio.write(config.DRIVER_A2, gpio.LOW)
end

function onOpen()
    gpio.trig(config.PIN_OPEN, "none")
    gpio.write(config.PIN_OPEN, gpio.HIGH)
    stopDrive()
    tmr.unregister(config.TIMER_CURT)
    app.publish("Open")
    --module.close()
end

function onClose()
    gpio.trig(config.PIN_CLOSE, "none")
    gpio.write(config.PIN_CLOSE, gpio.HIGH)
    stopDrive()
    tmr.unregister(config.TIMER_CURT)
    app.publish("Close")
    --module.open()
end

function module.close()
    app.publish("Closing...")
    gpio.write(config.DRIVER_A1, gpio.HIGH)
    gpio.write(config.DRIVER_A2, gpio.LOW)
    
    gpio.write(config.PIN_CLOSE, gpio.HIGH)
    tmr.alarm(config.TIMER_CURT, config.DEFAULT_TIMEOUT, tmr.ALARM_SINGLE, onClose)
    gpio.trig(config.PIN_CLOSE, "low", onClose)
end

function module.open()
    app.publish("Opening...")
    gpio.write(config.DRIVER_A1, gpio.LOW)
    gpio.write(config.DRIVER_A2, gpio.HIGH)
    tmr.alarm(config.TIMER_CURT, config.DEFAULT_TIMEOUT, tmr.ALARM_SINGLE, onOpen)

    gpio.write(config.PIN_OPEN, gpio.HIGH)
    gpio.trig(config.PIN_OPEN, "low", onOpen)
end

function module.stop()
    stopDrive()
    tmr.unregister(config.TIMER_CURT)
    app.publish("Stopped")
end

module.onMessage = {
    ["open"] = module.open,
    ["close"] = module.close,
    ["stop"] = module.stop,
    ["restart"] = node.reset,
}

return module
