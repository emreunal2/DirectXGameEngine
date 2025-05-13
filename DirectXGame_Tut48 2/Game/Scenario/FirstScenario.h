#pragma once
#include "Scenario.h"
class FirstScenario : public Scenario
{
public:
	FirstScenario(Game* game);
	~FirstScenario();
	void generateScenario();
	void onRestart();
	void onCreate();
	void onUpdate(f32 deltaTime);

};

