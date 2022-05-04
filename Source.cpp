#include "file.h"
int main() {
	fileEmulator em;
	std::string now, inst;

	while (true) {
		std::cin >> now;
		if (now == "cd..") em.cdo();
		else if (now == "ls")em.ls();
		else if (now == "pwd")em.pwd();
		else if (em.instructions.count(now)) {
			std::cin >> inst;
			(em.*(em.instructions[now]))(inst);
		}
		else std::cout << "unknown command" << std::endl;
	}
}