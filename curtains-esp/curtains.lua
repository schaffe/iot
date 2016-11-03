local module = {}

module.state = "low"
module.sensorOpen = 4
module.sensorClose = 3
module.TIMER_ID = 2
module.DEFAULT_TIMEOUT = 5000

function module.start()
    app.publish("Curtains app started")
    print("Setting up interrupts at Open sensor on port " .. module.sensorOpen)
    gpio.mode(module.sensorOpen, gpio.INT)
    gpio.mode(module.sensorClose, gpio.INT)
end

function onOpen()
    gpio.trig(module.sensorOpen, "none")
    app.publish("Open")
    tmr.stop(module.TIMER_ID)
    --module.close()
end

function onClose()
    gpio.trig(module.sensorClose, "none")
    app.publish("Close")
    tmr.stop(module.TIMER_ID)
    --module.open()
end

function module.close()
    app.publish("Closing...")
    tmr.alarm(module.TIMER_ID, module.DEFAULT_TIMEOUT, tmr.ALARM_SINGLE, onClose)
    gpio.trig(module.sensorClose, "low", onClose)
end

function module.open()
    app.publish("Opening...")
    tmr.alarm(module.TIMER_ID, module.DEFAULT_TIMEOUT, tmr.ALARM_SINGLE, onOpen)
    gpio.trig(module.sensorOpen, "low", onOpen)
end

function module.stop()
    app.publish("Stopped")
end

module.onMessage = {
    ["open"] = module.open,
    ["close"] = module.close,
    ["stop"] = module.stop,
}

return module
