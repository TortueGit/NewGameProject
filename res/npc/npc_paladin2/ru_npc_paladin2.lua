-- Routine for NPC "Paladin2"

velocity = 40

loadRoutine = function(R, W)

	if (W:isConditionFulfilled("default","gandria_open")) then

		R:setTilePosition(44.5,52.5)
		R:setLooped(false)
		
		R:goToTile(44.5,52.6)
		
	else
		
		R:setTilePosition(44,54)

		R:wait(5000)	
		R:goToTile(44,54)
		R:goToTile(43,55)
		
	end

end	