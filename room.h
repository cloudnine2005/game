#pragma once
#include <string>
#include <vector>
#include <map>


enum class RoomType {
	NORMAL,     // ��ͨ����
	BATTLE,     // ս������
	TREASURE,   // ���ط���
	REST,       // ��Ϣ����
	BOSS        // BOSS����
};
class Room {
private:

	//������Ϣ�趨
	int _id;
	std::string _name;
	std::string _desc;
	RoomType _type; 
	bool _completed;    

public:
	//���ӷ����趨
	std::map < std::string, int> exits;//���뷽������Ӧ�ķ���id
	//��ʼ��������Ϣ
	Room(int roomId, const std::string& roomName, const std::string& roomDesc, RoomType type = RoomType::NORMAL);
	~Room();

	//���ʷ�����Ϣ
	int getRoomId() const;
	std::string getRoomName() const;
	std::string getRoomDesc() const;
	RoomType getRoomType() const;
	bool isCompleted() const;

	//���÷���״̬
	void setCompleted(bool completed);

	//�½����ڡ���ͨ����ȡ����id�ͷ���
	void addExits(int roomId, const std::string &roomDesc);

	//�ӷ������ȥ����Ϊ����ͨ�������Ƿ�ƥ�䷵�ط���id
	int getExits(const std::string& direction);

	//չʾ������Ϣ
	void displayRoom() const;

	// �������⹦��
	std::string getRoomStatus() const;

	// ��ȡ�������͵���������
	std::string getRoomTypeString() const;
};

