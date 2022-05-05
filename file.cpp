#include "file.h"

void fileEmulator::ls() {

    for (int i = 0; i < (currentfolder->folders).size(); ++i) {
        std::cout << currentfolder->folders[i]->name << std::endl;
    }
    for (int i = 0; i < currentfolder->files.size(); ++i) {
        std::cout << currentfolder->files[i]->name << std::endl;
    }
}


void fileEmulator::pwd() {
    std::cout << currentpath << std::endl;
}

void fileEmulator::cdo() {
    if (history.size() < 1) {
        std::cout << "You are in Root there aren't any previous folder" << std::endl;
        return;
    }
  
    int i = currentpath.length() - 2;
    while (currentpath[i + 2] != 92) {
        currentpath.erase(currentpath.begin() + i + 2);
        --i;
    }
    ++i;
    currentpath.erase(currentpath.begin() + i + 1, currentpath.begin() + i + 2);
    int j = history.size() - 1;
    currentfolder = history[j];
    history.erase(history.begin() + j + 1, history.end());

}


void fileEmulator::cd(std::string path) {
    std::vector<std::string>items = path_parser(path);
    for (int i = 0; i < items.size(); ++i) {
        switch (folderchange(items[i])) {//1 case of direction, 2case of file
            case 1: makepath(items[i]);
                break;
            case 2: return;
            case 0:std::cout << "unknown file or folder"<<std::endl;
                break;
        }
    }
}


void fileEmulator::mkdir(std::string name) {
    std::shared_ptr<folder> a(new folder);
    a->name = name;
    currentfolder->folders.push_back(a);
}


void fileEmulator::touch(std::string name) {
    std::shared_ptr<file> a(new file);
    a->name = name;
    currentfolder->files.push_back(a);
}



void fileEmulator::rm(std::string name) {
    for (int i = 0; i < currentfolder->files.size(); ++i) {
        if (currentfolder->files[i]->name == name) {
            currentfolder->files.erase(currentfolder->files.begin() + i);
            return;
        }
    }
     std::cout << "unknown file" << std::endl;

}


void fileEmulator::rmdir(std::string name) {
    for (int i = 0; i < currentfolder->folders.size(); ++i) {
        if (currentfolder->folders[i]->name == name) {
            currentfolder->folders.erase(currentfolder->folders.begin() + i);
            return;
        }
    }
      std::cout << "unknown direction" << std::endl;
}


void fileEmulator::makepath(std::string name) {
    currentpath += ("\\" + name);
}


int fileEmulator::folderchange(std::string name) {;
    for (int i = 0; i < currentfolder->folders.size(); ++i) {
        if (currentfolder->folders[i]->name == name) {
            history.push_back(currentfolder);
            currentfolder = currentfolder->folders[i];
            return 1;
        }
    }
    for (int i = 0; i < currentfolder->files.size(); ++i) {
        if (currentfolder->files[i]->name == name) {
            cdfile(currentfolder->files[i]);
            return 2;
        }
    }
    return 0;
}


void fileEmulator::cdfile(std::shared_ptr<file> name) {
    std::cout << "you are in " << name->name << " enter introduction, for exit enter ~" << std::endl;
    for (int i = 0; i < name->introduction.size(); ++i) {
        std::cout << name->introduction[i]<<" ";
    }
    currentfolder->name = name->name;
    std::string n;
    while (n != "~") {
        name->introduction.push_back(n);
        std::cin >> n;
    }
}
void fileEmulator::mapping() {
    instructions.emplace("cd", & fileEmulator::cd);
    instructions.emplace("mkdir" , &fileEmulator::mkdir);
    instructions.emplace("rmdir", &fileEmulator::rmdir);
    instructions.emplace("rm", &fileEmulator::rm);
    instructions.emplace("touch", &fileEmulator::touch); 
}
  

std::vector<std::string> fileEmulator::path_parser(std::string path) {
    std::vector<std::string> items;
    std::string tmp;
    for (int i = 0; i < path.length(); ++i) {
        tmp += path[i];
        if (path[i + 1] == 92) {
            items.push_back(tmp);
            tmp = "";
            ++i;
        }
        else if (path[i + 1] == '\0')
            items.push_back(tmp);
    }
    return items;
}
