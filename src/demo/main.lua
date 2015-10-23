
require 'defs'

local oda = require 'oda'
local ev
local effects

function love.load ()
  oda.start()
  oda.registerPath("../patches") 
  oda.registerPath(ODA_PATCHES_PATH) 
  ev = oda.eventInstance "example"
  effects = {}
end

function love.keypressed (key)
  print("[demo] Pressed '"..key.."'")
  if key == 'escape' then
    love.event.push 'quit'
  elseif key == 'return' then
    ev:pushCommand('start')
  elseif key == 'tab' then
    ev:pushCommand('test')
  else
    ev:pushCommand('tune', key:byte(1))
  end
end

function love.update (dt)
  local dead = {}
  for i,effect in ipairs(effects) do
    if effect[3] <= 0 then
      table.insert(dead, i)
    else
      effect[3] = effect[3] - 1000*dt
    end
  end
  for k=#dead,1,-1 do
    table.remove(effects, dead[k])
  end
  if love.mouse.isDown 'l' then
    local x, y = love.mouse.getPosition()
    local w, h = love.window.getDimensions()
    ev:pushCommand('tune', 127*(x*y)/(w*h))
    table.insert(effects, { x, y, 20 })
  end
  oda.tick()
end

function love.quit ()
  ev = nil
  oda.finish()
end

function love.draw ()
  for i,effect in ipairs(effects) do
    love.graphics.circle('fill', effect[1], effect[2], 2*effect[3])
  end
end

