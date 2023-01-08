#pragma once


namespace Orange
{
	enum class OpenMode
	{
		Read = 0,
		Write = 1,
		Append = 2,
	};

	class File
	{
	public:
		File(std::string_view filePath, OpenMode openMode);
		virtual ~File();

		void Open();
		void Close();

		void Write(std::string_view text);
		void WriteLine(std::string_view line);

		std::string Read(uint32_t count = 0);
		std::string ReadLine(uint32_t count = 0);
		std::vector<std::string> ReadLines(uint32_t count = 0);

		bool IsOpened() const;
	public:
		static bool Exists(std::string_view filePath);
		static bool Create(std::string_view filePath);
		static bool CreateDir(std::string_view filePath);
		static bool IsFile(std::string_view filePath);
		static bool IsDir(std::string_view filePath);
	private:
		bool CheckForOpen() const;
		bool CheckForWrite() const;
		bool CheckForRead() const;
	private:
		std::string m_FilePath;
		bool m_IsOpened;
		OpenMode m_OpenMode;

		std::unique_ptr<std::fstream> m_Handle;
	};
}
