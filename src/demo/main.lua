
require 'defs'

local oda = require 'oda'

function love.load ()
  oda.start()
  oda.registerPath("../patches") 
  oda.registerPath(ODA_PATCHES_PATH) 
  local ev = oda.eventInstance "example"
end

function love.keypressed (key)
  if key == 'escape' then
    love.event.push 'quit'
  end
end
  
local time = 0

function love.update (dt)
  oda.tick()
  time = time + dt
end

function love.quit ()
  oda.finish()
end

