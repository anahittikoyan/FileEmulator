#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include<memory>
class fileEmulator {

public:
	std::map<std::string, void(fileEmulator::*)(std::string)> instructions;

	fileEmulator();
	fileEmulator(const fileEmulator&) = delete;
	fileEmulator(const fileEmulator&&) = delete;
	fileEmulator& operator=(const fileEmulator&) = delete;
	fileEmulator& operator=(const fileEmulator&&) = delete;
	~fileEmulator() = default;

	void ls() const;
	void pwd() const;
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
		std::vector < std::shared_ptr<file>> files;
		std::vector < std::shared_ptr<folder>>folders;
	};
	std::shared_ptr<folder> currentfolder ;
	std::string currentpath = "Computer\\User\\Root";
	std::vector<std::shared_ptr<folder>>history ;
	
	void makepath(std::string);
	int folderchange(std::string);
	void mapping();
	void cdfile(std::shared_ptr<file>);
	std::vector<std::string> path_parser(std::string );
};

#endif
