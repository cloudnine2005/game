#ifndef FIGHT_H
#define FIGHT_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <random>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <climits>

// ս��״̬ö��
enum class BattleState {
    PRE_BATTLE,
    IN_BATTLE,
    VICTORY,
    DEFEAT,
    FLEE
};

// �˺�����ö��
enum class DamageType {
    PHYSICAL,
    FIRE,
    ICE,
    LIGHTNING,
    WIND,
    QUANTUM,
    IMAGINARY
};

// ��ɫ״̬�ṹ
struct CharacterStats {
    int maxHP;
    int currentHP;
    int attack;
    int defense;
    int speed;          // �ٶ�����
    int currentSpeed;   // ��ǰ�ٶȣ���Ч��Ӱ�죩
    float critRate;     // ������
    float critDamage;   // �����˺�
    float effectHitRate; // Ч������
    float effectResistance; // Ч���ֿ�

    // ���Ĭ�Ϲ��캯��
    CharacterStats() : maxHP(0), currentHP(0), attack(0), defense(0),
        speed(0), currentSpeed(0), critRate(0.0f),
        critDamage(0.0f), effectHitRate(0.0f), effectResistance(0.0f) {}

    CharacterStats(int hp, int atk, int def, int spd, float cr = 0.05, float cd = 0.5, float ehr = 0.0, float eres = 0.0);
};

// ս��Ч����buff/debuff��
struct BattleEffect {
    std::string name;
    int duration;
    int stackCount;
    bool isDebuff;

    // Ч�������޸�
    int attackModifier;
    int defenseModifier;
    int speedModifier;
    float damageTakenModifier;

    BattleEffect(std::string n, int dur, bool debuff = false,
        int atkMod = 0, int defMod = 0, int spdMod = 0, float dmgMod = 1.0f);

    void decreaseDuration();
};

// �ж���Ϣ
struct ActionInfo {
    std::string characterName;
    int actionValue;  // �ж�ֵ
    bool isPlayer;

    ActionInfo(const std::string& name, int value, bool player);

    // �������ȶ��бȽ�
    bool operator<(const ActionInfo& other) const;
};

// ǰ������
class BattleCharacter;

// ���ܻ���
class Skill {
protected:
    std::string name;
    std::string description;
    DamageType damageType;
    int energyCost;
    int energyGain;
    bool isUltimate;
    int actionValueCost; // �ж�ֵ����

public:
    Skill(std::string n, std::string desc, DamageType type, int cost = 0, int gain = 0,
        bool ultimate = false, int avCost = 100);
    virtual ~Skill() = default;

    virtual void execute(BattleCharacter& user, BattleCharacter& target) = 0;

    std::string getName() const;
    std::string getDescription() const;
    DamageType getDamageType() const;
    bool getIsUltimate() const;
    int getEnergyCost() const;
    int getEnergyGain() const;
    int getActionValueCost() const;
};

// ս����ɫ��
class BattleCharacter {
private:
    std::string name;
    CharacterStats stats;
    int energy;
    int maxEnergy;
    int actionValue; // ��ǰ�ж�ֵ
    std::vector<std::shared_ptr<Skill>> skills;
    std::vector<BattleEffect> effects;
    bool isPlayerControlled;

public:
    // ���Ĭ�Ϲ��캯��
    BattleCharacter() : name(""), stats(0, 0, 0, 0), energy(0), maxEnergy(100),
        actionValue(0), isPlayerControlled(false) {}

    BattleCharacter(std::string n, CharacterStats baseStats, bool playerControlled = false);

    void addSkill(std::shared_ptr<Skill> skill);
    void takeDamage(int damage, DamageType type);
    void heal(int amount);
    void addEnergy(int amount);
    void addEffect(const BattleEffect& effect);
    void processEffects();
    void updateCurrentSpeed();
    void advanceActionValue(int amount = 1);
    bool canAct() const;
    void consumeActionValue(int cost);
    int getTimeToNextAction() const;
    bool checkCriticalHit();
    bool checkEffectHit(float baseChance, float targetResistance);
    int getCurrentAttack() const;
    int getCurrentDefense() const;
    int getCurrentSpeed() const;
    bool isAlive() const;
    std::string getName() const;
    int getCurrentHP() const;
    int getMaxHP() const;
    int getEnergy() const;
    int getMaxEnergy() const;
    int getActionValue() const;
    const std::vector<std::shared_ptr<Skill>>& getSkills() const;
    bool getIsPlayerControlled() const;
    const std::vector<BattleEffect>& getEffects() const;

    void setEnergy(int value);
    void setActionValue(int value);
};

// ��ͨ��������
class BasicAttack : public Skill {
private:
    float damageMultiplier;

public:
    BasicAttack(std::string n, DamageType type, float multiplier = 1.0f);
    void execute(BattleCharacter& user, BattleCharacter& target) override;
};

// ս��
class BattleSkill : public Skill {
private:
    float damageMultiplier;
    float effectChance;
    BattleEffect possibleEffect;

public:
    BattleSkill(std::string n, std::string desc, DamageType type,
        float multiplier = 1.0f, float eChance = 0.0f,
        const BattleEffect& effect = BattleEffect("", 0), int cost = 0);
    void execute(BattleCharacter& user, BattleCharacter& target) override;
};

// �սἼ
class UltimateSkill : public Skill {
private:
    float damageMultiplier;
    BattleEffect guaranteedEffect;

public:
    UltimateSkill(std::string n, std::string desc, DamageType type,
        float multiplier = 1.0f, const BattleEffect& effect = BattleEffect("", 0));
    void execute(BattleCharacter& user, BattleCharacter& target) override;
};

// ս��ϵͳ��
class BattleSystem {
private:
    std::vector<BattleCharacter> playerParty;
    std::vector<BattleCharacter> enemyParty;
    BattleState currentState;
    int turnCounter;
    std::priority_queue<ActionInfo> actionQueue;

public:
    BattleSystem(const std::vector<BattleCharacter>& players, const std::vector<BattleCharacter>& enemies);
    void startBattle();
    void processBattle();
    void advanceActionValues();
    BattleCharacter* getNextActor();
    void playerAction(BattleCharacter& actor);
    void enemyAction(BattleCharacter& actor);
    void displayBattleStatus();
    void displayCharacterDetails(const BattleCharacter& character) const;
    void checkBattleEnd();
    BattleState getCurrentState() const;
};

int getValidatedInput(int min, int max);

#endif // FIGHT_H