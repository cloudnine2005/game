#pragma once
#include <string>
#include <vector>
#include <map>


enum class RoomType {
	NORMAL,     // 普通房间
	BATTLE,     // 战斗房间
	TREASURE,   // 宝藏房间
	REST,       // 休息房间
	BOSS        // BOSS房间
};
class Room {
private:

	//基础信息设定
	int _id;
	std::string _name;
	std::string _desc;
	RoomType _type; 
	bool _completed;    

public:
	//连接房间设定
	std::map < std::string, int> exits;//进入方向所对应的房间id
	//初始化房间信息
	Room(int roomId, const std::string& roomName, const std::string& roomDesc, RoomType type = RoomType::NORMAL);
	~Room();

	//访问房间信息
	int getRoomId() const;
	std::string getRoomName() const;
	std::string getRoomDesc() const;
	RoomType getRoomType() const;
	bool isCompleted() const;

	//设置房间状态
	void setCompleted(bool completed);

	//新建出口——通过获取房间id和方向
	void addExits(int roomId, const std::string &roomDesc);

	//从房间里出去的行为——通过方向是否匹配返回房间id
	int getExits(const std::string& direction);

	//展示房间信息
	void displayRoom() const;

	// 房间特殊功能
	std::string getRoomStatus() const;

	// 获取房间类型的中文描述
	std::string getRoomTypeString() const;
};

