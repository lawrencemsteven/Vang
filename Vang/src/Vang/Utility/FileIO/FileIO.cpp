#include "FileIO.h"

namespace Vang::Utility::FileIO {

	std::optional<std::string> readFile(const std::filesystem::path& path) {
		std::ifstream fileStream{path};

		// Read From File
		if (!fileStream.is_open()) {
			VANG_ERROR("Could not read file!");
			return std::nullopt;
		}

		std::string line;
		std::string file_data;

		while (!fileStream.eof()) {
			line.clear();
			std::getline(fileStream, line);
			file_data.append(std::move(line) + "\n");
		}

		return file_data;
	}

	FileWriter::FileWriter(std::filesystem::path path, const bool clearFile)
		: m_path{std::move(path)},
		  m_fileStream{m_path, clearFile ? std::ofstream::trunc : std::ofstream::app} {
		// TODO: Ensure this will never fail
		if (!m_fileStream.is_open()) {
			VANG_ERROR("Could not open file!");
		}
	}

	FileWriter::~FileWriter() {
		m_fileStream.close();
	}

	void FileWriter::write(const std::string& text) {
		m_fileStream << text;
	}

	void FileWriter::writeLine(const std::string& text) {
		write(text);
		write("\n");
	}

	void FileWriter::clearFile() {
		m_fileStream.close();
		m_fileStream = std::ofstream{m_path, std::ofstream::trunc};
	}

}