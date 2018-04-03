-- Behavior for LEEEROY JENKINS

leeroy = false
isLeaving = false;

update = function(B, W)
    if (not leeroy) then
        leeroy = true
        B:say("Leeroy", 5)
    end
    if (B:getPosX() > 2100 and not isLeaving) then
        W:addQuestProgress("save_leeroy", "save_leeroy")
        W:addConditionProgress("npc_leeroy","finished")
        B:say("LeeroyDidIt", 5)
		B:setMovingTarget(2250, 0)
		B:wait(5)
        isLeaving = true
        return
    end
    if (isLeaving) then
        B:setDisposed()
        B:leaveLevel()
    end
end

onDeath = function(B, W)
    W:changeQuestState("save_leeroy", "failed")
    W:addConditionProgress("npc_leeroy","finished")
	B:say("Chicken", 4)
    B:setDisposed()
end
