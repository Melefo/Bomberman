#!/usr/local/bin/lua

-- -20 = INWALL
-- -21 = OFFWALL

Xdir = 0.0;
Zdir = 0.0;

function get_direction(pos, boxmap)
    if (boxmap[pos[3]+1][pos[1]+1] == -20 or boxmap[pos[3]+1][pos[1]+1] == -21) then
        Xdir = 0.5;
        Zdir = 0.0;
    else
        Xdir = 0.0;
        Zdir = 0.5;
    end
    return (0)
end

function is_a_safe_area(bombarea, boxarea, playerarea)
    if (bombarea == -3 and boxarea == -3 and playerarea == -3) then
        return true
    else
        return false
    end
    return false
end

function get_safe_direction(pos, boxmap, bombtimemap)
    local direction = {north = false, west = false, south = false, east = false}

    direction.north = is_a_safe_area(bombtimemap[math.floor(pos[3]+2)][math.floor(pos[1]+1)], boxmap[math.floor(pos[3]+2)][math.floor(pos[1]+1)], boxmap[math.floor(pos[3]+2)][math.floor(pos[1]+1)])
    direction.west = is_a_safe_area(bombtimemap[math.floor(pos[3]+1)][math.floor(pos[1])], boxmap[math.floor(pos[3]+1)][math.floor(pos[1])], boxmap[math.floor(pos[3]+1)][math.floor(pos[1])])
    direction.south = is_a_safe_area(bombtimemap[math.floor(pos[3])][math.floor(pos[1]+1)], boxmap[math.floor(pos[3])][math.floor(pos[1]+1)], boxmap[math.floor(pos[3])][math.floor(pos[1]+1)])
    direction.east = is_a_safe_area(bombtimemap[math.floor(pos[3]+1)][math.floor(pos[1]+2)], boxmap[math.floor(pos[3]+1)][math.floor(pos[1]+2)], boxmap[math.floor(pos[3]+1)][math.floor(pos[1]+2)])
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
        --infinite dab
        return (0)
    end
    return (0)
end 

function is_safe(pos, bombtimemap)
    if (bombtimemap[pos[3]+1][pos[1]+1] < 4 and bombtimemap[pos[3]+1][pos[1]+1] >= 0) then
        return (false)
    else
        return (true)
    end
    return (true)
end

function drop_a_bomb(pos, boxmap)
    if (boxmap[pos[3]+1][pos[1]+1] == 1 or boxmap[pos[3]+1][pos[1]+1] == 2 or boxmap[pos[3]+1][pos[1]+1] == 3) then
        return (1)
    elseif (boxmap[pos[3]+2][pos[1]+1] == 1 or boxmap[pos[3]+2][pos[1]+1] == 2 or boxmap[pos[3]+2][pos[1]+1] == 3) then
        return (1)
    elseif (boxmap[pos[3]+1][pos[1]+2] == 1 or boxmap[pos[3]+1][pos[1]+2] == 2 or boxmap[pos[3]+1][pos[1]+2] == 3) then
        return (1)
    else
        return (0)
    end
end