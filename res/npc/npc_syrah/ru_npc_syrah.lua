-- Routine for NPC "Syrah" 

velocity = 30

loadRoutine = function(R, W)

	if (W:isConditionFulfilled("npc_syrah","talked")) then
		R:setTalkingActive(W:hasItem("qe_invisrecipe", 1) and not W:isConditionFulfilled("npc_syrah", "invis_recipe"))
		R:setReloadEnabled(false)
		R:setTilePosition(13,11)
		
		R:setFacingDown()
		R:wait(1000)
		R:goToTile(13,9.5)
		R:wait(5000)
		R:goToTile(13,11)
		R:goToTile(10,11)
		R:goToTile(10,7)
		R:goToTile(9,7)
		R:setFacingUp()
		R:wait(5000)
		R:goToTile(11,7)
		R:goToTile(11,5.5)
		R:goToTile(15.5,5.5)
		R:goToTile(15.5,7)
		R:setFacingLeft()
		R:wait(2000)
		R:goToTile(17,7)
		R:setFacingDown()
		R:wait(3000)
		R:goToTile(15.5,7)
		R:goToTile(15.5,5.5)
		R:goToTile(11,5.5)
		R:goToTile(11,7)
		R:goToTile(10,7)
		R:goToTile(10,11)
		
	else
		R:setTalkingActive(true)
		R:setReloadEnabled(true)
		R:setTilePosition(13,10.5)
		R:setFacingDown()
		R:setLooped(false)
	end

end	