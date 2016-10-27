
require 'defs'

local oda = require 'oda'

local SPEED = 128

local ev
local W,H
local avatar

function love.load ()
  oda.start()
  oda.registerPath("../patches")
  oda.registerPath(ODA_PATCHES_PATH)
  ev = oda.eventInstance "demo"
  W,H = love.graphics.getDimensions()
  avatar = {}
  avatar.x, avatar.y = W/2, H/2
end

function love.keypressed (key)
  if key == 'escape' then
    love.event.push 'quit'
  end
end

local DIRS = {
  up = { x = 0, y = -1 },
  down = { x = 0, y = 1 },
  left = { x = -1, y = 0 },
  right = { x = 1, y = 0 },
}

function love.update (dt)
  local vx, vy = 0, 0
  for key,dir in pairs(DIRS) do
    if love.keyboard.isDown(key) then
      vx, vy = vx + dir.x, vy + dir.y
    end
  end
  avatar.x, avatar.y = avatar.x + SPEED*vx*dt, avatar.y + SPEED*vy*dt
  ev:pushCommand("pos", avatar.x/W, avatar.y/H)
  ev:setAudioSource(5*(avatar.x - W/2)/W, 5*(avatar.y - W/2)/W, 0)
  oda.tick(dt)
end

function love.quit ()
  ev = nil
  oda.finish()
end

function love.draw ()
  love.graphics.setColor(200, 100, 255)
  love.graphics.circle('fill', avatar.x, avatar.y, 32, 16)
end
