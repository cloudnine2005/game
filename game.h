#pragma once

#include <string>
#include <vector>



struct SaveData {
    std::string playerName;
    int currentRoom;
    std::vector<bool> roomCompleted; // ��¼ÿ�������Ƿ������
};

class Player;
class Room;

class Game {
private:
    Player* player;     //�����Ϣ
    std::vector<Room*> rooms;   //�����б�
    bool isRunning;     //��Ϸ����״̬
    const std::string gamedata = "save.dat";    //��Ϸ���ݴ洢�ļ�

    //��ʼ������
    void initializeRooms();    

    //��������
	void processCommand(const std::string& command);  

    //��ʾ������Ϣ
    void displayHelp() const;    

    //�ƶ����
    void movePlayer(const std::string& direction);   

    //��ʾ��ǰ������Ϣ
    void displayCurrentRoom() const;


    // �������⹦��
    void handleRoomEvent();     //�������¼�
    void startBattle();         //��ʼս��
    void openTreasure();        //�򿪱���
    void restAtRoom();          //��Ϣ
    void fightBoss();           //��boss
    // �浵��غ���
    void saveGame() const;          // ������Ϸ״̬
    bool loadGame();                // ������Ϸ״̬
    std::string getSaveFilePath() const; // ��ȡ�浵�ļ�·��
    bool isFileEmpty(const std::string& filename);
public:

    Game();
    ~Game();
    //�ж���Ϸ״̬
    void start();
    void run();
    void stop() {
        isRunning = false; 
    }
    void displayMap();
};

