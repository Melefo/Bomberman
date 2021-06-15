#!/usr/local/bin/lua

require "Pathfinding"

BoxMapValues = {
    OFFWALL = -21,
    INWALL = -20,
    EMPTY = -3,
    BOX = 1
}

BombMapValues = {
    OFFWALL = -21,
    INWALL = -20,
    EMPTY = -3,
    BOMB = 0
}

PlayerMapValues = {
    OFFWALL = -21,
    INWALL = -20,
    PLAYER = 1,
    EMPTY = -3
}

moves = {
    right = {x = 1, y = 0},
    left = {x = -1, y = 0},
    up = {x = 0, y = 1},
    down = {x = 0, y = -1}
};

local bombMap = {}
local playerMap = {}
local boxMap = {}

Xdir = 0.0;
Zdir = 0.0;

function is_a_safe_area(bombarea, boxarea, playerarea)
    if (bombarea == BombMapValues.EMPTY and boxarea == BoxMapValues.EMPTY and playerarea == PlayerMapValues.EMPTY) then
        return true
    else
        return false
    end
    return false
end

function is_a_free_to_walk_area(area)
    if (area != BoxMapValues.EMPTY) then
        return false
    else
        return true
    end
    return false
end

function is_close_to_box(pos, boxmap, bombtimermap)
    local posi = {x = math.floor(pos[1]+1), z = math.floor(pos[3]+1)}
    local case = {N = boxmap[posi.z+1][posi.x], W = boxmap[posi.z][posi.x-1], S = boxmap[posi.z-1][posi.x], E = boxmap[posi.z][posi.x+1]}

    --check au nord
    if (case.N > 0 or case.W > 0 or case.S > 0 or case.E > 0) then
        return true
    end
end

--[[
function check_area_around(posi, boxmap, bombtimermap, playersmap, value)

    --comment stocker les différents path ?
    --attention à pas dépasser les limites de la map
    --avec cette recursive ca va boucle inf

    if (boxmap[posi.z+1][posi.x] == BoxMapValues.EMPTY) then
        check_area_around( , boxmap, bombtimermap, playersmap, value)
    end
    if (boxmap[posi.z][posi.x-1] == BoxMapValues.EMPTY) then
        check_area_around( , boxmap, bombtimermap, playersmap, value)
    end
    if (boxmap[posi.z-1][posi.x] == BoxMapValues.EMPTY) then
        check_area_around( , boxmap, bombtimermap, playersmap, value)
    end
    if (boxmap[posi.z][posi.x+1] == BoxMapValues.EMPTY) then
        check_area_around( , boxmap, bombtimermap, playersmap, value)
    end
end

function find_closest_value(pos, boxmap, bombtimermap, playersmap, value)
    local posi = {x = math.floor(pos[1]+1), z = math.floor(pos[3]+1)}

    check_area_around(posi, boxmap, bombtimermap, playersmap, value)
end
]]
function get_direction(pos, boxmap, bombtimemap)
    local direction = {north = false, west = false, south = false, east = false}
    local posi = {x = math.floor(pos[1]+1), z = math.floor(pos[3]+1)}

    direction.north = is_a_safe_area(bombtimemap[posi.z+1][posi.x], boxmap[posi.z+1][posi.x], boxmap[posi.z+1][posi.x])
    direction.west = is_a_safe_area(bombtimemap[posi.z][posi.x-1], boxmap[posi.z][posi.x-1], boxmap[posi.z][posi.x-1])
    direction.south = is_a_safe_area(bombtimemap[posi.z-1][posi.x], boxmap[posi.z-1][posi.x], boxmap[posi.z-1][posi.x])
    direction.east = is_a_safe_area(bombtimemap[posi.z][posi.x+1], boxmap[posi.z][posi.x+1], boxmap[posi.z][posi.x+1])
    print(direction.north, direction.west, direction.south, direction.east)
    return (direction)
end

function get_simple_direction(pos, boxmap, bombtimemap)
    local direction = {north = false, west = false, south = false, east = false}
    local posi = {x = math.floor(pos[1]+1), z = math.floor(pos[3]+1)}

    direction.north = is_a_free_to_walk_area(boxmap[posi.z+1][posi.x])
    direction.west = is_a_free_to_walk_area(boxmap[posi.z][posi.x-1])
    direction.south = is_a_free_to_walk_area(boxmap[posi.z-1][posi.x])
    direction.east = is_a_free_to_walk_area(boxmap[posi.z][posi.x+1])
    return (direction)
end

function modify_direction(direction)
    if (direction.north == true) then
        Xdir = 0
        Zdir = 0.5
    elseif (direction.west == true) then
        Xdir = -0.5
        Zdir = 0
    elseif (direction.south == true) then
        Xdir = 0
        Zdir = -0.5
    elseif (direction.east == true) then
        Xdir = 0.5
        Zdir = 0
    else
        return (0)
    end
end

function get_safe_direction(pos, boxmap, bombtimemap)
    local direction = get_direction(pos, boxmap, bombtimemap)

    modify_direction()
    if (Xdir == 0 and Zdir == 0)
        direction = get_simple_direction(pos, boxmap, bombtimemap)
        modify_direction(direction)
    end
    print("\n")
    return (0)
end 

function SimpleIsWalkable(pos)

    if (bombMap[pos.x][pos.y] < BombMapValues.BOMB) then
        return (true)
    end
    return (false)
end

function is_safe(pos, bombtimemap)
    if (bombtimemap[pos[3]+1][pos[1]+1] < 4 and bombtimemap[pos[3]+1][pos[1]+1] >= 0) then
        return (false)
    else
        return (true)
    end
    return (true)
end


function SetMapValues(updatedBombMap, updatedPlayerMap, updatedBoxMap)
    bombMap = updatedBombMap
    playerMap = updatedPlayerMap
    boxMap = updatedBoxMap
end

function IsPositionWalkable(position, neighbour)
    -- ! ajouter + 1 ??
    if (boxMap[position.x][position.y] == BoxMapValues.EMPTY) then
        if (Pathfinding.dist(position, neighbour) <= 1) then
            return (true)
        end
    end
    return (false)
end