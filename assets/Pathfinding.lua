#!/usr/local/bin/lua

BombMap = {}
PlayerMap = {}
BoxMap = {}

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

local infini = 1 / 0

Start = { x = 0, y = 0 }

function SetMapValues(updatedBombMap, updatedPlayerMap, updatedBoxMap)
    BombMap = updatedBombMap
    PlayerMap = updatedPlayerMap
    BoxMap = updatedBoxMap
end

function dist(pos1, pos2)
	return (((pos2.x - pos1.x) ^ 2 + (pos2.y - pos1.y) ^ 2) ^ 0.5)
end

function is_valid_node(node, neighbor)
	--print(Dump(BoxMap[node.x + 1][node.y + 1]))
	--print("Volo")

	--print(BoxMap[node.y + 1][node.x + 1])
	if (BoxMap[node.y + 1][node.x + 1] == BoxMapValues.EMPTY) then
		--print("Rolo")
        if (dist(node, neighbor) <= 1.0) then
			--print("Solo")
            return (true)
        end
    end
    return (false)
end

function lowest_f_score(set, f_score)
	local lowest = infini
	local best = nil

	for _, node in ipairs(set) do
		local score = f_score[node]
		if score < lowest then
			lowest = score
			best = node
		end
	end
	return best
end

function neighbor_nodes(currentPos, positions)

	local neighbours = {}

    for _, pos in ipairs(positions) do
		--print("Yolo")
        if (currentPos.x ~= pos.x or currentPos.y ~= pos.y) and is_valid_node(currentPos, pos) then
			--print("Lolo")
            table.insert(neighbours, pos)
        end
		--print("Molo")
    end
	---print("Nolo")
    return (neighbours)
end

function unwind_path(path, map, current)
	if map[current] then
		table.insert( path, 1, map[current] )
		return unwind_path(path, map, map[current])
	end
	return path
end

function remove_node(set, remove)
	for i, node in ipairs(set) do
		if (node.x == remove.x and node.y == remove.y) then
			set[i] = set[#set]
			set[#set] = nil
            return
        end
	end
end

function not_in(set, current)
	for _, node in ipairs(set) do
		if (node.x == current.x and node.y == current.y) then
			return false
		end
	end
	return true
end

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

function AStar(start, goal, nodes)
	--print("Starting AStar")

	--print("Nolo")
    local openSet = { start }
	local closeSet = {}

	local fScore = {}
	local gScore = {}

	local came_from = {}

	gScore[start] = 0
	--print("start and goal :")
	--print(start.x)
	--print(start.y)
	--print(goal.x)
	--print(goal.y)
	--print(Dump(goal))
	--print(Dump(nodes))
	--print("gScore:")
	--print(gScore[start])
	--print(start.x - goal.x)

	fScore[start] = gScore[start] + (dist(start, goal) + .0)
    --print("After dist")
	--print(fScore[start])

	--print("Starting while")
	while #openSet > 0 do

		local current = lowest_f_score(openSet, fScore)

		--print("156 curr " .. Dump(current))
		--print("157 goal " .. Dump(goal))
		--print()

		if current.x == goal.x and current.y == goal.y then
			local path = unwind_path({}, came_from, goal)

			table.insert( path, goal )
			--print("return path")
			return path
		end

		remove_node(openSet, current)
		table.insert(closeSet, current)

		--print("Starting for")
		--print("Get neighbor nodes")
		local neighbors = neighbor_nodes(current, nodes)
		--print("After neighbor nodes")
		for _, neighbor in ipairs(neighbors) do
			--print("Starting not_in close")
			if not_in(closeSet, neighbor) then
				--print(gScore[current])
				--print(Dump(current))
				--print(Dump(neighbor))
				local tentative = gScore[current] + (dist(current, neighbor) + .0)

				--print("Starting not_in open")
				if not_in(openSet, neighbor) or tentative < gScore[neighbor] then
					came_from[neighbor] = current
					gScore[neighbor] = tentative
					fScore[neighbor] = gScore[neighbor] + (dist(neighbor, goal) + .0)
					if not_in(openSet, neighbor) then
						table.insert(openSet, neighbor)
					end
				end
			end
		end
	end
	print("Null path!")
	return ({ start })
end

--local test3 = {}
--local index = 1

--for i = 0, 10 do
--	for j = 0, 10 do
		--test3[index] = {x = i, y = j}
		--index = index + 1
	--end
--end

--local valid_node_func = function (node, neighbor)

--	local MAX_DIST = 1

	--if dist(node, neighbor) <= MAX_DIST then
--		return true
--	end
--	return false
--end

--local result = astar(test3[1], test3[index - 1], test3, valid_node_func)


--print(Dump(result))