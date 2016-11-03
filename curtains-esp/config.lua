-- file : config.lua
local module = {}

module.SSID = {}  
module.SSID["Kozyavki"] = "kozyavki25"

module.HOST = "192.168.1.4"  
module.PORT = 1883  
module.ID = node.chipid()

module.ENDPOINT = "/room/curtains/"  
return module  
