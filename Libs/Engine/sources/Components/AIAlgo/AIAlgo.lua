#!/usr/local/bin/lua

-- -20 = INWALL
-- -21 = OFFWALL

Xdir = 0.0;
Zdir = 0.0;

function is_a_safe_area(bombarea, boxarea, playerarea)
    if (bombarea == -3 and boxarea == -3 and playerarea == -3) then
        return true
    else
        return false
    end
    return false
end

function is_a_bomb_area(bombarea)
    if (bombarea >= 0) then
        return true
    else
        return false
    end
    return true
end

function is_close_to_box(pos, boxmap, bombtimermap)
    local posi = {x = math.floor(pos[1]+1), z = math.floor(pos[3]+1)}
    local case = {N = boxmap[posi.z+1][posi.x], W = boxmap[posi.z][posi.x-1], S = boxmap[posi.z-1][posi.x], E = boxmap[posi.z][posi.x+1]}

    --check au nord
    if (case.N > 0 or case.W > 0 or case.S > 0 or case.E > 0) then
        return true
    end
end

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

function get_safe_direction(pos, boxmap, bombtimemap)
    print(pos[1]+1, pos[3]+1)
    local direction = get_direction(pos, boxmap, bombtimemap)

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
    print("\n")
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