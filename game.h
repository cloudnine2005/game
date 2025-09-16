#pragma once

#include <string>
#include <vector>



struct SaveData {
    std::string playerName;
    int currentRoom;
    std::vector<bool> roomCompleted; // 记录每个房间是否已完成
};

class Player;
class Room;

class Game {
private:
    Player* player;     //玩家信息
    std::vector<Room*> rooms;   //房间列表
    bool isRunning;     //游戏运行状态
    const std::string gamedata = "save.dat";    //游戏数据存储文件

    //初始化房间
    void initializeRooms();    

    //处理命令
	void processCommand(const std::string& command);  

    //显示帮助信息
    void displayHelp() const;    

    //移动玩家
    void movePlayer(const std::string& direction);   

    //显示当前房间信息
    void displayCurrentRoom() const;


    // 房间特殊功能
    void handleRoomEvent();     //处理房间事件
    void startBattle();         //开始战斗
    void openTreasure();        //打开宝箱
    void restAtRoom();          //休息
    void fightBoss();           //打boss
    // 存档相关函数
    void saveGame() const;          // 保存游戏状态
    bool loadGame();                // 加载游戏状态
    std::string getSaveFilePath() const; // 获取存档文件路径
    bool isFileEmpty(const std::string& filename);
public:

    Game();
    ~Game();
    //判断游戏状态
    void start();
    void run();
    void stop() {
        isRunning = false; 
    }
    void displayMap();
};

