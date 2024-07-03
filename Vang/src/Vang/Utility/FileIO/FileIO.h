#pragma once

namespace Vang::Utility::FileIO {

	// TODO: Deprecated, use Vang::Utility::FileIO::FileReader
	std::optional<std::string> readFile(const std::filesystem::path& path);

	// TODO: FileReader
	class FileReader {
		FileReader(std::filesystem::path path);
		~FileReader();
		FileReader(const FileReader&)			 = delete;
		FileReader(FileReader&&)				 = default;
		FileReader& operator=(const FileReader&) = delete;
		FileReader& operator=(FileReader&&)		 = default;
	};

	class FileWriter {
	public:
		FileWriter(std::filesystem::path path, const bool clearFile = true);
		~FileWriter();
		FileWriter(const FileWriter&)			 = delete;
		FileWriter(FileWriter&&)				 = default;
		FileWriter& operator=(const FileWriter&) = delete;
		FileWriter& operator=(FileWriter&&)		 = default;

		void write(const std::string& text);
		void writeLine(const std::string& text);

		void clearFile();

	private:
		std::filesystem::path m_path;
		std::ofstream m_fileStream;
	};

}
