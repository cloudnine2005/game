#include "fight.h"
#include <limits> // 添加用于输入验证

// CharacterStats 实现
CharacterStats::CharacterStats(int hp, int atk, int def, int spd, float cr, float cd, float ehr, float eres)
    : maxHP(hp), currentHP(hp), attack(atk), defense(def), speed(spd), currentSpeed(spd),
    critRate(cr), critDamage(cd), effectHitRate(ehr), effectResistance(eres) {}

// BattleEffect 实现
BattleEffect::BattleEffect(std::string n, int dur, bool debuff,
    int atkMod, int defMod, int spdMod, float dmgMod)
    : name(n), duration(dur), stackCount(1), isDebuff(debuff),
    attackModifier(atkMod), defenseModifier(defMod),
    speedModifier(spdMod), damageTakenModifier(dmgMod) {}

void BattleEffect::decreaseDuration() {
    if (duration > 0) duration--;
}

// ActionInfo 实现
ActionInfo::ActionInfo(const std::string& name, int value, bool player)
    : characterName(name), actionValue(value), isPlayer(player) {}

bool ActionInfo::operator<(const ActionInfo& other) const {
    return actionValue > other.actionValue;
}

// Skill 实现
Skill::Skill(std::string n, std::string desc, DamageType type, int cost, int gain,
    bool ultimate, int avCost)
    : name(n), description(desc), damageType(type),
    energyCost(cost), energyGain(gain), isUltimate(ultimate), actionValueCost(avCost) {}

std::string Skill::getName() const { return name; }
std::string Skill::getDescription() const { return description; }
DamageType Skill::getDamageType() const { return damageType; }
bool Skill::getIsUltimate() const { return isUltimate; }
int Skill::getEnergyCost() const { return energyCost; }
int Skill::getEnergyGain() const { return energyGain; }
int Skill::getActionValueCost() const { return actionValueCost; }

// BattleCharacter 实现
BattleCharacter::BattleCharacter(std::string n, CharacterStats baseStats, bool playerControlled)
    : name(n), stats(baseStats), energy(0), maxEnergy(100), actionValue(0),
    isPlayerControlled(playerControlled) {}

void BattleCharacter::addSkill(std::shared_ptr<Skill> skill) {
    skills.push_back(skill);
}

void BattleCharacter::takeDamage(int damage, DamageType type) {
    int finalDamage = damage - getCurrentDefense();
    if (finalDamage < 1) finalDamage = 1;

    for (const auto& effect : effects) {
        finalDamage = static_cast<int>(finalDamage * effect.damageTakenModifier);
    }

    stats.currentHP -= finalDamage;
    if (stats.currentHP < 0) stats.currentHP = 0;

    std::cout << name << "受到了" << finalDamage << "点伤害！\n";
}

void BattleCharacter::heal(int amount) {
    stats.currentHP += amount;
    if (stats.currentHP > stats.maxHP) stats.currentHP = stats.maxHP;
    std::cout << name << "恢复了" << amount << "点生命值！\n";
}

void BattleCharacter::addEnergy(int amount) {
    energy += amount;
    if (energy > maxEnergy) energy = maxEnergy;
}

void BattleCharacter::addEffect(const BattleEffect& effect) {
    for (auto& existingEffect : effects) {
        if (existingEffect.name == effect.name) {
            existingEffect.stackCount++;
            existingEffect.duration = std::max(existingEffect.duration, effect.duration);
            return;
        }
    }
    effects.push_back(effect);
    updateCurrentSpeed();
}

void BattleCharacter::processEffects() {
    for (auto it = effects.begin(); it != effects.end(); ) {
        it->decreaseDuration();
        if (it->duration <= 0) {
            it = effects.erase(it);
        }
        else {
            ++it;
        }
    }
    updateCurrentSpeed();
}

void BattleCharacter::updateCurrentSpeed() {
    stats.currentSpeed = stats.speed;
    for (const auto& effect : effects) {
        stats.currentSpeed += effect.speedModifier;
    }
    stats.currentSpeed = std::max(0, stats.currentSpeed);
}

void BattleCharacter::advanceActionValue(int amount) {
    actionValue += amount;
}

bool BattleCharacter::canAct() const {
    return actionValue >= 10000;
}

void BattleCharacter::consumeActionValue(int cost) {
    actionValue -= cost;
}

int BattleCharacter::getTimeToNextAction() const {
    if (stats.currentSpeed <= 0) return 999999;
    return (10000 - actionValue) / stats.currentSpeed;
}

bool BattleCharacter::checkCriticalHit() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen) <= stats.critRate;
}

bool BattleCharacter::checkEffectHit(float baseChance, float targetResistance) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    float finalChance = baseChance * (1.0f + stats.effectHitRate) * (1.0f - targetResistance);
    return dis(gen) <= finalChance;
}

int BattleCharacter::getCurrentAttack() const {
    int attack = stats.attack;
    for (const auto& effect : effects) {
        attack += effect.attackModifier;
    }
    return std::max(0, attack);
}

int BattleCharacter::getCurrentDefense() const {
    int defense = stats.defense;
    for (const auto& effect : effects) {
        defense += effect.defenseModifier;
    }
    return std::max(0, defense);
}

int BattleCharacter::getCurrentSpeed() const {
    return stats.currentSpeed;
}

bool BattleCharacter::isAlive() const { return stats.currentHP > 0; }
std::string BattleCharacter::getName() const { return name; }
int BattleCharacter::getCurrentHP() const { return stats.currentHP; }
int BattleCharacter::getMaxHP() const { return stats.maxHP; }
int BattleCharacter::getEnergy() const { return energy; }
int BattleCharacter::getMaxEnergy() const { return maxEnergy; }
int BattleCharacter::getActionValue() const { return actionValue; }
const std::vector<std::shared_ptr<Skill>>& BattleCharacter::getSkills() const { return skills; }
bool BattleCharacter::getIsPlayerControlled() const { return isPlayerControlled; }
const std::vector<BattleEffect>& BattleCharacter::getEffects() const { return effects; }

void BattleCharacter::setEnergy(int value) { energy = value; }
void BattleCharacter::setActionValue(int value) { actionValue = value; }

// BasicAttack 实现
BasicAttack::BasicAttack(std::string n, DamageType type, float multiplier)
    : Skill(n, "普通攻击", type, 0, 20, false, 10000), damageMultiplier(multiplier) {}

void BasicAttack::execute(BattleCharacter& user, BattleCharacter& target) {
    int baseDamage = static_cast<int>(user.getCurrentAttack() * damageMultiplier);
    bool isCrit = user.checkCriticalHit();
    int finalDamage = isCrit ? static_cast<int>(baseDamage * (1.0f + 0.5f)) : baseDamage;

    std::cout << user.getName() << "对" << target.getName() << "使用了" << name << "！\n";
    if (isCrit) {
        std::cout << "暴击！";
        finalDamage = static_cast<int>(finalDamage * (1.0f + 0.5f));
    }

    target.takeDamage(finalDamage, damageType);
    user.addEnergy(energyGain);
    user.consumeActionValue(actionValueCost);
}

// BattleSkill 实现
BattleSkill::BattleSkill(std::string n, std::string desc, DamageType type,
    float multiplier, float eChance, const BattleEffect& effect, int cost)
    : Skill(n, desc, type, cost, 30, false, 10000), damageMultiplier(multiplier),
    effectChance(eChance), possibleEffect(effect) {}

void BattleSkill::execute(BattleCharacter& user, BattleCharacter& target) {
    int baseDamage = static_cast<int>(user.getCurrentAttack() * damageMultiplier);
    bool isCrit = user.checkCriticalHit();
    int finalDamage = isCrit ? static_cast<int>(baseDamage * (1.0f + 0.5f)) : baseDamage;

    std::cout << user.getName() << "对" << target.getName() << "使用了" << name << "！\n";
    if (isCrit) {
        std::cout << "暴击！";
        finalDamage = static_cast<int>(finalDamage * (1.0f + 0.5f));
    }

    target.takeDamage(finalDamage, damageType);

    if (effectChance > 0 && user.checkEffectHit(effectChance, 0.0f)) {
        target.addEffect(possibleEffect);
        std::cout << target.getName() << "获得了" << possibleEffect.name << "效果！\n";
    }

    user.addEnergy(energyGain);
    user.consumeActionValue(actionValueCost);
}

// UltimateSkill 实现
UltimateSkill::UltimateSkill(std::string n, std::string desc, DamageType type,
    float multiplier, const BattleEffect& effect)
    : Skill(n, desc, type, 100, 0, true, 0), damageMultiplier(multiplier),
    guaranteedEffect(effect) {}

void UltimateSkill::execute(BattleCharacter& user, BattleCharacter& target) {
    if (user.getEnergy() < energyCost) {
        std::cout << "能量不足！\n";
        return;
    }

    user.setEnergy(user.getEnergy() - energyCost);

    int baseDamage = static_cast<int>(user.getCurrentAttack() * damageMultiplier);
    bool isCrit = user.checkCriticalHit();
    int finalDamage = isCrit ? static_cast<int>(baseDamage * (1.0f + 0.5f)) : baseDamage;

    std::cout << user.getName() << "对" << target.getName() << "使用了终结技：" << name << "！\n";
    if (isCrit) {
        std::cout << "暴击！";
        finalDamage = static_cast<int>(finalDamage * (1.0f + 0.5f));
    }

    target.takeDamage(finalDamage, damageType);

    target.addEffect(guaranteedEffect);
    std::cout << target.getName() << "获得了" << guaranteedEffect.name << "效果！\n";
}

// BattleSystem 实现
BattleSystem::BattleSystem(const std::vector<BattleCharacter>& players, const std::vector<BattleCharacter>& enemies)
    : playerParty(players), enemyParty(enemies), currentState(BattleState::PRE_BATTLE), turnCounter(0) {}

void BattleSystem::startBattle() {
    std::cout << "战斗开始！\n";
    currentState = BattleState::IN_BATTLE;
    turnCounter = 0;

    for (auto& character : playerParty) {
        if (character.isAlive()) {
            character.setActionValue(0);
        }
    }
    for (auto& character : enemyParty) {
        if (character.isAlive()) {
            character.setActionValue(0);
        }
    }

    processBattle();
}

void BattleSystem::processBattle() {
    while (currentState == BattleState::IN_BATTLE) {
        advanceActionValues();

        BattleCharacter* nextActor = getNextActor();
        if (nextActor) {
            if (nextActor->getIsPlayerControlled()) {
                playerAction(*nextActor);
            }
            else {
                enemyAction(*nextActor);
            }
        }

        checkBattleEnd();
    }
}

void BattleSystem::advanceActionValues() {
    for (auto& character : playerParty) {
        if (character.isAlive()) {
            character.advanceActionValue(character.getCurrentSpeed());
            character.processEffects();
        }
    }
    for (auto& character : enemyParty) {
        if (character.isAlive()) {
            character.advanceActionValue(character.getCurrentSpeed());
            character.processEffects();
        }
    }
}

BattleCharacter* BattleSystem::getNextActor() {
    BattleCharacter* nextActor = nullptr;
    int minActionValue = INT_MAX;

    for (auto& character : playerParty) {
        if (character.isAlive() && character.canAct() && character.getActionValue() < minActionValue) {
            minActionValue = character.getActionValue();
            nextActor = &character;
        }
    }

    for (auto& character : enemyParty) {
        if (character.isAlive() && character.canAct() && character.getActionValue() < minActionValue) {
            minActionValue = character.getActionValue();
            nextActor = &character;
        }
    }

    return nextActor;
}

// 输入验证辅助函数
int getValidatedInput(int min, int max) {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请输入数字 (" << min << "-" << max << "): ";
        }
        else if (input < min || input > max) {
            std::cout << "输入超出范围，请重新输入 (" << min << "-" << max << "): ";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}

void BattleSystem::playerAction(BattleCharacter& actor) {
    std::cout << "\n=== " << actor.getName() << "的行动回合 ===\n";
    turnCounter++;

    int choice;
    while (true) {
        std::cout << "\n选择行动:\n";
        std::cout << "1. 使用技能\n";
        std::cout << "2. 查看角色属性\n";
        std::cout << "3. 查看战场状态\n";
        std::cout << "4. 终止战斗并返回主菜单\n";
        std::cout << "请选择 (1-4): ";

        choice = getValidatedInput(1, 4);

        if (choice == 2) {
            // 查看属性
            std::cout << "\n选择要查看的角色:\n";
            std::cout << "=== 我方角色 ===\n";
            for (int i = 0; i < playerParty.size(); i++) {
                if (playerParty[i].isAlive()) {
                    std::cout << i + 1 << ". " << playerParty[i].getName() << "\n";
                }
            }
            std::cout << "=== 敌方角色 ===\n";
            for (int i = 0; i < enemyParty.size(); i++) {
                if (enemyParty[i].isAlive()) {
                    std::cout << i + playerParty.size() + 1 << ". " << enemyParty[i].getName() << "\n";
                }
            }
            std::cout << "0. 返回\n";
            std::cout << "选择角色: ";

            int viewChoice = getValidatedInput(0, playerParty.size() + enemyParty.size());

            if (viewChoice == 0) continue;

            if (viewChoice > 0 && viewChoice <= playerParty.size()) {
                displayCharacterDetails(playerParty[viewChoice - 1]);
            }
            else if (viewChoice > playerParty.size() && viewChoice <= playerParty.size() + enemyParty.size()) {
                int enemyIndex = viewChoice - playerParty.size() - 1;
                displayCharacterDetails(enemyParty[enemyIndex]);
            }
            continue;
        }
        else if (choice == 3) {
            // 查看战场状态
            displayBattleStatus();
            continue;
        }
        else if (choice == 4) {
            // 终止战斗
            currentState = BattleState::FLEE;
            std::cout << "战斗已终止，返回主菜单...\n";
            return;
        }
        else if (choice == 1) {
            break; // 进入技能选择
        }
    }

    displayBattleStatus();

    int skillIndex = 0;
    std::cout << "可用技能:\n";
    for (const auto& skill : actor.getSkills()) {
        std::cout << skillIndex + 1 << ". " << skill->getName();
        if (skill->getIsUltimate()) {
            std::cout << " (终结技 - 能量: " << actor.getEnergy() << "/" << actor.getMaxEnergy() << ")";
        }
        else {
            std::cout << " (行动值消耗: " << skill->getActionValueCost() / 100 << ")";
        }
        std::cout << " - " << skill->getDescription() << "\n";
        skillIndex++;
    }

    std::cout << "选择技能 (1-" << skillIndex << "): ";
    int chosenSkill = getValidatedInput(1, skillIndex);
    chosenSkill--;

    std::cout << "选择目标:\n";
    std::vector<int> aliveEnemies;
    for (int i = 0; i < enemyParty.size(); i++) {
        if (enemyParty[i].isAlive()) {
            aliveEnemies.push_back(i);
            std::cout << aliveEnemies.size() << ". " << enemyParty[i].getName()
                << " HP: " << enemyParty[i].getCurrentHP() << "/" << enemyParty[i].getMaxHP() << "\n";
        }
    }

    if (aliveEnemies.empty()) {
        std::cout << "没有可用的目标！\n";
        return;
    }

    std::cout << "选择目标 (1-" << aliveEnemies.size() << "): ";
    int targetChoice = getValidatedInput(1, aliveEnemies.size());
    int targetIndex = aliveEnemies[targetChoice - 1];

    actor.getSkills()[chosenSkill]->execute(actor, enemyParty[targetIndex]);
}

void BattleSystem::enemyAction(BattleCharacter& actor) {
    std::cout << "\n=== " << actor.getName() << "的行动回合 ===\n";
    turnCounter++;

    std::shared_ptr<Skill> chosenSkill = nullptr;

    for (const auto& skill : actor.getSkills()) {
        if (skill->getIsUltimate() && actor.getEnergy() >= skill->getEnergyCost()) {
            chosenSkill = skill;
            break;
        }
    }

    if (!chosenSkill) {
        std::vector<std::shared_ptr<Skill>> availableSkills;
        for (const auto& skill : actor.getSkills()) {
            if (!skill->getIsUltimate()) {
                availableSkills.push_back(skill);
            }
        }

        if (!availableSkills.empty()) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, availableSkills.size() - 1);
            chosenSkill = availableSkills[dis(gen)];
        }
    }

    std::vector<int> alivePlayers;
    for (int i = 0; i < playerParty.size(); i++) {
        if (playerParty[i].isAlive()) {
            alivePlayers.push_back(i);
        }
    }

    if (!alivePlayers.empty() && chosenSkill) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, alivePlayers.size() - 1);
        int targetIndex = alivePlayers[dis(gen)];

        chosenSkill->execute(actor, playerParty[targetIndex]);
    }
}

void BattleSystem::displayBattleStatus() {
    std::cout << "\n战斗状态 (回合: " << turnCounter << "):\n";

    std::cout << "我方:\n";
    for (const auto& character : playerParty) {
        std::cout << "  " << character.getName() << " HP: " << character.getCurrentHP() << "/" << character.getMaxHP()
            << " 能量: " << character.getEnergy() << " 行动值: " << character.getActionValue() / 100;
        if (!character.getEffects().empty()) {
            std::cout << " [";
            for (const auto& effect : character.getEffects()) {
                std::cout << effect.name << "(" << effect.duration << ") ";
            }
            std::cout << "]";
        }
        std::cout << "\n";
    }

    std::cout << "敌方:\n";
    for (const auto& character : enemyParty) {
        std::cout << "  " << character.getName() << " HP: " << character.getCurrentHP() << "/" << character.getMaxHP()
            << " 行动值: " << character.getActionValue() / 100;
        if (!character.getEffects().empty()) {
            std::cout << " [";
            for (const auto& effect : character.getEffects()) {
                std::cout << effect.name << "(" << effect.duration << ") ";
            }
            std::cout << "]";
        }
        std::cout << "\n";
    }
}

void BattleSystem::displayCharacterDetails(const BattleCharacter& character) const {
    std::cout << "\n=== " << character.getName() << " 角色详情 ===\n";
    std::cout << "生命值: " << character.getCurrentHP() << "/" << character.getMaxHP() << "\n";
    std::cout << "能量: " << character.getEnergy() << "/" << character.getMaxEnergy() << "\n";
    std::cout << "行动值: " << character.getActionValue() / 100 << "\n";
    std::cout << "攻击力: " << character.getCurrentAttack() << "\n";
    std::cout << "防御力: " << character.getCurrentDefense() << "\n";
    std::cout << "速度: " << character.getCurrentSpeed() << "\n";

    // 显示技能信息
    std::cout << "\n技能列表:\n";
    int skillIndex = 1;
    for (const auto& skill : character.getSkills()) {
        std::cout << skillIndex << ". " << skill->getName();
        if (skill->getIsUltimate()) {
            std::cout << " (终结技)";
        }
        std::cout << " - " << skill->getDescription() << "\n";
        skillIndex++;
    }

    // 显示效果信息
    if (!character.getEffects().empty()) {
        std::cout << "\n当前效果:\n";
        for (const auto& effect : character.getEffects()) {
            std::cout << "  " << effect.name << " ("
                << (effect.isDebuff ? "减益" : "增益")
                << ") - 剩余回合: " << effect.duration
                << " - 层数: " << effect.stackCount << "\n";
        }
    }
    else {
        std::cout << "\n当前无任何效果\n";
    }

    std::cout << "======================\n";
}

void BattleSystem::checkBattleEnd() {
    bool allPlayersDead = true;
    for (const auto& player : playerParty) {
        if (player.isAlive()) {
            allPlayersDead = false;
            break;
        }
    }

    if (allPlayersDead) {
        currentState = BattleState::DEFEAT;
        std::cout << "战斗失败！\n";
        return;
    }

    bool allEnemiesDead = true;
    for (const auto& enemy : enemyParty) {
        if (enemy.isAlive()) {
            allEnemiesDead = false;
            break;
        }
    }

    if (allEnemiesDead) {
        currentState = BattleState::VICTORY;
        std::cout << "战斗胜利！\n";
        return;
    }
}

BattleState BattleSystem::getCurrentState() const { return currentState; }