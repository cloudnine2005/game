#include "room.h"
#include "player.h"
#include <string>
#include <vector>
#include <iostream>
static std::vector <Room*> rooms;

//��ʼ������id���������֡��¼�����
Room::Room(int roomId, const std::string& roomName, const std::string& roomDesc, RoomType type)
	: _id(roomId), _name(roomName), _desc(roomDesc), _type(type), _completed(false) {
}
Room :: ~Room(){
}

//���ʷ�������
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

//���÷���״̬

void Room::setCompleted(bool completed) {
	_completed = completed;
}

//�ȴ����䴴���������뷿��id�뷿��λ��
void Room::addExits(int roomId, const std::string& direction) {
	exits [direction] = roomId;
}

//��÷��䷽�򣬳ɹ�����򷵻ط���id
int Room::getExits(const std::string& direction) {
	auto it = exits.find(direction);
	if (it != exits.end()) {
		return it->second;
	}
	else return -1;
}

void Room::displayRoom() const {
    std::cout << "======" << _name << "======" << std::endl;

    // ��ʾ�������ͺ�״̬
    std::cout << "����: " << getRoomTypeString() << std::endl;
    std::cout << "״̬: " << getRoomStatus() << std::endl;

    std::cout << "����: " << _desc << std::endl;

    // ��ʾ���õĳ���
    if (!exits.empty()) {
        std::cout << "���ó���: ";
        for (auto& exit : exits) {
            std::cout << exit.first << " ";
        }
        std::cout << std::endl;
    }

    // ��ʾ���õ�����
    std::cout << "��������: look, move, interact";
    std::cout << std::endl;
}

// ��ȡ�������͵���������
std::string Room::getRoomTypeString() const {
    switch (_type) {
    case RoomType::NORMAL:
        return "��ͨ����";
    case RoomType::BATTLE:
        return "ս������";
    case RoomType::TREASURE:
        return "���ط���";
    case RoomType::REST:
        return "��Ϣ����";
    case RoomType::BOSS:
        return "BOSS����";
    default:
        return "δ֪����";
    }
}

// ��ȡ����״̬����
std::string Room::getRoomStatus() const {

    switch (_type) {
    case RoomType::NORMAL:
        return "ƽƽ����ķ��䣬ûʲô����Ķ���";
    case RoomType::BATTLE:
        return _completed ? "�����ѻ���" : "�й����ε����㲻��˯��";
    case RoomType::TREASURE:
        return _completed ? "�����Ѵ�" : "�������ı���";
    case RoomType::REST:
        return "�������Ĵ�������һ��˯������";
    case RoomType::BOSS:
        return _completed ? "BOSS�ѻ���" : "����boss��û";
    default:
        return "��";
    }
}