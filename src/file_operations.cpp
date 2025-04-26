#include "../headers/window.h"

void Window::MoveFile(std::string c_path, std::string n_path) {

	std::string file_path = c_path; 
	if (c_path.find(cur_path) != 0) {
		file_path.insert(0, cur_path);
	}

	std::string destination = n_path;
	if (n_path.find(cur_path) != 0) {
		destination.insert(0, cur_path);
	}

	std::cout << file_path << "\n";

	std::ifstream c_file(file_path, std::ios::ate | std::ios::binary);

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

	std::ofstream n_file(destination, std::ios::binary);
	n_file.write(&buffer[0], file_size);

	c_file.close();
	n_file.close();

	std::remove(file_path.c_str());
}

void Window::CopyFile(std::string c_path, std::string n_path) {

	std::string file_path = c_path; 
	if (c_path.find(cur_path) != 0) {
		file_path.insert(0, cur_path);
	}

	std::cout << file_path << "\n";

	std::ifstream c_file(file_path, std::ios::ate | std::ios::binary);

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

void Window::DeleteFile(std::string path) {
	std::remove(path.c_str());
}

void Window::MakeFile(std::string fname) {
	std::string file_path = fname; 
	if (fname.find(cur_path) != 0) {
		file_path.insert(0, cur_path);
	}

	std::cout << file_path << "\n";

	std::ofstream file(file_path);
}

// int GetFileCount(std::string path) {
// 	int count = 0;
//     for (const auto & entry : std::filesystem::directory_iterator(path))
//     	count++;

//     return count;
// }