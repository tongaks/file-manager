#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <stdio.h>

void MoveFile(std::string c_path, std::string n_path) {

	std::ifstream c_file(c_path, std::ios::ate | std::ios::binary);

	if (!c_file) {
		std::cout << "File was not found";
		return;
	}

	int file_size = c_file.tellg();
	c_file.seekg(0, std::ios::beg);	

	std::vector<char> buffer(file_size);
	if (!c_file.read(buffer.data(), file_size)) {
		std::cout << "Error reading the file.\n";
		return;
	}

	std::ofstream n_file(n_path, std::ios::binary);
	n_file.write(&buffer[0], file_size);

	c_file.close();
	n_file.close();

	std::remove(c_path.c_str());
}

void CopyFile(std::string c_path, std::string n_path) {

	std::ifstream c_file(c_path, std::ios::ate | std::ios::binary);

	if (!c_file) {
		std::cout << "File was not found";
		return;
	}

	int file_size = c_file.tellg();
	c_file.seekg(0, std::ios::beg);	

	std::vector<char> buffer(file_size);
	if (!c_file.read(buffer.data(), file_size)) {
		std::cout << "Error reading the file.\n";
		return;
	}

	std::ofstream n_file(n_path, std::ios::binary);
	n_file.write(&buffer[0], file_size);

	c_file.close();
	n_file.close();
}

void DeleteFile(std::string path) {
	std::remove(path.c_str());
}

int GetFileCount(std::string path) {
	int count = 0;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    	count++;

    return count;
}