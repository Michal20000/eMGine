#include "Timer.hpp"
#include "BitField.hpp"
#include "Vector.hpp"
#include "Buffer.hpp"
#include "Logs.hpp"
#include "Errors.hpp"
#include "EntityEngine.hpp"
#include <type_traits>
#include <conio.h>

#define MIN(X, Y) ((X) <= (Y)) ? (X) : (Y)
#define MAX(X, Y) ((X) >= (Y)) ? (X) : (Y)
#define BETWEEN(X, Y) rand() % (Y - X + 1) + X



struct YourParty : public EntityGroup<YourParty>
{
};
struct YourEnemies : public EntityGroup<YourEnemies>
{
};
struct MainRow : public EntityGroup<MainRow>
{
};
struct DistanceRow : public EntityGroup<DistanceRow>
{
};



struct ActionEvent
{
	public:
	DEFAULT_5_RULE(ActionEvent);
	using ActionFunction = void (*)(EntityEngine&, ActionEvent&);
	Entity EntityEmitter;
	ActionFunction Function;

	static void OnEvent(EntityEngine& entity_engine, ActionEvent& event)
	{
		event.Function(entity_engine, event);

	}

};
struct EntityResult
{
	public:
	Entity Ob;
	size_t Length;

};

struct Action
{
	public:
	DEFAULT_5_RULE(Action);
	using ActionFunction = void (*)(EntityEngine&, ActionEvent&);
	ActionFunction Function;
	float InitiativeCost;
	int16_t StaminaCost;
	int16_t Probability;

	static EntityResult FindTarget(EntityEngine& ee, Entity entity)
	{
		if (ee.VerifyFragment<YourParty>(entity)) {
			EntityResult entity;
			entity.Length = 0;
			for (EntityView view = ee.View<YourEnemies>(); view.Verify(); ++view) entity.Length += 1;
			if (entity.Length == 0) return entity;
			size_t el = rand() % entity.Length; size_t i = 0;
			for (EntityView view = ee.View<YourEnemies>(); view.Verify(); ++view, ++i)
				if (el == i) entity.Ob = view.Record();
			return entity;

		}
		else {
			EntityResult entity;
			entity.Length = 0;
			for (EntityView view = ee.View<YourParty>(); view.Verify(); ++view) entity.Length += 1;
			if (entity.Length == 0) return entity;
			size_t el = rand() % entity.Length; size_t i = 0;
			for (EntityView view = ee.View<YourParty>(); view.Verify(); ++view, ++i)
				if (el == i) entity.Ob = view.Record();
			return entity;

		}

	}
	static void Deffensive(EntityEngine& ee, ActionEvent& event);
	static void Offensive(EntityEngine& ee, ActionEvent& event);

	static void Crossbow(EntityEngine& ee, ActionEvent& event);
	static void Bow(EntityEngine& ee, ActionEvent& event);
	static void Daggers(EntityEngine& ee, ActionEvent& event);
	static void Rocks(EntityEngine& ee, ActionEvent& event);

	static void Warhammer(EntityEngine& ee, ActionEvent& event);
	static void ConcussiveWarhammer(EntityEngine& ee, ActionEvent& event);

	static void LeftAxe(EntityEngine& ee, ActionEvent& event);
	static void RightAxe(EntityEngine& ee, ActionEvent& event);
	static void PowerfullAxe(EntityEngine& ee, ActionEvent& event);

	static void LeftSword(EntityEngine& ee, ActionEvent& event);
	static void RightSword(EntityEngine& ee, ActionEvent& event);
	static void PowerfullSword(EntityEngine& ee, ActionEvent& event);

};



struct Character : public EntityFragment<Character>
{
	public:
	std::string Label;
	int16_t LowestDamage;
	int16_t HighestDamage;
	int16_t Attack;
	int16_t Defense;
	static void OnCreate(Character& ob)
	{
		new(&ob.Label) std::string("");

	}
	static void OnDestroy(Character& ob)
	{
		ob.Label.~basic_string();

	}

};
struct Health : public EntityFragment<Health>
{
	public:
	int16_t Current;
	int16_t Limit;
	int16_t Regeneration;

};
struct Stamina : public EntityFragment<Stamina>
{
	public:
	int16_t Current;
	int16_t Limit;
	int16_t Regeneration;

};
struct Initiative : public EntityFragment<Initiative>
{
	public:
	float Current;
	float Regeneration;

};
struct AI : public EntityFragment<AI>
{
	public:
	std::vector<Action> Actions;
	Action* Current;
	static void OnCreate(AI& ob)
	{
		new(&ob.Actions) std::vector<Action>();
		ob.Actions.reserve(16);
		ob.Current = nullptr;

	}
	static void OnDestroy(AI& ob)
	{
		ob.Actions.~vector();

	}


};
struct Bleeding : public EntityFragment<Bleeding>
{
	public:
	float Current;
	static void OnCreate(Bleeding& ob)
	{
		LOG_FL_ERROR("Bleeding");
		ob.Current = 1.0;

	}
	
};
struct Poisoning : public EntityFragment<Poisoning>
{
	public:
	float Current;
	static void OnCreate(Poisoning& ob)
	{
		LOG_FL_ERROR("Poisoning");
		ob.Current = 1.0;

	}

};
struct Exhaustion : public EntityFragment<Exhaustion>
{
	public:
	float Current;
	static void OnCreate(Exhaustion& ob)
	{
		LOG_FL_ERROR("Exhaustion");
		ob.Current = 1.0;

	}
	
};



struct AttachBleeding
{
	public:
	Entity EntityEmitter;
	static void OnEvent(EntityEngine& ee, AttachBleeding& event)
	{
		ee.Attach<Bleeding>(event.EntityEmitter);
		Bleeding& debuff = ee.Fragment<Bleeding>(event.EntityEmitter);
		debuff.Current = 1.0F;

	}

};
struct AttachPoisoning
{
	public:
	Entity EntityEmitter;
	static void OnEvent(EntityEngine& ee, AttachPoisoning& event)
	{
		ee.Attach<Poisoning>(event.EntityEmitter);
		Poisoning& debuff = ee.Fragment<Poisoning>(event.EntityEmitter);
		debuff.Current = 1.0F;

	}

};
struct AttachExhaustion
{
	public:
	Entity EntityEmitter;
	static void OnEvent(EntityEngine& ee, AttachExhaustion& event)
	{
		ee.Attach<Exhaustion>(event.EntityEmitter);
		Exhaustion& debuff = ee.Fragment<Exhaustion>(event.EntityEmitter);
		debuff.Current = 1.0F;

	}

};
struct DetachBleeding
{
	public:
	Entity EntityEmitter;
	static void OnEvent(EntityEngine& ee, DetachBleeding& event)
	{
		ee.Detach<Bleeding>(event.EntityEmitter);

	}

};
struct DetachPoisoning
{
	public:
	Entity EntityEmitter;
	static void OnEvent(EntityEngine& ee, DetachPoisoning& event)
	{
		ee.Detach<Poisoning>(event.EntityEmitter);

	}

};
struct DetachExhaustion
{
	public:
	Entity EntityEmitter;
	static void OnEvent(EntityEngine& ee, DetachExhaustion& event)
	{
		ee.Detach<Exhaustion>(event.EntityEmitter);

	}

};
struct DeathEvent
{
	public:
	Entity EntityEmitter;
	static void OnEvent(EntityEngine& ee, DeathEvent& event)
	{
		Character& character = ee.Fragment<Character>(event.EntityEmitter);
		std::string dialogues[5];
		dialogues[0] = "As the life slowly fades from their eyes, Character $XYZ reflects on their journey, realizing that their time has come to an end.";
		dialogues[1] = "With each labored breath, Character $XYZ feels their strength waning, knowing that their final moments are upon them.";
		dialogues[2] = "As the world around them blurs, Character $XYZ whispers their last words, embracing the inevitable end of their journey.";
		dialogues[3] = "In the quiet solitude of their final moments, Character $XYZ finds peace, accepting the inevitability of their fate.";
		dialogues[4] = "As darkness envelops them, Character $XYZ's thoughts turn to the memories they leave behind, knowing that their story has reached its conclusion.";
		std::string& dialogue = dialogues[rand() % 5];
		dialogue.replace(dialogue.find("$XYZ"), 4, character.Label);
		ee.DestroyEntity(event.EntityEmitter);

	}

};



class Regeneration
{
	public:
	static void OnFrame(EntityEngine& ee, float dt)
	{
		for (EntityView view = ee.View<Character, Health>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Character& character = view.Fragment<Character>();
			Health& health = view.Fragment<Health>();

			std::string dialogues[3];
			dialogues[0] = "$XYZ feels a surge of energy coursing through their veins as they regain $V health points.";
			dialogues[1] = "As $XYZ takes a moment to rest, they feel their wounds slowly closing, regenerating $V health points.";
			dialogues[2] = "$XYZ takes a deep breath, feeling invigorated as their body heals, restoring $V health points.";
			std::string& dialogue = dialogues[rand() % 3];
			int16_t health_random = rand() % health.Regeneration;
			int16_t health_regeneration = MIN(health_random, health.Limit - health.Current);
			std::stringstream health_string; health_string << health_regeneration;
			health.Current += health_regeneration;
			
			dialogue.replace(dialogue.find("$XYZ"), 4, character.Label);
			dialogue.replace(dialogue.find("$V"), 2, health_string.str());
			if (health_regeneration != 0) LOG_WARN(dialogue);

		}
		for (EntityView view = ee.View<Character, Stamina>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Character& character = view.Fragment<Character>();
			Stamina& stamina = view.Fragment<Stamina>();

			std::string dialogues[3];
			dialogues[0] = "With a brief moment of concentration, $XYZ channels their inner strength, replenishing $V stamina points.";
			dialogues[1] = "Feeling revitalized, $XYZ focuses their mind, replenishing $V stamina points with renewed vigor.";
			dialogues[2] = "$XYZ takes a moment to catch their breath, feeling their stamina returning as they regain $V points of energy.";
			std::string& dialogue = dialogues[rand() % 3];
			int16_t stamina_random = rand() % stamina.Regeneration;
			int16_t stamina_regeneration = MIN(stamina_random, stamina.Limit - stamina.Current);
			std::stringstream stamina_string; stamina_string << stamina_regeneration;
			stamina.Current += stamina_regeneration;
			
			dialogue.replace(dialogue.find("$XYZ"), 4, character.Label);
			dialogue.replace(dialogue.find("$V"), 2, stamina_string.str());
			if (stamina_regeneration != 0) LOG_WARN(dialogue);

		}
		for (EntityView view = ee.View<Initiative>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Initiative& initiative = view.Fragment<Initiative>();
			initiative.Current += initiative.Regeneration * dt;

		}

	}

};
class AIController
{
	public:
	static void OnFrame(EntityEngine& ee, float dt)
	{
		for (EntityView view = ee.View<Stamina, Initiative, AI>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Stamina& stamina = view.Fragment<Stamina>();
			Initiative& initative = view.Fragment<Initiative>();
			AI& ai = view.Fragment<AI>();

			if (ai.Current == nullptr) {
				std::vector<uint16_t> choices = std::vector<uint16_t>();
				choices.reserve(ai.Actions.size());
				uint16_t chance = 0;
				for (Action& action : ai.Actions) {
					uint16_t stamina_modifier = stamina.Current >= action.StaminaCost ? 10 : 0;
					uint16_t initative_mofifier = initative.Current >= action.InitiativeCost ? 5 : 0;
					chance += action.Probability + stamina_modifier + initative_mofifier;
					choices.push_back(chance);

				}
				uint16_t value = rand() % chance;
				for (size_t i = 0; i < choices.size(); ++i) {
					if (value < choices[i]) {
						ai.Current = &ai.Actions[i];
						break;

					}

				}

			}

		}

	}

};
class ActionController
{
	public:
	static void OnFrame(EntityEngine& ee, float dt)
	{
		for (EntityView view = ee.View<Stamina, Initiative, AI>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Stamina& stamina = view.Fragment<Stamina>();
			Initiative& initative = view.Fragment<Initiative>();
			AI& ai = view.Fragment<AI>();

			if (ai.Current != nullptr) {
				if (stamina.Current >= ai.Current->StaminaCost && initative.Current >= ai.Current->InitiativeCost) {
					stamina.Current -= ai.Current->StaminaCost;
					initative.Current -= ai.Current->InitiativeCost;
					ActionEvent& event = ee.Dispatch<ActionEvent>();
					event.EntityEmitter = entity;
					event.Function = ai.Current->Function;
					ai.Current = nullptr;

				}
				
			}

		}
		ee.OnEvent();

	}

};
class BuffsDebuffs
{
	public:
	static void OnFrame(EntityEngine& ee, float dt)
	{
		for (EntityView view = ee.View<Character, Bleeding, Health>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Character& character = view.Fragment<Character>();
			Bleeding& bleeding = view.Fragment<Bleeding>();
			Health& health = view.Fragment<Health>();

			std::string dialogues[2];
			dialogues[0] = "As Character $XYZ grits their teeth in pain from their earlier wounds, they stumble and receive $V more damage.";
			dialogues[1] = "Character $XYZ curses under their breath, feeling the sting of their previous injuries as they take an additional $V points of damage.";
			std::string& dialogue = dialogues[rand() % 2];

			int16_t health_loss = rand() % 5; health_loss += 1;
			std::stringstream health_str; health_str << health_loss;
			health.Current -= health_loss;
			bleeding.Current -= dt;
			if (bleeding.Current <= 0.0F) {
				DetachBleeding& event = ee.Dispatch<DetachBleeding>();
				event.EntityEmitter = entity;

			}
			dialogue.replace(dialogue.find("$XYZ"), 4, character.Label);
			dialogue.replace(dialogue.find("$V"), 2, health_str.str());
			LOG_WARN(dialogue);

		}
		for (EntityView view = ee.View<Character, Poisoning, Health, Stamina>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Character& character = view.Fragment<Character>();
			Poisoning& poisoning = view.Fragment<Poisoning>();
			Health& health = view.Fragment<Health>();
			Stamina& stamina = view.Fragment<Stamina>();

			std::string dialogues[2];
			dialogues[0] = "$XYZ grimaces as the poison courses through their veins, dealing $V points of damage and draining $V points of stamina.";
			dialogues[1] = "Gasping for air, $XYZ feels the poison weakening their body, inflicting $V points of damage and sapping $V points of stamina.";
			std::string& dialogue = dialogues[rand() % 2];

			int16_t health_loss = rand() % 3; health_loss += 1;
			int16_t stamina_loss = rand() % 3; stamina_loss += 1;
			std::stringstream health_str; health_str << health_loss;
			std::stringstream stamina_str; stamina_str << stamina_loss;
			health.Current -= health_loss;
			stamina.Current -= stamina_loss;
			poisoning.Current -= dt;
			if (poisoning.Current <= 0.0F) {
				DetachPoisoning& event = ee.Dispatch<DetachPoisoning>();
				event.EntityEmitter = entity;

			}
			dialogue.replace(dialogue.find("$XYZ"), 4, character.Label);
			dialogue.replace(dialogue.find("$V"), 2, health_str.str());
			dialogue.replace(dialogue.find("$V"), 2, stamina_str.str());
			LOG_WARN(dialogue);

		}
		for (EntityView view = ee.View<Character, Exhaustion, Stamina>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Character& character = view.Fragment<Character>();
			Exhaustion& exhaustion = view.Fragment<Exhaustion>();
			Stamina& stamina = view.Fragment<Stamina>();

			std::string dialogues[2];
			dialogues[0] = "Exhausted from the relentless battle, $XYZ's muscles ache as they lose $V points of stamina.";
			dialogues[1] = "Feeling drained of energy, Character $XYZ's movements become sluggish as they lose $V points of stamina.";
			std::string& dialogue = dialogues[rand() % 2];

			int16_t stamina_loss = rand() % 5; stamina_loss += 1;
			std::stringstream stamina_str; stamina_str << stamina_loss;
			stamina.Current -= stamina_loss;
			exhaustion.Current -= dt;
			if (exhaustion.Current <= 0.0F) {
				DetachExhaustion& event = ee.Dispatch<DetachExhaustion>();
				event.EntityEmitter = entity;

			}
			dialogue.replace(dialogue.find("$XYZ"), 4, character.Label);
			dialogue.replace(dialogue.find("$V"), 2, stamina_str.str());
			LOG_WARN(dialogue);

		}
		ee.OnEvent();

	}

};
class DeathController
{
	public:
	static void OnFrame(EntityEngine& ee, float dt)
	{
		for (EntityView view = ee.View<Health>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Health health = view.Fragment<Health>();
			if (health.Current <= 0) {
				DeathEvent& event = ee.Dispatch<DeathEvent>();
				event.EntityEmitter = entity;

			}

		}
		ee.OnEvent();

	}

};
class FinishBattle
{
	public:
	static uint16_t PartyLength;
	static uint16_t EnemiesLength;
	static uint16_t OthersLength;
	static void OnFrame(EntityEngine& ee, float dt)
	{
		PartyLength = 0;
		EnemiesLength = 0;
		OthersLength = 0;

		for (EntityView view = ee.View<>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			if (ee.VerifyFragment<YourParty>(entity)) PartyLength += 1;
			else if (ee.VerifyFragment<YourEnemies>(entity)) EnemiesLength += 1;
			else OthersLength += 1;

		}
		if (OthersLength == 0) {
			if (PartyLength == 0 && EnemiesLength == 0)
				LOG_WARN("There is draw in the Battle");
			else if (PartyLength == 0)
				LOG_WARN("Your Party wins the Battle");
			else if (EnemiesLength == 0)
				LOG_WARN("Your Enemies win the Battle");

		}

	}

};
uint16_t FinishBattle::PartyLength = 0;
uint16_t FinishBattle::EnemiesLength = 0;
uint16_t FinishBattle::OthersLength = 0;



int32_t main()
{
	srand(time(nullptr));
	EntityEngine::Register<Character>();
	EntityEngine::Register<Health>();
	EntityEngine::Register<Stamina>();
	EntityEngine::Register<Initiative>();
	EntityEngine::Register<AI>();
	EntityEngine::Register<Bleeding>();
	EntityEngine::Register<Poisoning>();
	EntityEngine::Register<Exhaustion>();
	EntityEngine::Register<YourParty>();
	EntityEngine::Register<YourEnemies>();
	EntityEngine::Register<MainRow>();
	EntityEngine::Register<DistanceRow>();
	LOG("");
	EntityEngine::Register<Regeneration>();
	EntityEngine::Register<AIController>();
	EntityEngine::Register<ActionController>();
	EntityEngine::Register<BuffsDebuffs>();
	EntityEngine::Register<DeathController>();
	EntityEngine::Register<FinishBattle>();
	LOG("");

	EntityEngine ee = EntityEngine();

	{ Entity e = ee.CreateEntity<Character, Health, Stamina, Initiative, AI, YourParty>();
		Character& character = ee.Fragment<Character>(e);
		character.Label = "Brigand Thug with Rocks"; character.Attack = 25; character.Defense = 10;
		character.LowestDamage = 2; character.HighestDamage = 9;
		Health& health = ee.Fragment<Health>(e); health.Current = 80;
		health.Limit = 80; health.Regeneration = 1;
		Stamina& stamina = ee.Fragment<Stamina>(e); stamina.Current = 60;
		stamina.Limit = 60; stamina.Regeneration = 2;
		Initiative& initiative = ee.Fragment<Initiative>(e); initiative.Current = 0.0F;
		initiative.Regeneration = 11;
		AI& ai = ee.Fragment<AI>(e);
		{ Action& action = ai.Actions.emplace_back();
			action.Function = &Action::Rocks; action.InitiativeCost = 4.0F;
			action.StaminaCost = 11; action.Probability = 10; } }
	
	{ Entity e = ee.CreateEntity<Character, Health, Stamina, Initiative, AI, YourParty>();
		Character& character = ee.Fragment<Character>(e);
		character.Label = "Brigand Thug with Daggers"; character.Attack = 33; character.Defense = 7;
		character.LowestDamage = 4; character.HighestDamage = 7;
		Health& health = ee.Fragment<Health>(e); health.Current = 80;
		health.Limit = 80; health.Regeneration = 1;
		Stamina& stamina = ee.Fragment<Stamina>(e); stamina.Current = 70;
		stamina.Limit = 70; stamina.Regeneration = 3;
		Initiative& initiative = ee.Fragment<Initiative>(e); initiative.Current = 0.0F;
		initiative.Regeneration = 11;
		AI& ai = ee.Fragment<AI>(e);
		{ Action& action = ai.Actions.emplace_back();
			action.Function = &Action::Daggers; action.InitiativeCost = 4.5F;
			action.StaminaCost = 9; action.Probability = 10; } }

	{ Entity e = ee.CreateEntity<Character, Health, Stamina, Initiative, AI, YourParty>();
		Character& character = ee.Fragment<Character>(e);
		character.Label = "Brigand Thug with Crossbow"; character.Attack = 24; character.Defense = 13;
		character.LowestDamage = 3; character.HighestDamage = 5;
		Health& health = ee.Fragment<Health>(e); health.Current = 90;
		health.Limit = 90; health.Regeneration = 1;
		Stamina& stamina = ee.Fragment<Stamina>(e); stamina.Current = 50;
		stamina.Limit = 50; stamina.Regeneration = 1;
		Initiative& initiative = ee.Fragment<Initiative>(e); initiative.Current = 0.0F;
		initiative.Regeneration = 8;
		AI& ai = ee.Fragment<AI>(e);
		{ Action& action = ai.Actions.emplace_back();
			action.Function = &Action::Crossbow; action.InitiativeCost = 7.5F;
			action.StaminaCost = 20; action.Probability = 10; } }
	


	{ Entity e = ee.CreateEntity<Character, Health, Stamina, Initiative, AI, YourEnemies>();
		Character& character = ee.Fragment<Character>(e);
		character.Label = "Barbarian Thrall with Rocks"; character.Attack = 24; character.Defense = 13;
		character.LowestDamage = 3; character.HighestDamage = 11;
		Health& health = ee.Fragment<Health>(e); health.Current = 80;
		health.Limit = 80; health.Regeneration = 1;
		Stamina& stamina = ee.Fragment<Stamina>(e); stamina.Current = 80;
		stamina.Limit = 80; stamina.Regeneration = 3;
		Initiative& initiative = ee.Fragment<Initiative>(e); initiative.Current = 0.0F;
		initiative.Regeneration = 11;
		AI& ai = ee.Fragment<AI>(e);
		{ Action& action = ai.Actions.emplace_back();
			action.Function = &Action::Rocks; action.InitiativeCost = 4.0F;
			action.StaminaCost = 11; action.Probability = 10; } }
	
	{ Entity e = ee.CreateEntity<Character, Health, Stamina, Initiative, AI, YourEnemies>();
		Character& character = ee.Fragment<Character>(e);
		character.Label = "Barbarian Reaver with Bow"; character.Attack = 24; character.Defense = 13;
		character.LowestDamage = 4; character.HighestDamage = 9;
		Health& health = ee.Fragment<Health>(e); health.Current = 90;
		health.Limit = 90; health.Regeneration = 1;
		Stamina& stamina = ee.Fragment<Stamina>(e); stamina.Current = 80;
		stamina.Limit = 80; stamina.Regeneration = 4;
		Initiative& initiative = ee.Fragment<Initiative>(e); initiative.Current = 0.0F;
		initiative.Regeneration = 13;
		AI& ai = ee.Fragment<AI>(e);
		{ Action& action = ai.Actions.emplace_back();
			action.Function = &Action::Bow; action.InitiativeCost = 5.0F;
			action.StaminaCost = 17; action.Probability = 10; } }

	ee.PrintEntities();
	ee.PrintTables();

	for (size_t i = 0; true; ++i) {
		LOG_ERROR("Time: " << i);
		LOG("");
		ee.OnFrame(0.0625F);
		if (FinishBattle::OthersLength == 0) {
			if (FinishBattle::PartyLength == 0 || FinishBattle::EnemiesLength == 0)
				break;

		}

	}

}



void Action::Deffensive(EntityEngine& ee, ActionEvent& event)
{
	// "$XYZ takes a defensive stance, preparing to weather the upcoming storm of attacks.";
	// Attack -=
	// Defense +=
	// TODO:

}
void Action::Offensive(EntityEngine& ee, ActionEvent& event)
{
	// "XYZ shifts into an offensive stance, ready to unleash a flurry of strikes against their opponent.";
	// Attack +=
	// Defense -=
	// TODO:

}

void Action::Crossbow(EntityEngine& ee, ActionEvent& event)
{
	Entity your_entity = event.EntityEmitter;
	Character& your_character = ee.Fragment<Character>(your_entity);
	EntityResult target = FindTarget(ee, your_entity);
	if (target.Length == 0) return;
	Character& target_character = ee.Fragment<Character>(target.Ob);
	Health& target_health = ee.Fragment<Health>(target.Ob);

	int16_t value = rand() % (your_character.Attack + target_character.Defense);
	if (value < your_character.Attack) {
		int16_t damage = 4 * BETWEEN(your_character.LowestDamage, your_character.HighestDamage);
		target_health.Current -= damage;
		std::stringstream damage_str; damage_str << damage;
		std::string dialogue = "$X takes aim with their crossbow and lets loose a bolt, striking $Y for $V damage.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		dialogue.replace(dialogue.find("$V"), 2, damage_str.str());
		LOG_WARN(dialogue);

	}
	else {
		std::string dialogue = "$X fires a bolt from their crossbow, but misses the mark as it sails past $Y.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		LOG_WARN(dialogue);
		
	}

}
void Action::Bow(EntityEngine& ee, ActionEvent& event)
{
	Entity your_entity = event.EntityEmitter;
	Character& your_character = ee.Fragment<Character>(your_entity);
	EntityResult target = FindTarget(ee, your_entity);
	if (target.Length == 0) return;
	Character& target_character = ee.Fragment<Character>(target.Ob);
	Health& target_health = ee.Fragment<Health>(target.Ob);

	int16_t value = rand() % (your_character.Attack + target_character.Defense);
	if (value < your_character.Attack) {
		int16_t damage =  3 * BETWEEN(your_character.LowestDamage, your_character.HighestDamage);
		target_health.Current -= damage;
		std::stringstream damage_str; damage_str << damage;
		std::string dialogue = "$X takes aim with their bow and releases a precise shot at $Y, dealing $V damage.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		dialogue.replace(dialogue.find("$V"), 2, damage_str.str());
		LOG_WARN(dialogue);

	}
	else {
		std::string dialogue = "$X draws their bow and takes a shot at $Y, but misses the mark.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		LOG_WARN(dialogue);
		
	}

}
void Action::Daggers(EntityEngine& ee, ActionEvent& event)
{
	Entity your_entity = event.EntityEmitter;
	Character& your_character = ee.Fragment<Character>(your_entity);
	EntityResult target = FindTarget(ee, your_entity);
	if (target.Length == 0) return;
	Character& target_character = ee.Fragment<Character>(target.Ob);
	Health& target_health = ee.Fragment<Health>(target.Ob);

	int16_t value = rand() % (your_character.Attack + target_character.Defense);
	if (value < your_character.Attack) {
		int16_t damage = 2 * BETWEEN(your_character.LowestDamage, your_character.HighestDamage);
		target_health.Current -= damage;
		std::stringstream damage_str; damage_str << damage;
		std::string dialogue = "$X strikes $Y with a thrown dagger, dealing $V damage and poisoning them.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		dialogue.replace(dialogue.find("$V"), 2, damage_str.str());
		ee.Attach<Poisoning>(target.Ob);
		LOG_WARN(dialogue);

	}
	else {
		std::string dialogue = "$X launches an attack with their dagger aimed at $Y, but misjudges the distance, the blade falling short of its mark.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		LOG_WARN(dialogue);
		
	}

}
void Action::Rocks(EntityEngine& ee, ActionEvent& event)
{
	Entity your_entity = event.EntityEmitter;
	Character& your_character = ee.Fragment<Character>(your_entity);
	EntityResult target = FindTarget(ee, your_entity);
	if (target.Length == 0) return;
	Character& target_character = ee.Fragment<Character>(target.Ob);
	Health& target_health = ee.Fragment<Health>(target.Ob);

	int16_t value = rand() % (your_character.Attack + target_character.Defense);
	if (value < your_character.Attack) {
		int16_t damage = BETWEEN(your_character.LowestDamage, your_character.HighestDamage);
		target_health.Current -= damage;
		std::stringstream damage_str; damage_str << damage;
		std::string dialogue = "$X hurls a stone at $Y, striking them squarely and dealing $V damage. $Y staggers back, feeling dizzy from the blow.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		dialogue.replace(dialogue.find("$Y"), 2, target_character.Label);
		dialogue.replace(dialogue.find("$V"), 2, damage_str.str());
		LOG_WARN(dialogue);

	}
	else {
		std::string dialogue = "$X throws a stone, but it misses its mark and sails wide of its intended target.";
		dialogue.replace(dialogue.find("$X"), 2, your_character.Label);
		LOG_WARN(dialogue);

	}

}

void Action::Warhammer(EntityEngine& ee, ActionEvent& event)
{
	// TODO:

}
void Action::ConcussiveWarhammer(EntityEngine& ee, ActionEvent& event)
{
	// TODO:

}

void Action::LeftAxe(EntityEngine& ee, ActionEvent& event)
{
	// TODO:

}
void Action::RightAxe(EntityEngine& ee, ActionEvent& event)
{
	// TODO:

}
void Action::PowerfullAxe(EntityEngine& ee, ActionEvent& event)
{
	// TODO:

}

void Action::LeftSword(EntityEngine& ee, ActionEvent& event)
{
	// TODO:
}
void Action::RightSword(EntityEngine& ee, ActionEvent& event)
{
	// TODO:

}
void Action::PowerfullSword(EntityEngine& ee, ActionEvent& event)
{
	// TODO:

}
	