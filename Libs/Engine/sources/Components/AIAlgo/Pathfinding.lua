#!/usr/local/bin/lua

require "AIAlgo"

local infini = 1 / 0

Start = { x = 0, y = 0 }

function dist(pos1, pos2)
	return math.sqrt((pos2.x - pos1.x) ^ 2 + (pos2.y - pos1.y) ^ 2)
end

function is_valid_node(node, neighbor)
	print("Tolo")
	print(Dump(BoxMap))
	print("After dump boxmap")
	if (BoxMap[position.x][position.y] == BoxMapValues.EMPTY and BombMap[position.x][position.y] == BoxMapValues.EMPTY) then
        if (dist(position, neighbour) <= 1) then
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
		print("Yolo")
        if currentPos ~= pos and is_valid_node(currentPos, pos) then
			print("Lolo")
            table.insert(neighbours, pos)
        end
		print("Molo")
    end
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
		if node == remove then
			set[i] = set[#set]
			set[#set] = nil
            return
        end
	end
end

function not_in(set, current)
	for _, node in ipairs(set) do
		if node == current then
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
	print("Starting AStar")

	print("Nolo")
    local openSet = { start }
	local closeSet = {}

	local fScore = {}
	local gScore = {}

	local came_from = {}

	gScore[start] = 0
	print("start and goal :")
	print(start.x)
	print(start.y)
	print(goal.x)
	print(goal.y)
	--print(Dump(goal))
	--print(Dump(nodes))
	print("gScore:")
	print(gScore[start])
	print(start.x - goal.x)

	fScore[start] = gScore[start] + dist(start, goal)
	print("After dist")
	print(fScore[start])

	print("Starting while")
	while #openSet > 0 do

		local current = lowest_f_score(openSet, fScore)

		if current == goal then
			local path = unwind_path({}, came_from, goal)

			table.insert( path, goal )
			print("return path")
			return path
		end

		remove_node(openSet, current)
		table.insert(closeSet, current)

		print("Starting for")
		local neighbors = neighbor_nodes(current, nodes)
		for _, neighbor in ipairs(neighbors) do
			print("Starting not_in close")
			if not_in(closeSet, neighbor) then
				print(gScore[current])
				print(Dump(current))
				print(Dump(neighbor))
				local tentative = gScore[current] + dist(current, neighbor)

				print("Starting not_in open")
				if not_in(openSet, neighbor) or tentative < gScore[neighbor] then
					came_from[neighbor] = current
					gScore[neighbor] = tentative
					fScore[neighbor] = gScore[neighbor] + dist(neighbor, goal)
					if not_in(openSet, neighbor) then
						table.insert(openSet, neighbor)
					end
				end
			end
		end
	end
	print("Null path!")
	return nil
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

MangeTesMorts()