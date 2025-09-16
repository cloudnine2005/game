#include "Game.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "data.h"
#include "fight.h"
#include "fighting.h"

bool moveCommand = false;

Game::Game() : player(nullptr), isRunning(false) {}

Game::~Game() {
    delete player;
    for (Room* room : rooms) {
        delete room;
    }
}

bool Game::isFileEmpty(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary); // 直接定位到文件末尾
    if (!file.is_open()) return true; // 文件不存在视为空
    bool isEmpty = (file.tellg() == 0);
    file.close(); // 显式关闭文件
    return isEmpty;
}

void Game::start() {
    std::string playerName;
    auto choice = 0;
    if (!isFileEmpty(gamedata)) {
        std::cout << "检测到上一次游戏时的存档记录，是否加载存档 ?" << std::endl
            << "输入‘1’加载，输入‘0’重新开始（游戏过程中尽量不要加载哦，否则临时数据将丢失~）" << std::endl;
        for (std::cin >> choice; !(choice == 1 || choice == 0); std::cin >> choice) {
            std::cout << "无效的输入！请重新输入（0或1）： " << std::endl;
        }
    }
    
    initializeRooms();
    
    if (choice == 1) {
        if (loadGame()) {
        std::cout << "o(￣▽￣)ｄ\n 欢迎" << playerName << "回来！请继续你的冒险之旅！！！" << std::endl;
    }
    }
    else {
            std::cout << "输入角色名： ";
            std::getline(std::cin, playerName);
            player = new Player(playerName);
            //1.欢迎信息
            std::cout << "\n@@ 故事背景：" << std::endl;
            std::cout << "   你从沉睡中醒来，发现自己是一支古老守护者血脉的最后传人。" << std::endl;
            std::cout << "   黑暗力量再次苏醒，蔓延的紫雾腐蚀着大地，怪物四处横行。" << std::endl;
            std::cout << "   根据家族传承的日记，只有集齐三件失落的圣物，才能封印黑暗之门。" << std::endl;
            std::cout << "   光明之石、勇气徽章、智慧宝珠散落在世界各地，等待真正的守护者找回。" << std::endl;
            std::cout << "   你的旅程即将开始，世界的命运掌握在你的手中...\n" << std::endl;

            std::cout << "你环顾四周，发现这是你的家，也是最后一任守护者的居所。" << std::endl;
            std::cout << "壁炉上方挂着一幅古老的地图，标记着三个神秘的地点。" << std::endl;
            std::cout << "书桌上有一本泛黄的日记，最后一页写着:" << std::endl;
            std::cout << "\"黑暗再次苏醒，三圣物散落各地。若见此文，吾已不在。继承吾志，找回圣物，封印黑暗...\"\n" << std::endl;
            std::cout << "窗外，不祥的紫雾正在缓缓蔓延，你知道必须立即行动。\n" << std::endl;

            std::cout << "** 游戏目标：" << std::endl;
            std::cout << "   1. 探索各个区域，寻找三件圣物的线索" << std::endl;
            std::cout << "   2. 击败守护圣物的强大怪物" << std::endl;
            std::cout << "   3. 集齐光明之石、勇气徽章和智慧宝珠" << std::endl;
            std::cout << "   4. 前往黑暗之门，与黑暗领主进行最终决战\n" << std::endl;

            player->setCurrentRoom(1); // 初始房间设定在家里

    }
    
    std::cout << "(特别提醒：结束游戏前记得输入“save”保存游戏)\n" << std::endl;

    // 1. 玩家初始状态
    std::cout << "## 玩家状态：" << std::endl;
    std::cout << "   姓名：" << player->getName() << std::endl;  // 调用Player类的getName方法

    // 2. 操作说明
    std::cout << "$$ 基础操作指令：" << std::endl;
    std::cout << "   - 移动：先输入'move'再选择方向（如：north、south、east、west等）" << std::endl;
    std::cout << "   - 查看房间：输入 'look' " << std::endl;
    std::cout << "   - 完成房间任务：输入 'interact' 进行战斗、训练、获取宝藏等等" << std::endl;
    std::cout << "   - 查看地图：输入 'map' " << std::endl;
    std::cout << "   - 帮助：输入 'help' 查看完整操作指令列表" << std::endl;
    std::cout << "   - 退出：输入 'quit' 退出游戏\n" << std::endl;
            
    // 3. 开始提示
    std::cout << "=========================================================  " << std::endl;
    std::cout << "请按回车键开始你的冒险...";

    run();
}

void Game::initializeRooms() {
    rooms.push_back(new Room(0, "远古训练场",
        "这里曾是古代守护者的训练场所。墙上刻满了古老的战斗符文，中央有一尊破损的战士雕像。\n"
        "雕像手中似乎曾经握着什么重要的东西，但现在只剩下空荡荡的底座。\n"
        "空气中弥漫着淡淡的魔法气息，仿佛时间在这里停滞了。", RoomType::NORMAL));

    rooms.push_back(new Room(1, "守护者小屋",
        "这是你的家，也是最后一任守护者的居所。壁炉上方挂着一幅古老的地图，标记着三个神秘的地点。\n"
        "书桌上有一本泛黄的日记，最后一页写着:\n"
        "\"黑暗再次苏醒，三圣物散落各地。若见此文，吾已不在。继承吾志，找回圣物，封印黑暗...\"\n"
        "窗外，不祥的紫雾正在缓缓蔓延。", RoomType::REST));

    rooms.push_back(new Room(2, "哭泣洞穴",
        "洞穴中回荡着诡异的哭泣声，墙壁上布满了发光的苔藓。\n"
        "这里盘踞着被黑暗侵蚀的地精，它们曾是矿工，如今只剩疯狂。\n"
        "洞穴深处隐约传来微弱的蓝光，似乎是第一件圣物—光明之石的所在。", RoomType::BATTLE));

    rooms.push_back(new Room(3, "遗忘图书馆",
        "这座古老的图书馆几乎被时间遗忘。书架倒塌，典籍散落一地。\n"
        "一位白发苍苍的学者正在艰难地整理残卷。他看到你，眼中闪过一丝希望:\n"
        "\"守护者血脉！你终于来了。我知道圣物的下落，但我需要你的帮助...\"", RoomType::NORMAL));

    rooms.push_back(new Room(4, "幽暗森林",
        "这片森林被不自然的黑暗笼罩，树木扭曲变形，仿佛在痛苦中呻吟。\n"
        "森林深处，一个被黑暗腐蚀的树精守护着第二件圣物—勇气徽章。\n"
        "空气中弥漫着腐败的气息，每一步都需格外小心。", RoomType::BATTLE));

    rooms.push_back(new Room(5, "神秘宝箱",
        "一个华丽的宝箱静静地放置在石台上，表面刻满了古老的符文。\n"
        "宝箱上有一行小字:\n"
        "\"真正的财富不是黄金，而是知识。学会古老的战斗技艺，比任何武器都更珍贵。\"\n"
        "打开它，你可能获得强大的力量，但也可能触发致命的陷阱。", RoomType::TREASURE));

    rooms.push_back(new Room(6, "流浪者营地",
        "一群被黑暗力量驱逐的流浪者在此暂歇。他们的领袖是一位独眼战士。\n"
        "\"守护者？我们已经很久没听到这个称呼了。\"他擦拭着剑刃说道。\n"
        "\"黑暗领主的手下正在寻找最后一件圣物—智慧宝珠。你必须赶在他们前面！\"", RoomType::NORMAL));

    rooms.push_back(new Room(7, "冰封王座",
        "极寒之地，一座冰雕王座矗立在洞穴中央。王座上坐着被冰封的古代国王。\n"
        "他的手中握着最后一件圣物—智慧宝珠，但黑暗力量已经腐蚀了这片区域。\n"
        "冰霜守卫苏醒过来，它们决不允许任何人触碰圣物。", RoomType::BATTLE));

    rooms.push_back(new Room(8, "黑暗之门",
        "巨大的黑暗能量从地底涌出，形成一道扭曲的传送门。\n"
        "黑暗领主的身影在门后若隐若现，试图跨越到这个世界。\n"
        "三件圣物在你手中发出共鸣，这是最后的决战时刻。", RoomType::BOSS));

    rooms[0]->addExits(1, "west");
    rooms[1]->addExits(0, "east");
    rooms[1]->addExits(2, "south");
    rooms[2]->addExits(1, "north");
    rooms[2]->addExits(3, "west");
    rooms[3]->addExits(2, "east");
    rooms[3]->addExits(4, "west");
    rooms[4]->addExits(3, "east");
    rooms[4]->addExits(5, "west");
    rooms[5]->addExits(4, "east");
    rooms[4]->addExits(6, "north");
    rooms[6]->addExits(4, "south");
    rooms[6]->addExits(7, "north");
    rooms[7]->addExits(6, "south");
    rooms[7]->addExits(8, "north");
    rooms[8]->addExits(7, "south");
}

void Game::run() {
    isRunning = true;
    displayCurrentRoom();

    while (isRunning) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        if (!input.empty()) {
            processCommand(input);
        }
    }
}

enum class Command {
    HELP,
    LOOK,
    STATS,
    MAP,
    MOVE,
    NORTH,
    SOUTH,
    EAST,
    WEST,
    QUIT,
    INTERACT,
    SAVE,
    LOAD,
    UNKNOWN
};

Command getCommandType(const std::string& cmd) {
    static const std::map<std::string, Command> commandMap = {
        {"help", Command::HELP},
        {"look", Command::LOOK},
        {"move", Command::MOVE},
        {"quit", Command::QUIT},
        {"north", Command::NORTH},
        {"south", Command::SOUTH},
        {"east", Command::EAST},
        {"west", Command::WEST},
        {"interact", Command::INTERACT},
        {"save", Command::SAVE},
        {"load", Command::LOAD},
        {"map", Command::MAP}
    };
    auto it = commandMap.find(cmd);
    return it != commandMap.end() ? it->second : Command::UNKNOWN;
}

void Game::processCommand(const std::string& command) {
    std::stringstream ss(command);
    std::string cmd;
    ss >> cmd;

    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower); //输入内容转换成小写

    std::string extra;
    if (ss >> extra) {
        std::cout << "哈？你在说什么意义不明的话呢？ " << std::endl;
        std::cout << "不过...如果你求求我的话，作为奖励给你点提示也不是不行哦~" << std::endl;
        std::cout << "旁白：是否向机娘寻求help？" << std::endl;
        return;
    }

    switch (getCommandType(cmd)) {
    case Command::HELP:
        displayHelp();
        break;
    case Command::LOOK:
        std::cout << rooms[player->getCurrentRoom()]->getRoomDesc() << std::endl;
        break;
    case Command::INTERACT:
        handleRoomEvent();
        break;
    case Command::MOVE: {
        std::cout << "可选方向" << std::endl;
        Room* currentRoom = rooms[player->getCurrentRoom()];
        for (auto& exit : currentRoom->exits) {
            std::cout << exit.first << "\t";
        }
        std::cout << std::endl;
        std::string direction;
        ss >> direction;
        if (!direction.empty()) {
            movePlayer(direction);
        }
        else {
            std::cout << "请指定移动方向" << std::endl;
            moveCommand = true;
        }
        break;
    }
    case Command::QUIT: {
        std::cout << "真的要退出吗QAQ？(y/n): ";
        std::string confirm;
        std::getline(std::cin, confirm);
        if (confirm == "y") {
            stop();
        }
        else {
            std::cout << "好的游戏继续" << std::endl;
        }
        break;
    }
    case Command::NORTH:
        if (moveCommand) {
            movePlayer("north");
            moveCommand = false;
        }
        else {
            std::cout << "哈？" << cmd << "? " << "你在说什么意义不明的话呢？" << std::endl;
            std::cout << "不过...如果你求求我的话，作为奖励给你点提示也不是不行哦~" << std::endl;
            std::cout << "旁白：是否向机娘寻求help？" << std::endl;
        }
        break;
    case Command::SOUTH:
        if (moveCommand) {
            movePlayer("south");
            moveCommand = false;
        }
        else {
            std::cout << "哈？" << cmd << "? " << "你在说什么意义不明的话呢？" << std::endl;
            std::cout << "不过...如果你求求我的话，作为奖励给你点提示也不是不行哦~" << std::endl;
            std::cout << "旁白：是否向机娘寻求help？" << std::endl;
        }
        break;
    case Command::EAST: {
        if (moveCommand) {
            movePlayer("east");
            moveCommand = false;
        }
        else {
            std::cout << "哈？" << cmd << "? " << "你在说什么意义不明的话呢？" << std::endl;
            std::cout << "不过...如果你求求我的话，作为奖励给你点提示也不是不行哦~" << std::endl;
            std::cout << "旁白：是否向机娘寻求help？" << std::endl;
        }
        break;
    }
    case Command::WEST: {
        if (moveCommand) {
            movePlayer("west");
            moveCommand = false;
        }
        else {
            std::cout << "哈？" << cmd << "? " << "你在说什么意义不明的话呢？" << std::endl;
            std::cout << "不过...如果你求求我的话，作为奖励给你点提示也不是不行哦~" << std::endl;
            std::cout << "旁白：是否向机娘寻求help？" << std::endl;
        }
        break;
    }
    case Command::SAVE:
        saveGame();
        break;
    case Command::LOAD:
        loadGame();
        break;
    case Command::MAP:
        displayMap();
        break;
    case Command::UNKNOWN:
    default:
        std::cout << "哈？" << cmd << "? " << "你在说什么意义不明的话呢？" << std::endl;
        std::cout << "不过...如果你求求我的话，作为奖励给你点提示也不是不行哦~" << std::endl;
        std::cout << "旁白：是否向机娘寻求help？" << std::endl;
    }
}

void Game::displayHelp() const {
    std::cout << "\n=== 旁白：由机娘大发慈悲地施舍给你的提示 ===" << std::endl;
    std::cout << "移动命令:" << std::endl;
    std::cout << "  move      - 向指定方向移动, 要先move才能选择移动方向" << std::endl;
    std::cout << "  north     - 向北移动" << std::endl;
    std::cout << "  south     - 向南移动" << std::endl;
    std::cout << "  east      - 向东移动" << std::endl;
    std::cout << "  west      - 向西移动" << std::endl;
    std::cout << std::endl;
    std::cout << "查看命令:" << std::endl;
    std::cout << "  look   - 查看当前房间" << std::endl;
    std::cout << "  stats  - 查看玩家状态" << std::endl;
    std::cout << "  map   - 查看游戏地图 " << std::endl;
    std::cout << std::endl;
    std::cout << "交互命令:" << std::endl;
    std::cout << "  interact  - 与当前房间交互，可以触发特殊事件（比如战斗）" << std::endl;
    std::cout << std::endl;
    std::cout << "存档命令:" << std::endl;
    std::cout << "  save      - 保存当前游戏进度" << std::endl;
    std::cout << "  load      - 加载已保存的游戏进度" << std::endl;
    std::cout << std::endl;
    std::cout << "其他命令:" << std::endl;
    std::cout << "  help      - 显示此帮助信息" << std::endl;
    std::cout << "  quit      - 退出游戏" << std::endl;
    std::cout << "==================\n" << std::endl;
}

void Game::movePlayer(const std::string& direction) {
    Room* currentRoom = rooms[player->getCurrentRoom()];
    int nextRoomId = currentRoom->getExits(direction);

    if (nextRoomId >= 0 && nextRoomId < static_cast<int>(rooms.size())) {
        player->setCurrentRoom(nextRoomId);
        std::cout << "你向 " << rooms[nextRoomId]->getRoomName() << " 走去..." << std::endl;
        displayCurrentRoom();
    }
    else {
        std::cout << "那个方向，什么也没有哦" << std::endl;
    }
}

void Game::displayCurrentRoom() const {
    Room* currentRoom = rooms[player->getCurrentRoom()];
    currentRoom->displayRoom();
}

void Game::handleRoomEvent() {
    Room* currentRoom = rooms[player->getCurrentRoom()];
    int roomId = currentRoom->getRoomId();

    switch (roomId) {
    case 0: // 训练场
        if (!currentRoom->isCompleted()) {
            std::cout << "\n当你触摸墙上的符文时，它们突然发出微光。\n";
            std::cout << "一段记忆涌入你的脑海：一位古代守护者正在训练，手中握着闪耀的圣物。\n";
            std::cout << "你似乎理解了某些古老的战斗技巧。\n";
        }
        break;

    case 1: // 家
        std::cout << "\n你翻阅守护者日记，发现更多细节：\n";
        std::cout << "\"三圣物分别藏在哭泣洞穴、幽暗森林和冰封王座。\n";
        std::cout << "它们必须按顺序收集：先光明之石，再勇气徽章，最后智慧宝珠。\n";
        std::cout << "否则，圣物的力量将会相互冲突...\"\n";
        break;

    case 2: // 哭泣洞穴
        if (!currentRoom->isCompleted()) {
            std::cout << "\n当你踏入洞穴，一个苍老的声音在你脑海中回响：\n";
            std::cout << "\"勇敢的守护者，这些地精曾是勤劳的矿工，被黑暗侵蚀了心智。\n";
            std::cout << "只有击败它们，才能取回光明之石，照亮前方的道路...\"\n";
        }
        else {
            std::cout << "\n光明之石在你手中发出温暖的光芒。\n";
            std::cout << "地精们恢复了部分理智，正茫然地看着周围。\n";
        }
        break;

    case 3: // 遗忘图书馆
        if (!currentRoom->isCompleted()) {
            std::cout << "\n老学者向你走来：\"感谢你的帮助，守护者。\n";
            std::cout << "据古籍记载，勇气徽章藏在幽暗森林的深处，被一个强大的树精守护。\n";
            std::cout << "只有真正的勇者才能获得它—而我相信你就是那个人。\"\n";
            std::cout << "他递给你一张详细的地图。\n";
        }
        break;

    case 4: // 幽暗森林
        if (!currentRoom->isCompleted()) {
            std::cout << "\n森林深处传来低沉的声音：\n";
            std::cout << "\"又一个寻求力量的愚者？勇气徽章不会轻易屈服，证明你的价值！\"\n";
        }
        else {
            std::cout << "\n勇气徽章在你胸前闪耀，周围的黑暗似乎退散了一些。\n";
            std::cout << "树精的残骸逐渐化为滋养土壤的养分，森林开始恢复生机。\n";
        }
        break;

    case 5: // 神秘宝箱
        if (!currentRoom->isCompleted()) {
            std::cout << "\n当你打开宝箱，一道强光射出，但不是陷阱。\n";
            std::cout << "箱中是一本古老的战斗手册，书页自动翻动，知识直接涌入你的脑海。\n";
            std::cout << "你感觉自己的战斗技巧提升了！\n";
        }
        break;

    case 6: // 流浪者营地
        if (!currentRoom->isCompleted()) {
            std::cout << "\n独眼战士走向你：\"守护者，时间不多了。\n";
            std::cout << "黑暗领主的爪牙已经前往冰封王座，试图夺取智慧宝珠。\n";
            std::cout << "如果它们得手，黑暗之门将完全开启！你必须阻止它们！\"\n";
            std::cout << "几位流浪者决定加入你的队伍，提供支援。\n";
        }
        break;

    case 7: // 冰封王座
        if (!currentRoom->isCompleted()) {
            std::cout << "\n当你接近王座，冰封的国王突然睁开眼睛：\n";
            std::cout << "\"千百年来，我守护着智慧宝珠，等待真正的守护者。\n";
            std::cout << "证明你配得上这份智慧，击败我的冰霜守卫！\"\n";
        }
        else {
            std::cout << "\n智慧宝珠融入你的意识，古代知识如洪水般涌来。\n";
            std::cout << "你终于明白如何完全激活三圣物的力量，封印黑暗之门。\n";
        }
        break;

    case 8: // 黑暗之门
        if (!currentRoom->isCompleted()) {
            std::cout << "\n黑暗领主的身影越来越清晰：\n";
            std::cout << "\"渺小的人类，你以为凭借那些古老的圣物就能阻止我吗？\n";
            std::cout << "我已经吞噬了无数世界，你的命运也将同样！\"\n";
            std::cout << "三圣物在你手中发出强烈的光芒，准备迎接最终决战！\n";
        }
        else {
            std::cout << "\n黑暗之门已经关闭，世界恢复了和平。\n";
            std::cout << "作为新的守护者，你的传奇将被世人传颂...\n";
        }
        break;
    }

    switch (currentRoom->getRoomType()) {
    case RoomType::BATTLE:
        if (!currentRoom->isCompleted()) {
            startBattle();
        }
        else {
            std::cout << "还想打？没了~" << std::endl;
        }
        break;
    case RoomType::TREASURE:
        if (!currentRoom->isCompleted()) {
            openTreasure();
        }
        else {
            std::cout << "开了一个宝箱还不满足？" << std::endl;
        }
        break;
    case RoomType::REST:
        restAtRoom();
        break;
    case RoomType::BOSS:
        if (!currentRoom->isCompleted()) {
            fightBoss();
        }
        else {
            std::cout << "BOSS已被击败！" << std::endl;
        }
        break;
    default:
        std::cout << "======训练中...=======" << std::endl;
        std::cout << "\n\n训练结束，你的战斗技艺更精湛了" << std::endl;
        break;
    }
}

void Game::startBattle() {
    int roomId = player->getCurrentRoom();

    switch (roomId) {
    case 2: // 哭泣洞穴
        std::cout << "\n地精们发现了你，发出刺耳的尖叫，挥舞着矿工镐冲过来！\n";
        std::cout << "你必须击败它们，取得光明之石！\n";
        break;

    case 4: // 幽暗森林
        std::cout << "\n巨大的树精从地底升起，枝条如鞭子般抽打地面。\n";
        std::cout << "\"勇气徽章只属于真正的勇者！证明你自己！\"它咆哮着。\n";
        break;

    case 7: // 冰封王座
        std::cout << "\n冰霜守卫从四面八方涌现，它们的剑刃闪烁着寒光。\n";
        std::cout << "冰封国王的声音回荡在大厅中：\"展示你的智慧与力量！\"\n";
        break;
    }

    int times = 0;
    int playerchoice = 0;

    while (true) {
        if (times == 0) {
            std::cout << "\n请确认是否开始战斗\n1.开始战斗\n2.取消" << std::endl;
            playerchoice = getValidatedInput(1, 2);
            if (playerchoice == 2) {
                break;
            }
        }
        else {
            std::cout << "\n请确认是否重新开始战斗\n1.重新开始\n2.取消" << std::endl;
            playerchoice = getValidatedInput(1, 2);
            if (playerchoice == 2) {
                break;
            }
        }
        std::cout << "\n=== 战斗开始！ ===" << std::endl;

        std::vector<BattleCharacter> enemyParty;
        std::vector<BattleCharacter> playerParty;
        int roomId = player->getCurrentRoom();

        switch (roomId) {
        case 2:
            enemyParty = PartyCreator::createEasyEnemyParty();
            break;
        case 4:
            enemyParty = PartyCreator::createMediumEnemyParty();
            break;
        case 7:
            enemyParty = PartyCreator::createMediumEnemyParty();
            break;
        default:
            enemyParty = PartyCreator::createEasyEnemyParty();
            break;
        }

        switch (roomId) {
        case 2:
            playerParty = PartyCreator::createPlayerPartyone();
            break;
        case 4:
            playerParty = PartyCreator::createPlayerPartytwo();
            break;
        case 7:
            playerParty = PartyCreator::createPlayerParty();
            break;
        default:
            playerParty = PartyCreator::createPlayerParty();
            break;
        }

        BattleSystem battle(playerParty, enemyParty);
        battle.startBattle();

        if (battle.getCurrentState() == BattleState::FLEE) {
            std::cout << "战斗已终止，返回...\n";
            times++;
            continue;
        }

        if (battle.getCurrentState() == BattleState::DEFEAT) {
            std::cout << "战斗已失败，返回...\n";
            times++;
            continue;
        }

        std::cout << "\n战斗结束! 按回车键继续...";
        std::cin.ignore();
        std::cin.get();
        break;
    }

    if (playerchoice == 1) {
        rooms[player->getCurrentRoom()]->setCompleted(true);
    }
    if (playerchoice == 2) {
        if (times == 0) {
            std::cout << "\n好家伙，试都不试";
        }
        else {
            std::cout << "\n在" << times << "次努力下，没有成功";
        }
    }
}

void Game::openTreasure() {
    std::cout << "\n=== 你打开了宝箱，学习了更精湛的战斗技艺 ===" << std::endl;
    rooms[player->getCurrentRoom()]->setCompleted(true);
}

void Game::restAtRoom() {
    std::cout << "\n=== 休息中... ===" << std::endl;
}

void Game::fightBoss() {
    int playerChoice = 0;
    int times = 0;

    while (playerChoice != 2 && playerChoice != 1) {
        std::cout << "\n请确认是否挑战BOSS\n1.挑战BOSS\n2.取消" << std::endl;
        std::cin >> playerChoice;

        if (playerChoice != 1 && playerChoice != 2) {
            std::cout << "请输入1或2" << std::endl;
        }
        if (playerChoice == 2) {
            std::cout << "你给路打油~~~~~~" << std::endl;
            return;
        }

        std::cout << "\n=== 最终决战 ===" << std::endl;
        std::cout << "黑暗领主完全显现，它的形态不断变化，充满难以名状的恐怖。" << std::endl;
        std::cout << "\"你太迟了，守护者！黑暗之门已经几乎完全开启！\"它嘲笑道。" << std::endl;
        std::cout << "你手中的三圣物发出强烈的光芒，相互共鸣。" << std::endl;
        std::cout << "你知道，这是决定世界命运的一战！" << std::endl;

        std::vector<BattleCharacter> enemyParty = PartyCreator::createBossEnemyParty();
        std::vector<BattleCharacter> playerParty = PartyCreator::createPlayerParty();

        BattleSystem battle(playerParty, enemyParty);
        battle.startBattle();

        if (battle.getCurrentState() == BattleState::VICTORY) {
            std::cout << "\n\n随着黑暗领主的倒下，笼罩世界的阴影开始消散。" << std::endl;
            std::cout << "你手中的三件圣物发出耀眼的光芒，在空中交织成一道强大的封印。" << std::endl;
            std::cout << "黑暗之门缓缓关闭，最后一丝黑暗能量被彻底净化。" << std::endl;
            std::cout << "阳光再次洒满大地，世界终于恢复了和平。" << std::endl;
            std::cout << "作为新的守护者，你的传奇将被世人传颂..." << std::endl;

            std::cout << "\n\n=== 游戏结局 ===" << std::endl;
            std::cout << "1. 继续探索世界" << std::endl;
            std::cout << "2. 返回主菜单" << std::endl;
            std::cout << "选择: ";

            int choice;
            choice = getValidatedInput(1, 2);

            if (choice == 2) {
                stop();
                return;
            }

            rooms[player->getCurrentRoom()]->setCompleted(true);
            break;
        }
        else if (battle.getCurrentState() == BattleState::FLEE) {
            std::cout << "战斗已终止，返回...\n";
            times++;
            return;
        }

        else if (battle.getCurrentState() == BattleState::DEFEAT) {
            std::cout << "战斗已失败，返回...\n";
            times++;
            return;
        }

        std::cout << "\n战斗结束! 按回车键继续...";
        std::cin.ignore();
        std::cin.get();

        if (playerChoice == 1) {
            std::cout << "\n恭喜！你击败了最终BOSS！" << std::endl;
            rooms[player->getCurrentRoom()]->setCompleted(true);
        }

        if (playerChoice == 2) {
            if (times == 0) {
                std::cout << "\n好家伙，试都不试";
            }
            else {
                std::cout << "\n在" << times << "次努力下，没有成功";
            }
        }
    }
}

std::string Game::getSaveFilePath() const {
    return gamedata;
}

void Game::saveGame() const {
    if (!player) return;

    SaveData data;
    data.playerName = player->getName();
   /* data.health = player->getHealth();
    data.maxHealth = player->getMaxHealth();
    data.attack = player->getAttack();
    data.defense = player->getDefense();
    data.level = player->getLevel();
    data.experience = player->getExperience();*/
    data.currentRoom = player->getCurrentRoom();
    data.roomCompleted.reserve(rooms.size());
    //data.playerName = player->getName();
   
   
    for (const Room* room : rooms) {
        data.roomCompleted.push_back(room->isCompleted());
    }

    std::ofstream file(getSaveFilePath(), std::ios::binary);
    if (!file.is_open()) {
        std::cout << "保存失败，无法打开文件！\n";
    }
    else {
        file.write(reinterpret_cast<const char*>(&data), sizeof(data));
        file.close();
        std::cout << "游戏已保存！\n";
    }
}

bool Game::loadGame() {
    std::cout << "开始加载存档..." << std::endl;
    std::ifstream file(getSaveFilePath(), std::ios::binary);
    if (!file.is_open()) {
        std::cout << "没有找到存档文件！\n";
        return false;
    }

    SaveData data;
    file.read(reinterpret_cast<char*>(&data), sizeof(data));

    if (player) {
        delete player;
        //player = nullptr;
    }

    player = new Player(data.playerName);
   /* player->setHealth(data.health);
    player->setMaxHealth(data.maxHealth);
    player->setAttack(data.attack);
    player->setDefense(data.defense);
    player->setLevel(data.level);
    player->setExperience(data.experience);*/
    player->setCurrentRoom(data.currentRoom);

   /* for (size_t i = 0; i < rooms.size() && i < data.roomCompleted.size(); ++i) {
        rooms[i]->setCompleted(data.roomCompleted[i]);
    }*/

    std::cout << "存档加载成功，准备显示当前房间..." << std::endl;
    displayCurrentRoom();
    std::cout << "存档加载流程结束。" << std::endl;
    return true;
}

/*int getValidatedInput(int min, int max) {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请重新输入（" << min << "-" << max << "）：";
        }
        else {
            std::cin.ignore();
            return input;
        }
    }
}*/
void Game::displayMap() {

    //获取玩家当前所在房间id
    int currentRoom = player->getCurrentRoom();

    //创建字符串数组地图，初始为空格*2
    std::vector<std::string> place(9, "  ");


    //在对应坐标位置显示“※”
    place[currentRoom] = " ※";
    // 绘制地图
    std::cout << "                                                  ※ 游戏地图展示：                                                  " << std::endl;
    std::cout << "  ===================================================================================================================" << std::endl;
    std::cout << "                            _____________                                                                                                                            " << std::endl;
    std::cout << "                           |           " << place[8] << "|                                                                                                           " << std::endl;
    std::cout << "                           |  黑暗之门   |                                                                                                                           " << std::endl;
    std::cout << "                           |______ ______|                                                                                                                           " << std::endl;
    std::cout << "                                  |                                                                                                                                  " << std::endl;
    std::cout << "                                  |                                                                                                                                  " << std::endl;
    std::cout << "                            ______|______                                                                                                                            " << std::endl;
    std::cout << "                           |           " << place[7] << "|                                                                                                           " << std::endl;
    std::cout << "                           |  冰封王座   |                                                                                                                           " << std::endl;
    std::cout << "                           |______ ______|                                                                                                                           " << std::endl;
    std::cout << "                                  |                                                                                                                                  " << std::endl;
    std::cout << "                                  |                                                                                                                                  " << std::endl;
    std::cout << "                            ______|______                                     _____________            _____________                                                 " << std::endl;
    std::cout << "                           |           " << place[6] << "|                                   |           " << place[1] << "|          |           " << place[0] << "|" << std::endl;
    std::cout << "                           | 流浪者营地  |                                   | 守护者小屋   ----------  远古训练场  |                                                " << std::endl;
    std::cout << "                           |______ ______|                                   |______ ______|          |_____________|                                                " << std::endl;
    std::cout << "                                  |                                                 |                                                                                " << std::endl;
    std::cout << "                                  |                                                 |                                                                                " << std::endl;
    std::cout << "   _____________            ______|______            _____________            ______|______                                                                          " << std::endl;
    std::cout << "  |           " << place[5] << "|          |           " << place[4] << "|          |           " << place[3] << "|          |           " << place[2] << "|         " << std::endl;
    std::cout << "  |  神秘宝箱    ----------   幽暗森林    ----------  遗忘图书馆   ----------   哭泣洞穴   |                                                                         " << std::endl;
    std::cout << "  |_____________|          |_____________|          |_____________|          |_____________|                                                                         " << std::endl;



    // 地图说明
    std::cout << "\n图例：" << std::endl;
    std::cout << "   [地点名]      - 可探索的区域" << std::endl;
    std::cout << "   ※            - 玩家当前位置" << std::endl;
    std::cout << "   — 或 |       - 可通行的路径" << std::endl;
    std::cout << "   BOSS/精英怪   - 战斗区域" << std::endl;
    std::cout << "   宝藏          - 可获取物品的区域" << std::endl;

    std::cout << "===================================================================================================================" << std::endl << std::endl;
}