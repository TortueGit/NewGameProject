-- Behavior for prisoner (2) in the level gandriamines

routine = function(O) 
	O:gotoTile(72.0, 32.1)
	O:setFacingLeft()
	
	for i = 1, 3 do 
		O:executeFightAnimation()
		O:wait(1)
		O:executeFightAnimation()
		O:wait(1)
		O:executeFightAnimation()
		O:wait(5)
	end

	O:say("WorkWork", 2)
	O:wait(2)
end
