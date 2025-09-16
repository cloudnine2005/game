#include "fight.h"
#include "data.h"
#include <iostream>
#include <limits> // �������������֤

//// ������֤��������
//int getValidatedInput(int min, int max) {
//    int input;
//    while (true) {
//        std::cin >> input;
//        if (std::cin.fail()) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            std::cout << "������Ч������������ (" << min << "-" << max << "): ";
//        }
//        else if (input < min || input > max) {
//            std::cout << "���볬����Χ������������ (" << min << "-" << max << "): ";
//        }
//        else {
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            return input;
//        }
//    }
//}

void displayMainMenu() {
    std::cout << "=== ս��ģ���� ===\n";
    std::cout << "1. ��ս�� (���׽��� + ��������)\n";
    std::cout << "2. �е�ս�� (�Զ����� + ������֮�� + ��������)\n";
    std::cout << "3. BOSSս (ĩ���� + �Զ�����)\n";
    std::cout << "4. �Զ������\n";
    std::cout << "5. �鿴��ɫͼ��\n";
    std::cout << "0. �˳�\n";
    std::cout << "��ѡ��: ";
}

void displayCharacterSelection() {
    std::cout << "\n=== ѡ������ɫ ===\n";
    std::cout << "1. �����ߡ�����\n";
    std::cout << "2. ������\n";
    std::cout << "3. ����\n";
    std::cout << "��ѡ���ɫ (������ţ�0����ѡ��): ";
}

void displayEnemySelection() {
    std::cout << "\n=== ѡ����� ===\n";
    std::cout << "1. ���׽���\n";
    std::cout << "2. ��������\n";
    std::cout << "3. ������֮��\n";
    std::cout << "4. �Զ���������\n";
    std::cout << "5. ĩ����\n";
    std::cout << "��ѡ����� (������ţ�0����ѡ��): ";
}

void displayGlobalCharacterInfo() {
    std::cout << "\n=== ��ɫͼ�� ===\n";

    std::cout << "\n=== ����ɫ ===\n";
    std::cout << "1. �����ߡ����� - HP:150 ����:25 ����:12 �ٶ�:240\n";
    std::cout << "2. ������ - HP:120 ����:18 ����:15 �ٶ�:220\n";
    std::cout << "3. ���� - HP:130 ����:28 ����:10 �ٶ�:260\n";

    std::cout << "\n=== ���˽�ɫ ===\n";
    std::cout << "1. ���׽��� - HP:1000 ����:15 ����:8 �ٶ�:120\n";
    std::cout << "2. �������� - HP:800 ����:20 ����:6 �ٶ�:180\n";
    std::cout << "3. ������֮�� - HP:1500 ����:18 ����:12 �ٶ�:100\n";
    std::cout << "4. �Զ��������� - HP:1200 ����:22 ����:10 �ٶ�:200\n";
    std::cout << "5. ĩ���� - HP:3000 ����:30 ����:20 �ٶ�:80\n";
}

std::vector<BattleCharacter> createCustomPlayerParty() {
    std::vector<BattleCharacter> party;
    int choice;

    std::cout << "\n�����Զ��������� (���3��):\n";

    for (int i = 0; i < 3; i++) {
        displayCharacterSelection();
        choice = getValidatedInput(0, 3);

        if (choice == 0) break;

        BattleCharacter newCharacter;
        switch (choice) {
        case 1:
            newCharacter = PlayerCharacters::createTrailblazerPhysical();
            std::cout << "��ѡ��: �����ߡ�����\n";
            break;
        case 2:
            newCharacter = PlayerCharacters::createMarch7th();
            std::cout << "��ѡ��: ������\n";
            break;
        case 3:
            newCharacter = PlayerCharacters::createDanHeng();
            std::cout << "��ѡ��: ����\n";
            break;
        default:
            std::cout << "��Чѡ��!\n";
            i--;
            continue;
        }
        PlayerCharacters::displayCharacterInfo(newCharacter);
        party.push_back(newCharacter);
    }

    if (party.empty()) {
        std::cout << "����Ϊ�գ�ʹ��Ĭ�϶���\n";
        party = PartyCreator::createPlayerParty();
    }

    return party;
}

std::vector<BattleCharacter> createCustomEnemyParty() {
    std::vector<BattleCharacter> party;
    int choice;

    std::cout << "\n�����Զ�����˶���:\n";

    while (true) {
        displayEnemySelection();
        choice = getValidatedInput(0, 5);

        if (choice == 0) break;

        switch (choice) {
        case 1:
            party.push_back(EnemyCharacters::createSilvermaneGuard());
            std::cout << "��ѡ��: ���׽���\n";
            break;
        case 2:
            party.push_back(EnemyCharacters::createSilvermaneSniper());
            std::cout << "��ѡ��: ��������\n";
            break;
        case 3:
            party.push_back(EnemyCharacters::createOutspaceIce());
            std::cout << "��ѡ��: ������֮��\n";
            break;
        case 4:
            party.push_back(EnemyCharacters::createAutomatonWolf());
            std::cout << "��ѡ��: �Զ���������\n";
            break;
        case 5:
            party.push_back(EnemyCharacters::createDoomsdayBeast());
            std::cout << "��ѡ��: ĩ����\n";
            break;
        default:
            std::cout << "��Чѡ��!\n";
            break;
        }
    }

    if (party.empty()) {
        std::cout << "���˶���Ϊ�գ�ʹ��Ĭ�ϵ���\n";
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
            std::cout << "\n���س�������...";
            std::cin.ignore();
            std::cin.get();
            continue;
        default:
            std::cout << "��Чѡ��!\n";
            continue;
        }

        // ��ʼս��
        BattleSystem battle(playerParty, enemyParty);
        battle.startBattle();

        // ���ս���Ƿ���ֹ
        if (battle.getCurrentState() == BattleState::FLEE) {
            std::cout << "ս������ֹ���������˵�...\n";
            continue;
        }

        std::cout << "\nս������! ���س�������...";
        std::cin.ignore();
        std::cin.get();
    }

    std::cout << "��л����ս��ģ����!\n";
    return 0;
}