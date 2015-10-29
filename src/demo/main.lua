require 'defs'

local oda = require 'oda'
local ev
local effects
local items

local ballX
local ballY
local gametime
local w, h = love.window.getDimensions()

local collectible
local quad

local function newItem() 
  table.insert(items, {love.math.random(1, w), love.math.random(1, h), love.math.random(1,4)})
end

function love.load ()
  oda.start()
  oda.registerPath("../patches") 
  oda.registerPath(ODA_PATCHES_PATH) 
  ev = oda.eventInstance "example"
  effects = {}
  items = {}
  ballX = 20
  ballY = 20
  gametime = 0
  collectible = love.graphics.newImage("crystal-qubodup-ccby3-32-blue.png")
  quad = love.graphics.newQuad(32,0,32,32,256,32)


end

function love.keypressed (key)
  print("[demo] Pressed '"..key.."'")
  if key == 'escape' then
    love.event.push 'quit'
  elseif key == 'return' then
    ev:pushCommand('start')
  elseif key == 'tab' then
    ev:pushCommand('test')
  elseif key == '1' then
    ev:pushCommand('trilha1')
  elseif key == '2' then
    ev:pushCommand('trilha2')
  elseif key == '3' then
    ev:pushCommand('ambos')
  end
end

function love.update (dt)
  local dead = {}
  local itemscollected = {}
  gametime = gametime + dt
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
  if love.keyboard.isDown("up") then
    ballY = math.max(20, ballY - 300*dt)
  elseif love.keyboard.isDown("down") then
    ballY = math.min(h-20, ballY + 300*dt)
  elseif love.keyboard.isDown("left") then
    ballX = math.max(20, ballX - 300*dt)
  elseif love.keyboard.isDown("right") then
    ballX = math.min(w-20, ballX + 300*dt)
  end
  ev:pushCommand('x', 127*ballX/w)
  ev:pushCommand('y', ballY/h)

  if gametime >= 5 then
    newItem()
    gametime = gametime - 5
  end

  for j,item in ipairs(items) do
    local distancia = math.sqrt(math.pow(item[1] - ballX, 2) + math.pow(item[2] - ballY, 2))
    if distancia <= 20 then
      ev:pushCommand('itemsong', item[3])
      table.insert(itemscollected, j)
    end
  end
  for k=#itemscollected,1,-1 do
    table.remove(items, itemscollected[k])
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
  for j,item in ipairs(items) do
    if item[3] == 2 then
      love.graphics.setColor(255,0,0,255)
    elseif item[3] == 3 then
      love.graphics.setColor(0,255,0,255)
    elseif item[3] == 4 then
      love.graphics.setColor(0,0,255,255)
    end

    love.graphics.draw(collectible, quad, item[1]-16, item[2]-16)
    love.graphics.setColor(255,255,255,255)
  end
  love.graphics.circle('line', ballX, ballY, 20)
end

