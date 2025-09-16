#include "room.h"
#include "player.h"
#include <string>
#include <vector>
#include <iostream>
static std::vector <Room*> rooms;

//初始化房间id、房间名字、事件描述
Room::Room(int roomId, const std::string& roomName, const std::string& roomDesc, RoomType type)
	: _id(roomId), _name(roomName), _desc(roomDesc), _type(type), _completed(false) {
}
Room :: ~Room(){
}

//访问房间内容
int Room::getRoomId() const {
	return _id;
}

std::string Room::getRoomName() const {
	return _name;
}

std::string Room::getRoomDesc() const {
	return _desc;
}

RoomType Room::getRoomType() const {
	return _type;
}

bool Room::isCompleted() const {
	return _completed;
}

//设置房间状态

void Room::setCompleted(bool completed) {
	_completed = completed;
}

//等待房间创建——输入房间id与房间位置
void Room::addExits(int roomId, const std::string& direction) {
	exits [direction] = roomId;
}

//获得房间方向，成功获得则返回房间id
int Room::getExits(const std::string& direction) {
	auto it = exits.find(direction);
	if (it != exits.end()) {
		return it->second;
	}
	else return -1;
}

void Room::displayRoom() const {
    std::cout << "======" << _name << "======" << std::endl;

    // 显示房间类型和状态
    std::cout << "类型: " << getRoomTypeString() << std::endl;
    std::cout << "状态: " << getRoomStatus() << std::endl;

    std::cout << "描述: " << _desc << std::endl;

    // 显示可用的出口
    if (!exits.empty()) {
        std::cout << "可用出口: ";
        for (auto& exit : exits) {
            std::cout << exit.first << " ";
        }
        std::cout << std::endl;
    }

    // 显示可用的命令
    std::cout << "可用命令: look, move, interact";
    std::cout << std::endl;
}

// 获取房间类型的中文描述
std::string Room::getRoomTypeString() const {
    switch (_type) {
    case RoomType::NORMAL:
        return "普通房间";
    case RoomType::BATTLE:
        return "战斗房间";
    case RoomType::TREASURE:
        return "宝藏房间";
    case RoomType::REST:
        return "休息房间";
    case RoomType::BOSS:
        return "BOSS房间";
    default:
        return "未知房间";
    }
}

// 获取房间状态描述
std::string Room::getRoomStatus() const {

    switch (_type) {
    case RoomType::NORMAL:
        return "平平无奇的房间，没什么新奇的东西";
    case RoomType::BATTLE:
        return _completed ? "怪物已击败" : "有怪物游荡，你不能睡觉";
    case RoomType::TREASURE:
        return _completed ? "宝箱已打开" : "闪亮亮的宝箱";
    case RoomType::REST:
        return "软塌塌的床，可以一觉睡到天亮";
    case RoomType::BOSS:
        return _completed ? "BOSS已击败" : "当心boss出没";
    default:
        return "无";
    }
}