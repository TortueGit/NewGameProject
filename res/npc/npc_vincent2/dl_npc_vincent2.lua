-- Dialogue for NPC "npc_vincent2"
loadDialogue = function(DL) 

	if (not DL:isConditionFulfilled("npc_vincent", "talked")) then 
		DL:setRoot(1) 
	elseif (DL:isQuestState("spoiled_fire", "started") and not DL:isConditionFulfilled("npc_rhendal", "spoiled_schnapps")) then 
		DL:setRoot(9) 
	elseif (DL:isQuestState("spoiled_fire", "started") and DL:isConditionFulfilled("npc_rhendal", "spoiled_schnapps")) then 
		DL:setRoot(10) 
	elseif (not DL:isConditionFulfilled("npc_vincent2", "talked") and DL:isQuestState("spoiled_fire", "completed")) then 
		DL:setRoot(11) 
	elseif (not DL:isConditionFulfilled("npc_vincent2", "talked") and DL:isConditionFulfilled("npc_vincent", "disgruntled")) then 
		DL:setRoot(12) 
	elseif (not DL:isConditionFulfilled("npc_vincent2", "talked")) then 
		DL:setRoot(13) 
	elseif (DL:isQuestState("elder_chest", "void")) then 
		DL:setRoot(2) 
	elseif (DL:isQuestState("elder_chest", "started")) then 
		DL:setRoot(35) 
	elseif (DL:isQuestState("elder_chest", "completed") and not DL:isConditionFulfilled("npc_vincent2", "second_quest")) then 
		DL:setRoot(39) 
	elseif (DL:isQuestState("invis_recipe", "void")) then 
		DL:setRoot(41) 
	elseif (DL:isQuestState("invis_recipe", "failed") and not  DL:isConditionFulfilled("npc_vincent2", "trusted_failed")) then 
		DL:setRoot(47) 
	else 
		DL:setRoot(45) 
	end 

	if (not DL:isConditionFulfilled("npc_vincent", "talked")) then 

		DL:createNPCNode(1, -2, "DL_Vincent_NotTalked") -- Hey you, psst! You look like you could use some gold. Interested in a ... special job?
		DL:addConditionProgress("npc_vincent", "talked")
		DL:addConditionProgress("npc_vincent2", "talked")
		DL:addConditionProgress("npc_vincent2", "key_50")
		DL:addNode()

	end

	if (DL:isQuestState("spoiled_fire", "started") and not DL:isConditionFulfilled("npc_rhendal", "spoiled_schnapps")) then 

		DL:createNPCNode(9, -1, "DL_Vincent_DoYourDuty") -- You remember that little deal we had in the tavern? You'd better do your job soon.
		DL:addNode()

	end

	if (DL:isQuestState("spoiled_fire", "started") and DL:isConditionFulfilled("npc_rhendal", "spoiled_schnapps")) then 

		DL:createNPCNode(10, 14, "DL_NPC_TaskFulfilled") -- Oh, it's you. You have carried out my task. Very good. You might be of use.
		DL:changeQuestState("spoiled_fire", "completed")
		DL:addGold(50)
		DL:addReputationProgress("thief", 10)
		DL:addNode()


		DL:createNPCNode(14, -2, "DL_Vincent_FurtherJob") -- Interested in another job?
		DL:addConditionProgress("npc_vincent2", "talked")
		DL:addNode()

	end

	if (not DL:isConditionFulfilled("npc_vincent2", "talked") and DL:isQuestState("spoiled_fire", "completed")) then 

		DL:createNPCNode(11, -2, "DL_Vincent_YouAgainGood") -- Hey. Good to see you here. My plan has worked out. Interested in another job?
		DL:addConditionProgress("npc_vincent2", "talked")
		DL:addNode()

	end

	if (not DL:isConditionFulfilled("npc_vincent2", "talked") and DL:isConditionFulfilled("npc_vincent", "disgruntled")) then 

		DL:createNPCNode(12, -2, "DL_Vincent_Disgruntled") -- Oh... you again. Y'know, I would have offered you an awesome job, if you hadn't been so aggressive. If you want another chance, it will cost you something.
		DL:addConditionProgress("npc_vincent2", "talked")
		DL:addConditionProgress("npc_vincent2", "key_150")
		DL:addNode()

	end

	if (not DL:isConditionFulfilled("npc_vincent2", "talked")) then 

		DL:createNPCNode(13, -2, "DL_Vincent_NotCooperated") -- Oh look. The boy who wasn't interested. Maybe a second chance for a job, huh?
		DL:addConditionProgress("npc_vincent2", "talked")
		DL:addConditionProgress("npc_vincent2", "key_100")
		DL:addNode()

	end

	if (DL:isQuestState("elder_chest", "void")) then 

		DL:createChoiceNode(2)
		if (not DL:isConditionFulfilled("npc_vincent2", "job_talked")) then 
			DL:addChoice(3, "DL_Choice_WhatDeal") -- Tell me more about that job.
		end
		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_50") and DL:hasItem("gold", 50)) then 
			DL:addItemChoice(5, "DL_Choice_GimmeKey", "gold", 50) -- Give me that key, I'll do it.
		end
		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_50") and not DL:hasItem("gold", 50)) then 
			DL:addItemChoice(15, "DL_Choice_GimmeKey", "gold", 50) -- 
		end
		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_100") and DL:hasItem("gold", 100)) then 
			DL:addItemChoice(16, "DL_Choice_GimmeKey", "gold", 100) -- 
		end
		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_100") and not DL:hasItem("gold", 100)) then 
			DL:addItemChoice(17, "DL_Choice_GimmeKey", "gold", 100) -- 
		end
		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_150") and DL:hasItem("gold", 150)) then 
			DL:addItemChoice(18, "DL_Choice_GimmeKey", "gold", 150) -- 
		end
		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_150") and not DL:hasItem("gold", 150)) then 
			DL:addItemChoice(19, "DL_Choice_GimmeKey", "gold", 150) -- 
		end
		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and not (DL:isConditionFulfilled("npc_vincent2", "key_150") or DL:isConditionFulfilled("npc_vincent2", "key_100") or DL:isConditionFulfilled("npc_vincent2", "key_50")) ) then 
			DL:addChoice(31, "DL_Choice_GimmeKey") -- 
		end
		DL:addChoice(8, "DL_Choice_NotInterested") -- I'm not interested.
		DL:addChoice(-1, "") -- 
		DL:addNode()

		if (not DL:isConditionFulfilled("npc_vincent2", "job_talked")) then 

			DL:createNPCNode(3, 4, "DL_Vincent_ExplainDeal") -- (Smiles and pulls out a golden key) I got this small key here. It belongs to a treasure chest. I could give it to you, if you want...
			DL:addConditionProgress("npc_vincent2", "job_talked")
			DL:addNode()


			DL:createChoiceNode(4)
			if (DL:isConditionFulfilled("npc_vincent2", "key_150")) then 
				DL:addChoice(6, "DL_Cendric_WhereCatch") -- And what is the catch?
			end
			if (DL:isConditionFulfilled("npc_vincent2", "key_100")) then 
				DL:addChoice(7, "DL_Cendric_WhereCatch") -- 
			end
			if (DL:isConditionFulfilled("npc_vincent2", "key_50")) then 
				DL:addChoice(20, "DL_Cendric_WhereCatch") -- 
			end
			if (not DL:isConditionFulfilled("npc_vincent2", "key_50") and not DL:isConditionFulfilled("npc_vincent2", "key_100") and not DL:isConditionFulfilled("npc_vincent2", "key_150")) then 
				DL:addChoice(21, "DL_Cendric_WhereCatch") -- 
			end
			DL:addNode()

			if (DL:isConditionFulfilled("npc_vincent2", "key_150")) then 

				DL:createNPCNode(6, 22, "DL_Vincent_TheCatch") -- Hehe, I knew you would ask. Well, the treasure chest doesn't belong to me, so to speak - it belongs to the Elder Rhendal.
				DL:addNode()


				DL:createNPCNode(22, 23, "DL_Vincent_KeyCost150") -- I had to steal the key from him. It wasn't easy, as he was fully awake.
				DL:addNode()


				DL:createNPCNode(23, 49, "DL_Vincent_KeyCost150_2") -- It wouldn't have been a problem if you did what I told you before... Now, to compensate for my troubles, it will cost you 150 golden coins.
				DL:addNode()


				DL:createNPCNode(49, -2, "DL_Vincent_Treasure") -- I only want you to get a special blue stone from the Elder's chest for me. You can keep the rest for yourself.
				DL:addNode()

			end

			if (DL:isConditionFulfilled("npc_vincent2", "key_100")) then 

				DL:createNPCNode(7, 24, "DL_Vincent_TheCatch") -- 
				DL:addNode()


				DL:createNPCNode(24, 25, "DL_Vincent_KeyCost100") -- I had to steal the key from him. It wasn't easy, as he was fully awake.
				DL:addNode()


				DL:createNPCNode(25, 50, "DL_Vincent_KeyCost100_2") -- It wouldn't have been a problem if you did what I told you before... Now, to compensate for my troubles, it will cost you 100 golden coins.
				DL:addNode()


				DL:createNPCNode(50, -2, "DL_Vincent_Treasure") -- 
				DL:addNode()

			end

			if (DL:isConditionFulfilled("npc_vincent2", "key_50")) then 

				DL:createNPCNode(20, 26, "DL_Vincent_TheCatch") -- 
				DL:addNode()


				DL:createNPCNode(26, 27, "DL_Vincent_KeyCost50") -- I had to steal the key from him. So, a small fee of 50 golden coins for the key would be a good compensation.
				DL:addNode()


				DL:createNPCNode(27, -2, "DL_Vincent_Treasure") -- 
				DL:addNode()

			end

			if (not DL:isConditionFulfilled("npc_vincent2", "key_50") and not DL:isConditionFulfilled("npc_vincent2", "key_100") and not DL:isConditionFulfilled("npc_vincent2", "key_150")) then 

				DL:createNPCNode(21, 28, "DL_Vincent_TheCatch") -- 
				DL:addNode()


				DL:createNPCNode(28, 29, "DL_Vincent_KeyCost0") -- You remember the stuff I mixed into the schnapps you gave him?
				DL:addNode()


				DL:createNPCNode(29, 52, "DL_Vincent_KeyCost0_2") -- It was a sleeping powder. Getting the key from him was mere child's play.
				DL:addNode()


				DL:createNPCNode(52, -2, "DL_Vincent_Treasure") -- 
				DL:addNode()

			end

		end

		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_50") and DL:hasItem("gold", 50)) then 

			DL:createNPCNode(5, 30, "DL_Vincent_StartElderQuest") -- A good choice. Here you go.
			DL:removeGold(50)
			DL:addItem("ke_rhendal", 1)
			DL:addNode()


			DL:createNPCNode(30, 54, "DL_Vincent_ChestIsObserved") -- The chest is in a secret room in the Elder's house, behind the wall to the West.
			DL:changeQuestState("elder_chest", "started")
			DL:addNode()


			DL:createNPCNode(54, -2, "DL_Vincent_ChestIsObserved2") -- Oh, and it's most likely guarded by observer spells. Just make sure that they don't catch you.
			DL:addNode()

		end

		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_50") and not DL:hasItem("gold", 50)) then 

			DL:createNPCNode(15, -1, "DL_Vincent_NotEnoughGold") -- Come back when you have enough gold.
			DL:addNode()

		end

		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_100") and DL:hasItem("gold", 100)) then 

			DL:createNPCNode(16, 32, "DL_Vincent_StartElderQuest") -- 
			DL:removeGold(100)
			DL:addItem("ke_rhendal", 1)
			DL:addNode()


			DL:createNPCNode(32, -2, "DL_Vincent_ChestIsObserved") -- 
			DL:changeQuestState("elder_chest", "started")
			DL:addNode()

		end

		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_100") and not DL:hasItem("gold", 100)) then 

			DL:createNPCNode(17, -1, "DL_Vincent_NotEnoughGold") -- 
			DL:addNode()

		end

		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_150") and DL:hasItem("gold", 150)) then 

			DL:createNPCNode(18, 33, "DL_Vincent_StartElderQuest") -- 
			DL:removeGold(150)
			DL:addItem("ke_rhendal", 1)
			DL:addNode()


			DL:createNPCNode(33, -2, "DL_Vincent_ChestIsObserved") -- 
			DL:changeQuestState("elder_chest", "started")
			DL:addNode()

		end

		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and DL:isConditionFulfilled("npc_vincent2", "key_150") and not DL:hasItem("gold", 150)) then 

			DL:createNPCNode(19, -1, "DL_Vincent_NotEnoughGold") -- 
			DL:addNode()

		end

		if (DL:isConditionFulfilled("npc_vincent2", "job_talked") and not (DL:isConditionFulfilled("npc_vincent2", "key_150") or DL:isConditionFulfilled("npc_vincent2", "key_100") or DL:isConditionFulfilled("npc_vincent2", "key_50")) ) then 

			DL:createNPCNode(31, 34, "DL_Vincent_StartElderQuest") -- 
			DL:addItem("ke_rhendal", 1)
			DL:addNode()


			DL:createNPCNode(34, -2, "DL_Vincent_ChestIsObserved") -- 
			DL:changeQuestState("elder_chest", "started")
			DL:addNode()

		end


		DL:createNPCNode(8, -1, "DL_Vincent_Pity") -- What a pity.
		DL:addConditionProgress("npc_vincent", "talked")
		DL:addConditionProgress("npc_vincent2", "talked")
		DL:addNode()

	end

	if (DL:isQuestState("elder_chest", "started")) then 

		DL:createChoiceNode(35)
		if (not DL:isConditionFulfilled("npc_vincent2", "observer_spells")) then 
			DL:addChoice(36, "DL_Choice_ObserverSpells") -- What are "observer spells"?
		end
		if (DL:isQuestState("elder_chest", "started") and DL:isConditionFulfilled("npc_vincent2", "rhendal_chest_looted")) then 
			DL:addChoice(37, "DL_Choice_FoundChest") -- I got the gem from the Elder's chest...
		end
		DL:addChoice(-1, "DL_Choice_CU") -- See you later.
		DL:addNode()

		if (not DL:isConditionFulfilled("npc_vincent2", "observer_spells")) then 

			DL:createNPCNode(36, 48, "DL_Vincent_ObserverSpells") -- A nasty form of magic. People place it in their homes so that thieves won't be able to steal something.
			DL:addConditionProgress("npc_vincent2", "observer_spells")
			DL:addHint("ObserverSpell")
			DL:addNode()


			DL:createNPCNode(48, -2, "DL_Vincent_ObserverSpells2") -- But they can't see everything... (grins). But if they see you stealing something, they will put you in jail. It won't be a nice experience, I can tell you that.
			DL:addNode()

		end

		if (DL:isQuestState("elder_chest", "started") and DL:isConditionFulfilled("npc_vincent2", "rhendal_chest_looted")) then 

			DL:createNPCNode(37, 38, "DL_Vincent_OpenedTheChest") -- Hehe, I knew you'd succeed. But I don't want that stone anyway, you can keep it as your reward.
			DL:addNode()


			DL:createNPCNode(38, -2, "DL_Vincent_StealingFitsYou") -- Taking belongings from other people doesn't seem to be a big deal for you. I could teach you how to get to even more valuables.
			DL:changeQuestState("elder_chest", "completed")
			DL:addReputationProgress("thief", 5)
			DL:addNode()

		end

	end

	if (DL:isQuestState("elder_chest", "completed") and not DL:isConditionFulfilled("npc_vincent2", "second_quest")) then 

		DL:createChoiceNode(39)
		DL:addChoice(40, "DL_Choice_TeachMe") -- Teach me.
		DL:addChoice(-1, "") -- 
		DL:addNode()


		DL:createNPCNode(40, -2, "DL_Vincent_TeachUnlock") -- Of course. Just read this scroll and I can offer you more work in this... domain. (Grins) 
		DL:addItem("sp_unlock", 1)
		DL:addConditionProgress("npc_vincent2", "second_quest")
		DL:addNode()

	end

	if (DL:isQuestState("invis_recipe", "void")) then 

		DL:createChoiceNode(41)
		if (DL:isSpellLearned(7)) then 
			DL:addChoice(42, "DL_Choice_SecondQuest") -- I'm ready for your new job.
		end
		DL:addChoice(-1, "") -- 
		DL:addNode()

		if (DL:isSpellLearned(7)) then 

			DL:createNPCNode(42, 43, "DL_Vincent_SecondQuest") -- Good. This time, the stakes are a little bit higher. We know that the mage Syrah knows how to brew a potion that can render you invisible.
			DL:addNode()


			DL:createNPCNode(43, 44, "DL_Vincent_SecondQuest2") -- A very useful ability, isn't it? The only problem is, she won't tell us how it works.
			DL:addNode()


			DL:createNPCNode(44, 51, "DL_Vincent_SecondQuest3") -- She leaves us no choice but to abstract the recipe from her.
			DL:addNode()


			DL:createNPCNode(51, 53, "DL_Vincent_SecondQuest4") -- There must be a way to get into her basement - by taking a shortcut through the sewers. Find that way and get the recipe for us.
			DL:addNode()


			DL:createNPCNode(53, -2, "DL_Vincent_SecondQuest5") -- If you manage to do that, you might get to know what "us" really means.
			DL:changeQuestState("invis_recipe", "started")
			DL:addNode()

		end

	end

	if (DL:isQuestState("invis_recipe", "failed") and not  DL:isConditionFulfilled("npc_vincent2", "trusted_failed")) then 

		DL:createNPCNode(47, -2, "DL_Vincent2_Disappointed") -- Hm. I trusted you and you failed me.
		DL:addConditionProgress("npc_vincent2", "trusted_failed")
		DL:addNode()

	end


	DL:createChoiceNode(45)
	if (DL:isQuestState("invis_recipe", "started") and DL:isQuestComplete("invis_recipe")) then 
		DL:addChoice(46, "DL_Choice_IGotRecipe") -- I got the recipe for you.
	end
	DL:addChoice(-1, "") -- 
	DL:addNode()

	if (DL:isQuestState("invis_recipe", "started") and DL:isQuestComplete("invis_recipe")) then 

		DL:createNPCNode(46, -1, "DL_Vincent_SecondQuestDone") -- Very well. I knew you had talent. Now, if you'd like to learn more of this useful magic, take this key and find the door it opens.
		DL:changeQuestState("invis_recipe", "completed")
		DL:removeItem("qe_invisrecipe", 1)
		DL:addItem("ke_thiefguild", 1)
		DL:addReputationProgress("thief", 10)
		DL:addConditionProgress("default", "thieves_open")
		DL:changeQuestState("rusty_key", "started")
		DL:addNode()

	end

end