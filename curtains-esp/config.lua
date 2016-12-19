-- file : config.lua
local module = {}

module.SSID = {}  
module.SSID[""] = ""

module.HOST = ""
module.PORT = 1883  
module.ID = node.chipid()

module.ENDPOINT = "/room/curtains/"

module.DIRECTION = true
module.PIN_OPEN = 6
module.PIN_CLOSE = 7
module.DRIVER_EN = 5
module.DRIVER_A1 = 1
module.DRIVER_A2 = 2
module.TIMER_CURT = 2
module.DEFAULT_TIMEOUT = 20000

return module  
