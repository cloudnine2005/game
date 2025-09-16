#pragma once

#include <string>
#include <vector>

class Player {
private:
    std::string name;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int level;
    int experience;
    int currentRoom ;    // 当前房间 id 编号

public:
    Player(const std::string& playerName);
    ~Player();

    // 获取属性值
    std::string getName() const { return name; }
    int getCurrentRoom() const { return currentRoom; }

    // 设置属性值
    void setHealth(int h) { health = h; }
    void setMaxHealth(int mh) { maxHealth = mh; }
    void setAttack(int a) { attack = a; }
    void setDefense(int d) { defense = d; }
    void setLevel(int l) { level = l; }
    void setExperience(int e) { experience = e; }
    void setCurrentRoom(int roomId) { currentRoom = roomId; }

    // 游戏功能

    void displayStats() const;
};