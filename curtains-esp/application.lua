-- file : application.lua
local module = {}  
m = nil

function module.publish( data, topic )
    local topic = topic or "general"
    print(topic .. ": " .. data)
    if m then
        m:publish(config.ENDPOINT .. topic,data,0,0)
    end
end

-- Sends a simple ping to the broker
local function send_ping()  
    m:publish(config.ENDPOINT .. "ping","id=" .. config.ID,0,0)
end

-- Sends my id to the broker for registration
local function register_myself()  
    m:subscribe(config.ENDPOINT .. "listen",0,function(conn)
        print("Successfully subscribed to data endpoint")
        onStart()
    end)
end

local function mqtt_start()  
    print("Subscribing to data endpoint");
    m = mqtt.Client(config.ID, 120)
    -- register message callback beforehand
    m:on("message", function(conn, topic, data) 
      if data ~= nil then
        print(topic .. ": " .. data)
        onMessage(data)
      end
    end)
    -- Connect to broker
    print(config.HOST .. config.PORT)
    m:connect(config.HOST, config.PORT, 0, function(con) 
        print("Attempting to subscribe");
        register_myself()
        -- And then pings each 1000 milliseconds
        tmr.stop(6)
        tmr.alarm(6, 5000, 1, send_ping)
    end) 

end

function module.start()  
  mqtt_start()
end

return module  
