onWin = function(W)
	W:addConditionProgress("boss", "BossKhajag")
    W:unlockAchievement("ACH_KILL_KHAJAG")
	W:setLevel("res/level/crystalcrypt/crystalcrypt.tmx", 520, 810)
end
	
onLose = function(W)
	W:setLevel("res/level/howlingcaverns/howlingcaverns.tmx", 4610, 560)
end