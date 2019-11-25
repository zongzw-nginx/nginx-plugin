
if (#arg ~= 1) then 
    print(string.format("%s <num>", arg[0]))
    os.exit(1)
end

local md5 = require "md5"
local socket = require "socket"

local fin
local st = socket.gettime()
for var=0, arg[1]-1 do
    fin = md5.sumhexa(var)
end
local et = socket.gettime()

local tc = math.floor((et - st)*1000000)
print(string.format("%s: %d, tv:%d millisecs", fin, arg[1]-1, tc))
