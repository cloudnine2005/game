#ifndef DATA_H
#define DATA_H

#include "fight.h"
#include <vector>
#include <memory>

// 玩家角色数据
namespace PlayerCharacters {
    // 开拓者（物理）
    inline BattleCharacter createTrailblazerPhysical() {
        CharacterStats stats(270, 25, 12, 240, 0.5f, 1.5f, 0.1f, 0.2f);
        BattleCharacter character("开拓者·物理", stats, true);

        auto basicAttack = std::make_shared<BasicAttack>("普通攻击", DamageType::PHYSICAL, 1.0f);
        auto battleSkill = std::make_shared<BattleSkill>("战技·裂空斩", "造成物理伤害并有几率使敌人防御降低",
            DamageType::PHYSICAL, 1.8f, 0.7f,
            BattleEffect("防御降低", 2, true, 0, -8));
        auto ultimate = std::make_shared<UltimateSkill>("终结技·天崩地裂", "造成大量物理伤害并必定使敌人防御大幅降低",
            DamageType::PHYSICAL, 3.0f,
            BattleEffect("防御大幅降低", 3, true, 0, -15));

        character.addSkill(basicAttack);
        character.addSkill(battleSkill);
        character.addSkill(ultimate);

        return character;
    }

    // 三月七
    inline BattleCharacter createMarch7th() {
        CharacterStats stats(120, 18, 15, 220, 0.08f, 0.4f, 0.2f, 0.3f);
        BattleCharacter character("三月七", stats, true);

        auto basicAttack = std::make_shared<BasicAttack>("普通攻击", DamageType::ICE, 0.9f);
        auto battleSkill = std::make_shared<BattleSkill>("战技·冰晶", "造成冰属性伤害并有几率冻结敌人",
            DamageType::ICE, 1.2f, 0.6f,
            BattleEffect("冻结", 1, true, 0, 0, -20, 1.2f));
        auto ultimate = std::make_shared<UltimateSkill>("终结技·极寒领域", "造成冰属性伤害并必定冻结敌人",
            DamageType::ICE, 2.2f,
            BattleEffect("深度冻结", 2, true, 0, 0, -30, 1.3f));

        character.addSkill(basicAttack);
        character.addSkill(battleSkill);
        character.addSkill(ultimate);

        return character;
    }

    // 丹恒
    inline BattleCharacter createDanHeng() {
        CharacterStats stats(130, 28, 10, 260, 0.75f, 2.6f, 0.1f, 0.1f);
        BattleCharacter character("丹恒", stats, true);

        auto basicAttack = std::make_shared<BasicAttack>("普通攻击", DamageType::WIND, 1.1f);
        auto battleSkill = std::make_shared<BattleSkill>("战技·疾风突刺", "造成风属性伤害并有几率使敌人速度降低",
            DamageType::WIND, 1.6f, 0.8f,
            BattleEffect("速度降低", 2, true, 0, 0, -15));
        auto ultimate = std::make_shared<UltimateSkill>("终结技·龙卷风暴", "造成大量风属性伤害并必定使敌人速度大幅降低",
            DamageType::WIND, 2.8f,
            BattleEffect("速度大幅降低", 3, true, 0, 0, -25));

        character.addSkill(basicAttack);
        character.addSkill(battleSkill);
        character.addSkill(ultimate);

        return character;
    }

    inline void displayCharacterInfo(const BattleCharacter& character) {
        std::cout << "\n=== 角色信息 ===\n";
        std::cout << "名称: " << character.getName() << "\n";
        std::cout << "生命值: " << character.getCurrentHP() << "/" << character.getMaxHP() << "\n";
        std::cout << "攻击力: " << character.getCurrentAttack() << "\n";
        std::cout << "防御力: " << character.getCurrentDefense() << "\n";
        std::cout << "速度: " << character.getCurrentSpeed() << "\n";
    }
}

// 敌人数据
namespace EnemyCharacters {
    // 银鬃近卫
    inline BattleCharacter createSilvermaneGuard() {
        CharacterStats stats(250, 15, 8, 120, 0.05f, 0.5f, 0.0f, 0.1f);
        BattleCharacter enemy("银鬃近卫", stats);

        auto basicAttack = std::make_shared<BasicAttack>("劈砍", DamageType::PHYSICAL, 1.0f);
        auto battleSkill = std::make_shared<BattleSkill>("重击", "造成物理伤害",
            DamageType::PHYSICAL, 1.3f);

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);

        return enemy;
    }

    // 银鬃射手
    inline BattleCharacter createSilvermaneSniper() {
        CharacterStats stats(200, 20, 6, 180, 0.1f, 0.6f, 0.1f, 0.0f);
        BattleCharacter enemy("银鬃射手", stats);

        auto basicAttack = std::make_shared<BasicAttack>("射击", DamageType::PHYSICAL, 1.1f);
        auto battleSkill = std::make_shared<BattleSkill>("精准射击", "造成物理伤害",
            DamageType::PHYSICAL, 1.5f);
        auto ultimate = std::make_shared<UltimateSkill>("连射", "快速射击多次",
            DamageType::PHYSICAL, 2.0f);

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }

    // 外宇宙之冰
    inline BattleCharacter createOutspaceIce() {
        CharacterStats stats(750, 18, 12, 100, 0.03f, 0.4f, 0.2f, 0.3f);
        BattleCharacter enemy("外宇宙之冰", stats);

        auto basicAttack = std::make_shared<BasicAttack>("冰锥", DamageType::ICE, 1.0f);
        auto battleSkill = std::make_shared<BattleSkill>("寒冰吐息", "造成冰属性伤害并有几率冻结目标",
            DamageType::ICE, 1.4f, 0.3f,
            BattleEffect("冻结", 1, true, 0, 0, -10, 1.1f));
        auto ultimate = std::make_shared<UltimateSkill>("绝对零度", "造成冰属性伤害并降低敌人速度",
            DamageType::ICE, 2.2f,
            BattleEffect("速度降低", 2, true, 0, 0, -20));

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }

    // 自动机兵·齿狼
    inline BattleCharacter createAutomatonWolf() {
        CharacterStats stats(600, 22, 10, 200, 0.08f, 0.5f, 0.0f, 0.2f);
        BattleCharacter enemy("自动机兵·齿狼", stats);

        auto basicAttack = std::make_shared<BasicAttack>("撕咬", DamageType::PHYSICAL, 1.2f);
        auto battleSkill = std::make_shared<BattleSkill>("利爪连击", "快速攻击多次",
            DamageType::PHYSICAL, 1.8f);
        auto ultimate = std::make_shared<UltimateSkill>("狂暴模式", "进入狂暴状态，攻击力大幅提升",
            DamageType::PHYSICAL, 1.0f,
            BattleEffect("狂暴", 3, false, 10, 0, 0, 0.9f));

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }

    // 末日兽
    inline BattleCharacter createDoomsdayBeast() {
        CharacterStats stats(3000, 30, 20, 80, 0.15f, 0.7f, 0.3f, 0.4f);
        BattleCharacter enemy("末日兽", stats);

        auto basicAttack = std::make_shared<BasicAttack>("毁灭重击", DamageType::PHYSICAL, 1.5f);
        auto battleSkill = std::make_shared<BattleSkill>("能量爆发", "造成量子伤害",
            DamageType::QUANTUM, 2.0f);
        auto ultimate = std::make_shared<UltimateSkill>("末日审判", "造成巨大伤害并降低敌人防御",
            DamageType::QUANTUM, 3.5f,
            BattleEffect("防御崩溃", 3, true, 0, -12));

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }
}

// 队伍创建函数
namespace PartyCreator {
    inline std::vector<BattleCharacter> createPlayerParty() {
        return {
            PlayerCharacters::createTrailblazerPhysical(),
            PlayerCharacters::createMarch7th(),
            PlayerCharacters::createDanHeng()
        };
    }

    inline std::vector<BattleCharacter> createPlayerPartyone() {
        return {
            PlayerCharacters::createTrailblazerPhysical()
        };
    }

    inline std::vector<BattleCharacter> createPlayerPartytwo() {
        return {
            PlayerCharacters::createTrailblazerPhysical(),
            PlayerCharacters::createMarch7th()
        };
    }

    inline std::vector<BattleCharacter> createEasyEnemyParty() {
        return {
            EnemyCharacters::createSilvermaneGuard(),
            EnemyCharacters::createSilvermaneSniper()
        };
    }

    inline std::vector<BattleCharacter> createMediumEnemyParty() {
        return {
            EnemyCharacters::createAutomatonWolf(),
            EnemyCharacters::createOutspaceIce(),
            EnemyCharacters::createSilvermaneSniper()
        };
    }

    inline std::vector<BattleCharacter> createBossEnemyParty() {
        return {
            EnemyCharacters::createDoomsdayBeast(),
            EnemyCharacters::createAutomatonWolf()
        };
    }
}

#endif // DATA_H