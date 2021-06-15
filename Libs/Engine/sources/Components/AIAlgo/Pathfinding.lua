#!/usr/local/bin/lua

local infini = 1 / 0

Start = { x = 0, y = 0 }

function dist(pos1, pos2)
	return math.sqrt(math.pow(pos2.x - pos1.x, 2) + math.pow(pos2.y - pos1.y, 2))
end

function is_valid_node(node, neighbor)
	return true
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
        if (currentPos ~= pos) then
            table.insert(neighbours, pos)
        end
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

function astar(start, goal, nodes, valid_node)

    local openSet = { start }
	local closeSet = {}

	local fScore = {}
	local gScore = {}

	local came_from = {}

	if valid_node then
		is_valid_node = valid_node
	end

	gScore[start] = 0
	fScore[start] = gScore[start] + dist(start, goal)

	while #openSet > 0 do

		local current = lowest_f_score(openSet, fScore)

		if current == goal then
			local path = unwind_path({}, came_from, goal)

			table.insert( path, goal )
			return path
		end

		remove_node(openSet, current)
		table.insert(closeSet, current)

		local neighbors = neighbor_nodes(current, nodes)
		for _, neighbor in ipairs(neighbors) do
			if not_in(closeSet, neighbor) then
				local tentative = gScore[current] + dist(current, neighbor)

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

local valid_node_func = function (node, neighbor)

	local MAX_DIST = 1

	if dist(node, neighbor) <= MAX_DIST then
		return true
	end
	return false
end

--local result = astar(test3[1], test3[index - 1], test3, valid_node_func)


--print(Dump(result))