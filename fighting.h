#pragma once

#include <vector>
#include "fight.h"
#include "data.h"

void displayMainMenu();
void displayCharacterSelection();
void displayEnemySelection();
void displayGlobalCharacterInfo();
std::vector<BattleCharacter> createCustomPlayerParty();
std::vector<BattleCharacter> createCustomEnemyParty();
int fighting();
