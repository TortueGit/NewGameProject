onWin = function(W)
	W:setLevel("res/level/jacklighthouse/jacklighthouse.tmx", 1500, 610)
	W:addConditionProgress("boss", "BossElysia")	
	W:addQuestDescription("element_master", 3)
    W:unlockAchievement("ACH_KILL_ELYSIA")
end
	
onLose = function(W)
	W:setLevel("res/level/jacklighthouse/jacklighthouse.tmx", 1360, 1460)
end