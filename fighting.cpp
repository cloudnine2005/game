#include "fight.h"
#include "data.h"
#include <iostream>
#include <limits> // 添加用于输入验证

//// 输入验证辅助函数
//int getValidatedInput(int min, int max) {
//    int input;
//    while (true) {
//        std::cin >> input;
//        if (std::cin.fail()) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            std::cout << "输入无效，请输入数字 (" << min << "-" << max << "): ";
//        }
//        else if (input < min || input > max) {
//            std::cout << "输入超出范围，请重新输入 (" << min << "-" << max << "): ";
//        }
//        else {
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            return input;
//        }
//    }
//}

void displayMainMenu() {
    std::cout << "=== 战斗模拟器 ===\n";
    std::cout << "1. 简单战斗 (银鬃近卫 + 银鬃射手)\n";
    std::cout << "2. 中等战斗 (自动机兵 + 外宇宙之冰 + 银鬃射手)\n";
    std::cout << "3. BOSS战 (末日兽 + 自动机兵)\n";
    std::cout << "4. 自定义队伍\n";
    std::cout << "5. 查看角色图鉴\n";
    std::cout << "0. 退出\n";
    std::cout << "请选择: ";
}

void displayCharacterSelection() {
    std::cout << "\n=== 选择星穹角色 ===\n";
    std::cout << "1. 开拓者·物理\n";
    std::cout << "2. 三月七\n";
    std::cout << "3. 丹恒\n";
    std::cout << "请选择角色 (输入序号，0结束选择): ";
}

void displayEnemySelection() {
    std::cout << "\n=== 选择敌人 ===\n";
    std::cout << "1. 银鬃近卫\n";
    std::cout << "2. 银鬃射手\n";
    std::cout << "3. 外宇宙之冰\n";
    std::cout << "4. 自动机兵·狼\n";
    std::cout << "5. 末日兽\n";
    std::cout << "请选择敌人 (输入序号，0结束选择): ";
}

void displayGlobalCharacterInfo() {
    std::cout << "\n=== 角色图鉴 ===\n";

    std::cout << "\n=== 星穹角色 ===\n";
    std::cout << "1. 开拓者·物理 - HP:150 攻击:25 防御:12 速度:240\n";
    std::cout << "2. 三月七 - HP:120 攻击:18 防御:15 速度:220\n";
    std::cout << "3. 丹恒 - HP:130 攻击:28 防御:10 速度:260\n";

    std::cout << "\n=== 敌人角色 ===\n";
    std::cout << "1. 银鬃近卫 - HP:1000 攻击:15 防御:8 速度:120\n";
    std::cout << "2. 银鬃射手 - HP:800 攻击:20 防御:6 速度:180\n";
    std::cout << "3. 外宇宙之冰 - HP:1500 攻击:18 防御:12 速度:100\n";
    std::cout << "4. 自动机兵·狼 - HP:1200 攻击:22 防御:10 速度:200\n";
    std::cout << "5. 末日兽 - HP:3000 攻击:30 防御:20 速度:80\n";
}

std::vector<BattleCharacter> createCustomPlayerParty() {
    std::vector<BattleCharacter> party;
    int choice;

    std::cout << "\n创建自定义星穹队伍 (最多3人):\n";

    for (int i = 0; i < 3; i++) {
        displayCharacterSelection();
        choice = getValidatedInput(0, 3);

        if (choice == 0) break;

        BattleCharacter newCharacter;
        switch (choice) {
        case 1:
            newCharacter = PlayerCharacters::createTrailblazerPhysical();
            std::cout << "已选择: 开拓者·物理\n";
            break;
        case 2:
            newCharacter = PlayerCharacters::createMarch7th();
            std::cout << "已选择: 三月七\n";
            break;
        case 3:
            newCharacter = PlayerCharacters::createDanHeng();
            std::cout << "已选择: 丹恒\n";
            break;
        default:
            std::cout << "无效选择!\n";
            i--;
            continue;
        }
        PlayerCharacters::displayCharacterInfo(newCharacter);
        party.push_back(newCharacter);
    }

    if (party.empty()) {
        std::cout << "队伍为空，使用默认队伍\n";
        party = PartyCreator::createPlayerParty();
    }

    return party;
}

std::vector<BattleCharacter> createCustomEnemyParty() {
    std::vector<BattleCharacter> party;
    int choice;

    std::cout << "\n创建自定义敌人队伍:\n";

    while (true) {
        displayEnemySelection();
        choice = getValidatedInput(0, 5);

        if (choice == 0) break;

        switch (choice) {
        case 1:
            party.push_back(EnemyCharacters::createSilvermaneGuard());
            std::cout << "已选择: 银鬃近卫\n";
            break;
        case 2:
            party.push_back(EnemyCharacters::createSilvermaneSniper());
            std::cout << "已选择: 银鬃射手\n";
            break;
        case 3:
            party.push_back(EnemyCharacters::createOutspaceIce());
            std::cout << "已选择: 外宇宙之冰\n";
            break;
        case 4:
            party.push_back(EnemyCharacters::createAutomatonWolf());
            std::cout << "已选择: 自动机兵·狼\n";
            break;
        case 5:
            party.push_back(EnemyCharacters::createDoomsdayBeast());
            std::cout << "已选择: 末日兽\n";
            break;
        default:
            std::cout << "无效选择!\n";
            break;
        }
    }

    if (party.empty()) {
        std::cout << "敌人队伍为空，使用默认敌人\n";
        party = PartyCreator::createEasyEnemyParty();
    }

    return party;
}

int fighting() {
    int choice;

    while (true) {
        displayMainMenu();
        choice = getValidatedInput(0, 5);

        if (choice == 0) break;

        std::vector<BattleCharacter> playerParty;
        std::vector<BattleCharacter> enemyParty;

        switch (choice) {
        case 1:
            playerParty = PartyCreator::createPlayerParty();
            enemyParty = PartyCreator::createEasyEnemyParty();
            break;
        case 2:
            playerParty = PartyCreator::createPlayerParty();
            enemyParty = PartyCreator::createMediumEnemyParty();
            break;
        case 3:
            playerParty = PartyCreator::createPlayerParty();
            enemyParty = PartyCreator::createBossEnemyParty();
            break;
        case 4:
            playerParty = createCustomPlayerParty();
            enemyParty = createCustomEnemyParty();
            break;
        case 5:
            displayGlobalCharacterInfo();
            std::cout << "\n按回车键继续...";
            std::cin.ignore();
            std::cin.get();
            continue;
        default:
            std::cout << "无效选择!\n";
            continue;
        }

        // 开始战斗
        BattleSystem battle(playerParty, enemyParty);
        battle.startBattle();

        // 检查战斗是否被终止
        if (battle.getCurrentState() == BattleState::FLEE) {
            std::cout << "战斗已终止，返回主菜单...\n";
            continue;
        }

        std::cout << "\n战斗结束! 按回车键继续...";
        std::cin.ignore();
        std::cin.get();
    }

    std::cout << "感谢游玩战斗模拟器!\n";
    return 0;
}