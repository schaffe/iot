-- file : init.lua
app = require("application")  
config = require("config")  
setup = require("setup")
curt = require("curtains")

function onStart()
    curt.start();
end

function onMessage(case)
    curt.onMessage[case]()
end

setup.start()  

