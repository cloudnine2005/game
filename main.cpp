#include <iostream>
#include <string>
#include "Game.h"
#include "room.h"
#include "player.h"
#include "fight.h"

void startUI() {
	// 清屏
	system("cls");

	// 游戏标题
	std::cout << "===================================================================================================================" << std::endl;
	std::cout << "                     _______ _            _____             _      _____                   " << std::endl;
	std::cout << "                    |__   __| |          |  __ \\           | |    |  __ \\                   " << std::endl;
	std::cout << "                       | |  | |__   ___  | |  | | __ _ _ __| | __ | |  | | ___   ___  _ __ " << std::endl;
	std::cout << "                       | |  | '_ \\ / _ \\ | |  | |/ _` | '__| |/ / | |  | |/ _ \\ / _ \\| '__|" << std::endl;
	std::cout << "                       | |  | | | |  __/ | |__| | (_| | |  |   <  | |__| | (_) | (_) | |   " << std::endl;
	std::cout << "                       |_|  |_| |_| ___| |_____/  __,_|_|  |_| _\\ |_____/  ___/  ___/|_|   " << std::endl;
	std::cout << "                                                                                           " << std::endl;
	std::cout << "      _______ _            _____             _      _____  _______ _            _____             _      _____          " << std::endl;
	std::cout << "                                                                                            " << std::endl;
	std::cout << "                                           圣物誓约：黑暗之门 v1.0                          " << std::endl;
	std::cout << "===================================================================================================================" << std::endl << std::endl;

}

	


int main() {
    startUI();
	std::cout << "欢迎来到圣物誓约：黑暗之门！\n";
    std::cout << "====================\n\n";

    Game game;
    game.start();


    std::cout << "\n感谢游玩！再见！\n";
    return 0;
}