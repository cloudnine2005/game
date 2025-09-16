#include "Player.h"
#include <iostream>

Player::Player(const std::string& playerName)   //����������Ȳ���һ��
    : name(playerName), health(100), maxHealth(100), attack(10), defense(5),
    level(1), experience(0), currentRoom(0) {
}

Player::~Player() {

}

void Player::displayStats()const {
    std::cout << "״̬����" << std::endl;
}