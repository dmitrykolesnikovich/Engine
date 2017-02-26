#include "core/file.h"
#include "core/debug.h"
#include "core/vector.h"

#include "catch.hpp"

namespace
{
	const char* fileName = "file_test_output";
	const char* folder1 = "file_test_folder";
	const char* folder2 = "file_test_folder/subfolder";

	const u8 testData[8] = {1, 2, 3, 4, 5, 6, 7, 8};

	void Cleanup()
	{
		if(Core::FileExists(fileName))
		{
			REQUIRE(Core::FileRemove(fileName));
		}

		if(Core::FileExists(folder2))
		{
			REQUIRE(Core::FileRemoveDir(folder2));
		}

		if(Core::FileExists(folder1))
		{
			REQUIRE(Core::FileRemoveDir(folder1));
		}
	}

	struct ScopedCleanup
	{
		ScopedCleanup() { Cleanup(); }

		~ScopedCleanup() { Cleanup(); }
	};

	void WriteTestData(Core::File& file, i64 offset, i64 bytes)
	{
		DBG_ASSERT(bytes <= 8);
		if(offset == 0)
		{
			REQUIRE(file.Write(&testData[0], bytes) == bytes);
		}
		else
		{
			for(i64 i = 0; i < bytes; ++i)
			{
				i64 j = (i + offset) % 8;
				REQUIRE(file.Write(&testData[j], 1) == 1);
			}
		}
	}

	void ReadTestData(Core::File& file, i64 offset, i64 bytes)
	{
		DBG_ASSERT(bytes <= 8);
		u8 readData[8] = {0};
		REQUIRE(file.Read(readData, bytes));
		for(i64 i = 0; i < bytes; ++i)
		{
			i64 j = (i + offset) % 8;
			REQUIRE(readData[i] == testData[j]);
		}
	}
}

TEST_CASE("file-tests-create")
{
	ScopedCleanup scopedCleanup;

	{
		Core::File file(fileName, Core::FileFlags::CREATE | Core::FileFlags::WRITE);
	}

	REQUIRE(Core::FileExists(fileName));
}

TEST_CASE("file-tests-write")
{
	ScopedCleanup scopedCleanup;

	{
		Core::File file(fileName, Core::FileFlags::CREATE | Core::FileFlags::WRITE);
		WriteTestData(file, 0, 8);
	}

	REQUIRE(Core::FileExists(fileName));
	{
		Core::File file(fileName, Core::FileFlags::READ);
		ReadTestData(file, 0, 8);
	}
}

TEST_CASE("file-tests-tell")
{
	ScopedCleanup scopedCleanup;

	{
		Core::File file(fileName, Core::FileFlags::CREATE | Core::FileFlags::WRITE);
		WriteTestData(file, 0, 4);
		REQUIRE(file.Tell() == 4);
		WriteTestData(file, 4, 4);
		REQUIRE(file.Tell() == 8);
	}

	REQUIRE(Core::FileExists(fileName));
	{
		Core::File file(fileName, Core::FileFlags::READ);
		ReadTestData(file, 0, 4);
		REQUIRE(file.Tell() == 4);
		ReadTestData(file, 4, 4);
		REQUIRE(file.Tell() == 8);
	}
}

TEST_CASE("file-tests-seek")
{
	ScopedCleanup scopedCleanup;

	{
		Core::File file(fileName, Core::FileFlags::CREATE | Core::FileFlags::WRITE);
		WriteTestData(file, 0, 8);
		REQUIRE(file.Seek(4));
		WriteTestData(file, 0, 4);
		WriteTestData(file, 0, 8);
		REQUIRE(file.Tell() == 16);
	}

	REQUIRE(Core::FileExists(fileName));
	{
		Core::File file(fileName, Core::FileFlags::READ);
		ReadTestData(file, 0, 4);
		ReadTestData(file, 0, 4);
		ReadTestData(file, 0, 8);
		REQUIRE(file.Seek(8));
		ReadTestData(file, 0, 8);
	}
}

TEST_CASE("file-tests-size")
{
	ScopedCleanup scopedCleanup;

	{
		Core::File file(fileName, Core::FileFlags::CREATE | Core::FileFlags::WRITE);
		WriteTestData(file, 0, 8);
	}

	REQUIRE(Core::FileExists(fileName));

	{
		Core::File file(fileName, Core::FileFlags::READ);
		REQUIRE(file.Size() == 8);
	}

	{
		Core::File file(fileName, Core::FileFlags::CREATE | Core::FileFlags::WRITE);
		WriteTestData(file, 0, 8);
		WriteTestData(file, 0, 8);
	}

	REQUIRE(Core::FileExists(fileName));

	{
		Core::File file(fileName, Core::FileFlags::READ);
		REQUIRE(file.Size() == 16);
	}
}

TEST_CASE("file-tests-create-dir")
{
	ScopedCleanup scopedCleanup;

	REQUIRE(Core::FileCreateDir(folder1));
	REQUIRE(Core::FileExists(folder1));
	REQUIRE(Core::FileRemoveDir(folder1));

	REQUIRE(Core::FileCreateDir(folder2));
	REQUIRE(Core::FileExists(folder1));
	REQUIRE(Core::FileExists(folder2));
	REQUIRE(Core::FileRemoveDir(folder2));
	REQUIRE(!Core::FileExists(folder2));
	REQUIRE(Core::FileRemoveDir(folder1));
	REQUIRE(!Core::FileExists(folder1));
}

TEST_CASE("file-tests-find-files")
{
	i32 foundFiles = Core::FileFindInPath(".", nullptr, nullptr, 0);
	REQUIRE(foundFiles > 0);

	Core::Vector<Core::FileInfo> fileInfos;
	fileInfos.resize(foundFiles);

	foundFiles = Core::FileFindInPath(".", nullptr, fileInfos.data(), fileInfos.size());	
}

