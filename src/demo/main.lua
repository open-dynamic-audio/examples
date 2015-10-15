
require 'defs'

local oda = require 'oda'

function love.load ()
  oda.start()
  oda.registerPath(ODA_PATCHES_PATH) 
end

function love.keypressed (key)
  if key == 'escape' then
    love.event.push 'quit'
  end
end
  
function love.update (dt)
  oda.tick()
end

function love.quit ()
  oda.finish()
end

