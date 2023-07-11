#include "FileIO.h"

namespace Vang::FileIO {

	std::optional<std::string> readFile(std::filesystem::path path) {
		std::string file_data;
		std::ifstream fileStream{path};

		// Read From File
		if (!fileStream.is_open()) {
			VANG_ERROR("Could not read file!");
			return std::nullopt;
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			file_data.append(line + "\n");
		}

		fileStream.close();

		return file_data;
	}

}