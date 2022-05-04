#include <string>
#include <iostream>
#include <vector>
#include <map>
class fileEmulator {

public:
	std::map<std::string, void(fileEmulator::*)(std::string)> instructions;

	fileEmulator() {
		Root.name = "Root";
		mapping(); }
	void ls();
	void pwd();
	void cdo();
	void cd(std::string);
	 void mkdir(std::string);
	 void touch(std::string);
	void rm(std::string);
	void rmdir(std::string);
private:
	struct file {
		std::string name;
		std::vector<std::string>introduction;
	};
	struct folder {
		std::string name{};
		std::vector <file*> files;
		std::vector <folder*>folders;
	};
	folder Root;
	folder* currentfolder=&Root;
	std::string currentpath = "Computer\\User\\Root";
	std::vector<folder*>history ;
	std::string makepath(std::string);
	int folderchange(std::string);
	void mapping();
	void cdfile(file*);
	std::vector<std::string> path_parser(std::string );
};