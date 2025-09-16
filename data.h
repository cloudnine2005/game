#ifndef DATA_H
#define DATA_H

#include "fight.h"
#include <vector>
#include <memory>

// ��ҽ�ɫ����
namespace PlayerCharacters {
    // �����ߣ�����
    inline BattleCharacter createTrailblazerPhysical() {
        CharacterStats stats(270, 25, 12, 240, 0.5f, 1.5f, 0.1f, 0.2f);
        BattleCharacter character("�����ߡ�����", stats, true);

        auto basicAttack = std::make_shared<BasicAttack>("��ͨ����", DamageType::PHYSICAL, 1.0f);
        auto battleSkill = std::make_shared<BattleSkill>("ս�����ѿ�ն", "��������˺����м���ʹ���˷�������",
            DamageType::PHYSICAL, 1.8f, 0.7f,
            BattleEffect("��������", 2, true, 0, -8));
        auto ultimate = std::make_shared<UltimateSkill>("�սἼ���������", "��ɴ��������˺����ض�ʹ���˷����������",
            DamageType::PHYSICAL, 3.0f,
            BattleEffect("�����������", 3, true, 0, -15));

        character.addSkill(basicAttack);
        character.addSkill(battleSkill);
        character.addSkill(ultimate);

        return character;
    }

    // ������
    inline BattleCharacter createMarch7th() {
        CharacterStats stats(120, 18, 15, 220, 0.08f, 0.4f, 0.2f, 0.3f);
        BattleCharacter character("������", stats, true);

        auto basicAttack = std::make_shared<BasicAttack>("��ͨ����", DamageType::ICE, 0.9f);
        auto battleSkill = std::make_shared<BattleSkill>("ս��������", "��ɱ������˺����м��ʶ������",
            DamageType::ICE, 1.2f, 0.6f,
            BattleEffect("����", 1, true, 0, 0, -20, 1.2f));
        auto ultimate = std::make_shared<UltimateSkill>("�սἼ����������", "��ɱ������˺����ض��������",
            DamageType::ICE, 2.2f,
            BattleEffect("��ȶ���", 2, true, 0, 0, -30, 1.3f));

        character.addSkill(basicAttack);
        character.addSkill(battleSkill);
        character.addSkill(ultimate);

        return character;
    }

    // ����
    inline BattleCharacter createDanHeng() {
        CharacterStats stats(130, 28, 10, 260, 0.75f, 2.6f, 0.1f, 0.1f);
        BattleCharacter character("����", stats, true);

        auto basicAttack = std::make_shared<BasicAttack>("��ͨ����", DamageType::WIND, 1.1f);
        auto battleSkill = std::make_shared<BattleSkill>("ս��������ͻ��", "��ɷ������˺����м���ʹ�����ٶȽ���",
            DamageType::WIND, 1.6f, 0.8f,
            BattleEffect("�ٶȽ���", 2, true, 0, 0, -15));
        auto ultimate = std::make_shared<UltimateSkill>("�սἼ������籩", "��ɴ����������˺����ض�ʹ�����ٶȴ������",
            DamageType::WIND, 2.8f,
            BattleEffect("�ٶȴ������", 3, true, 0, 0, -25));

        character.addSkill(basicAttack);
        character.addSkill(battleSkill);
        character.addSkill(ultimate);

        return character;
    }

    inline void displayCharacterInfo(const BattleCharacter& character) {
        std::cout << "\n=== ��ɫ��Ϣ ===\n";
        std::cout << "����: " << character.getName() << "\n";
        std::cout << "����ֵ: " << character.getCurrentHP() << "/" << character.getMaxHP() << "\n";
        std::cout << "������: " << character.getCurrentAttack() << "\n";
        std::cout << "������: " << character.getCurrentDefense() << "\n";
        std::cout << "�ٶ�: " << character.getCurrentSpeed() << "\n";
    }
}

// ��������
namespace EnemyCharacters {
    // ���׽���
    inline BattleCharacter createSilvermaneGuard() {
        CharacterStats stats(250, 15, 8, 120, 0.05f, 0.5f, 0.0f, 0.1f);
        BattleCharacter enemy("���׽���", stats);

        auto basicAttack = std::make_shared<BasicAttack>("����", DamageType::PHYSICAL, 1.0f);
        auto battleSkill = std::make_shared<BattleSkill>("�ػ�", "��������˺�",
            DamageType::PHYSICAL, 1.3f);

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);

        return enemy;
    }

    // ��������
    inline BattleCharacter createSilvermaneSniper() {
        CharacterStats stats(200, 20, 6, 180, 0.1f, 0.6f, 0.1f, 0.0f);
        BattleCharacter enemy("��������", stats);

        auto basicAttack = std::make_shared<BasicAttack>("���", DamageType::PHYSICAL, 1.1f);
        auto battleSkill = std::make_shared<BattleSkill>("��׼���", "��������˺�",
            DamageType::PHYSICAL, 1.5f);
        auto ultimate = std::make_shared<UltimateSkill>("����", "����������",
            DamageType::PHYSICAL, 2.0f);

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }

    // ������֮��
    inline BattleCharacter createOutspaceIce() {
        CharacterStats stats(750, 18, 12, 100, 0.03f, 0.4f, 0.2f, 0.3f);
        BattleCharacter enemy("������֮��", stats);

        auto basicAttack = std::make_shared<BasicAttack>("��׶", DamageType::ICE, 1.0f);
        auto battleSkill = std::make_shared<BattleSkill>("������Ϣ", "��ɱ������˺����м��ʶ���Ŀ��",
            DamageType::ICE, 1.4f, 0.3f,
            BattleEffect("����", 1, true, 0, 0, -10, 1.1f));
        auto ultimate = std::make_shared<UltimateSkill>("�������", "��ɱ������˺������͵����ٶ�",
            DamageType::ICE, 2.2f,
            BattleEffect("�ٶȽ���", 2, true, 0, 0, -20));

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }

    // �Զ�����������
    inline BattleCharacter createAutomatonWolf() {
        CharacterStats stats(600, 22, 10, 200, 0.08f, 0.5f, 0.0f, 0.2f);
        BattleCharacter enemy("�Զ�����������", stats);

        auto basicAttack = std::make_shared<BasicAttack>("˺ҧ", DamageType::PHYSICAL, 1.2f);
        auto battleSkill = std::make_shared<BattleSkill>("��צ����", "���ٹ������",
            DamageType::PHYSICAL, 1.8f);
        auto ultimate = std::make_shared<UltimateSkill>("��ģʽ", "�����״̬���������������",
            DamageType::PHYSICAL, 1.0f,
            BattleEffect("��", 3, false, 10, 0, 0, 0.9f));

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }

    // ĩ����
    inline BattleCharacter createDoomsdayBeast() {
        CharacterStats stats(3000, 30, 20, 80, 0.15f, 0.7f, 0.3f, 0.4f);
        BattleCharacter enemy("ĩ����", stats);

        auto basicAttack = std::make_shared<BasicAttack>("�����ػ�", DamageType::PHYSICAL, 1.5f);
        auto battleSkill = std::make_shared<BattleSkill>("��������", "��������˺�",
            DamageType::QUANTUM, 2.0f);
        auto ultimate = std::make_shared<UltimateSkill>("ĩ������", "��ɾ޴��˺������͵��˷���",
            DamageType::QUANTUM, 3.5f,
            BattleEffect("��������", 3, true, 0, -12));

        enemy.addSkill(basicAttack);
        enemy.addSkill(battleSkill);
        enemy.addSkill(ultimate);

        return enemy;
    }
}

// ���鴴������
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