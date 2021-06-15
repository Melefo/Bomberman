#!/usr/local/bin/lua

function IsSafe(curr_area)
    if curr_area ~= 0 then
        return false;
    else
        return true;
    end
end

function Add(a, b)
    return a + b;
end

local safe = IsSafe(5);

CASE = {bomb = false, bonus = false, box = true}
BP = { bombpow = 0, bombtimer = 0}

Hello = "Hello World!";

local bombmap = {}

if safe then
    print("safe")
else
    print("not safe")
end

print(CASE.bomb)

--print(bombmap[1].bombtimer);

print("Hello World!");

function Dump(o)
    if type(o) == 'table' then
       local s = '{ '
       for k,v in pairs(o) do
          if type(k) ~= 'number' then k = '"'..k..'"' end
          s = s .. '['..k..'] = ' .. Dump(v) .. ','
       end
       return s .. '} '
    else
       return tostring(o)
    end
 end

print(Dump(Vector));

function dumpTest(test)
	print(Dump(test))
    print(test.x)
    local result = {}
    result[1] = 1
    result[2] = 2
    result[3] = 3
    return result
end
