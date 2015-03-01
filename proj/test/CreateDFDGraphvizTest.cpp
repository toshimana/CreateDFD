#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <CreateDFDGraphviz.h>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

using namespace ::testing;

class CreateDFDGraphvizTest : public ::testing::Test
{
protected:
	virtual void SetUp( void );
	virtual void TearDown( void );
	fs::path tempPath;
};

void
CreateDFDGraphvizTest::SetUp( void )
{
	tempPath = fs::unique_path();
}

void
CreateDFDGraphvizTest::TearDown( void )
{
	if ( fs::exists( tempPath ) ) {
		fs::remove( tempPath );
	}
}

TEST_F( CreateDFDGraphvizTest, ConvertTest )
{
	{
		std::ofstream ofs( tempPath.string() );
		ofs << "Func[A][B]";
	}

	int ret = CreateDFDGraphviz::createDFD( tempPath.string() );
	ASSERT_THAT( ret, Eq( 0 ) );

	fs::path pdfPath( tempPath );
	pdfPath.replace_extension( "pdf" );
	ASSERT_TRUE( fs::exists( pdfPath ) );
}