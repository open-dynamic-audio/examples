
require 'defs'

local oda = require 'oda'
local ev

function love.load ()
  oda.start()
  oda.registerPath("../patches") 
  oda.registerPath(ODA_PATCHES_PATH) 
  ev = oda.eventInstance "example"
end

function love.keypressed (key)
  if key == 'escape' then
    love.event.push 'quit'
  elseif key == 'return' then
    ev:pushCommand('start')
  elseif key == 'tab' then
    ev:pushCommand('test')
  end
end

function love.update (dt)
  oda.tick()
end

function love.quit ()
  ev = nil
  oda.finish()
end

