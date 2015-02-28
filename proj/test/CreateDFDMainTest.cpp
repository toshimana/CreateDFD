#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <CreateDFDMain.h>

using namespace ::testing;

class CreateDFDMainTest : public ::testing::Test
{
};

TEST_F( CreateDFDMainTest, ArgumentsLessThan2 )
{
	char* argv[] = {
		"CreateDFDMain.exe",
	};

	int argc = sizeof( argv ) / sizeof( char* );

	internal::CaptureStderr();
	int ret = CreateDFDMain( argc, argv );
	std::string msg = internal::GetCapturedStderr();

	ASSERT_THAT( ret, Ne( 0 ) );
	ASSERT_THAT( msg, HasSubstr( "ERROR" ) );
}

TEST_F( CreateDFDMainTest, ArgumentsGreaterThan2 )
{
	char* argv[] = {
		"CreateDFDMain.exe",
		"A",
		"B"
	};

	int argc = sizeof( argv ) / sizeof( char* );

	internal::CaptureStderr();
	int ret = CreateDFDMain( argc, argv );
	std::string msg = internal::GetCapturedStderr();

	ASSERT_THAT( ret, Ne( 0 ) );
	ASSERT_THAT( msg, HasSubstr( "ERROR" ) );
}