#include "pchOrange.h"
#include "File.h"


namespace Orange
{
	File::File(std::string_view filePath, OpenMode openMode)
		:m_IsOpened(false), m_FilePath(filePath), m_OpenMode(openMode)
	{
		Open();
	}

	File::~File()
	{
		Close();
	}

	void File::Open()
	{
		if (!m_IsOpened)
		{
			m_IsOpened = true;

			std::ios_base::openmode mode = 0;

			switch (m_OpenMode)
			{
			case Orange::OpenMode::Read:
				ORANGE_ASSERT(Exists(m_FilePath), "You can not read from an unexisting file! File: '{0}'", m_FilePath);
				mode = std::ios_base::in;
				break;
			case Orange::OpenMode::Write:
				mode = std::ios_base::out;
				break;
			case Orange::OpenMode::Append:
				mode = std::ios_base::app;
				break;
			}

			m_Handle = std::make_unique<std::fstream>(m_FilePath.data(), mode);
		}
	}

	void File::Close()
	{
		if (m_IsOpened)
		{
			m_IsOpened = false;
			m_Handle->close();
		}
	}

	void File::Write(std::string_view text)
	{
		if (CheckForOpen() && CheckForWrite())
		{
			(*m_Handle) << text;
		}
	}

	void File::WriteLine(std::string_view line)
	{
		if (CheckForOpen() && CheckForWrite())
		{
			(*m_Handle) << line << '\n';
		}
	}

	std::string File::Read(uint32_t count)
	{
		if (CheckForOpen() && CheckForRead())
		{
			if (count == 0)
			{
				std::stringstream ss;
				ss << m_Handle->rdbuf();
				return ss.str();
			}
			char* buf = Alloc<char>(count + 1);
			m_Handle->get(buf, count + 1);
			std::string str = buf;
			delete[] buf;
			return str;
		}
		return "";
	}

	std::string File::ReadLine(uint32_t count)
	{
		if (CheckForOpen() && CheckForRead())
		{
			if (count == 0)
			{
				std::string str;
				std::getline(*m_Handle, str);
				return str;
			}
			char* buf = new char[count];
			m_Handle->get(buf, count, '\n');
			std::string str = buf;
			delete[] buf;
			return str;
		}
		return "";
	}

	std::vector<std::string> File::ReadLines(uint32_t count)
	{
		std::vector<std::string> lines;
		if (CheckForOpen() && CheckForRead())
		{
			std::string line;

			if (count == 0)
			{
				while (std::getline(*m_Handle, line))
					lines.push_back(line);
			}
			else
			{
				while (std::getline(*m_Handle, line))
				{
					lines.push_back(line);
					count--;
					if (count == 0)
						break;
				}
			}
		}
		
		return lines;
	}

	bool File::IsOpened() const
	{
		return m_IsOpened;
	}

	bool File::Exists(std::string_view filePath)
	{
		struct stat buffer;
		return (stat(filePath.data(), &buffer) == 0);
	}

	bool File::Create(std::string_view filePath)
	{
		if (!Exists(filePath))
		{
			File file = File(filePath, OpenMode::Write);
			file.Close();
			return true;
		}
		else
		{
			ORANGE_ERROR("File '{0}' already exists!", filePath.data());
		}
	}

	bool File::CreateDir(std::string_view filePath)
	{
		if (!Exists(filePath))
		{
			if (mkdir(filePath.data()) == -1)
				ORANGE_ERROR(strerror(errno));
			else
				return true;
		}
		else
		{
			ORANGE_ERROR("Directory '{0}' already exists!", filePath.data());
		}
		return false;
	}

	bool File::IsFile(std::string_view filePath)
	{
		struct stat buffer;
		if (stat(filePath.data(), &buffer) == 0)
		{
			if (buffer.st_mode & S_IFREG)
			{
				return true;
			}
		}
		else
		{
			ORANGE_ERROR("File or directory '{0}' does not exist", filePath);
		}
		return false;
	}

	bool File::IsDir(std::string_view filePath)
	{
		struct stat buffer;
		if (stat(filePath.data(), &buffer) == 0)
		{
			if (buffer.st_mode & S_IFDIR)
			{
				return true;
			}
		}
		else
		{
			ORANGE_ERROR("File or directory '{0}' does not exist", filePath);
		}
		return false;
	}

	bool File::CheckForOpen() const
	{
		if (!m_IsOpened)
		{
			ORANGE_ERROR("Invalid operation on closed file: '{0}'", m_FilePath);
			return false;
		}
		return true;
	}

	bool File::CheckForWrite() const
	{
		if (m_OpenMode == OpenMode::Write || m_OpenMode == OpenMode::Append)
		{
			return true;
		}
		ORANGE_ERROR("Can't write to file: '{0}'", m_FilePath);
		return false;
	}

	bool File::CheckForRead() const
	{
		if (m_OpenMode == OpenMode::Read)
		{
			return true;
		}
		ORANGE_ERROR("Can't read from file: '{0}'", m_FilePath);
		return false;
	}
}