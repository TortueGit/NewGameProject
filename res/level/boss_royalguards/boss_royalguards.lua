onWin = function(W)
	W:addConditionProgress("boss", "BossRoyalguards")
    W:unlockAchievement("ACH_KILL_ROYAL_GUARDS")
	W:setMap("res/map/gandriacastle/gandriacastle.tmx", 638, 360)
end
	
onLose = function(W)
	W:setMap("res/map/gandriacastle/gandriacastle.tmx", 638, 360)
end