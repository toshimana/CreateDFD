#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <CreateDFD.h>

using namespace ::testing;

class CreateDFDTest : public ::testing::Test
{
 protected:
  virtual void SetUp(void);
  virtual void TearDown(void);
  static  void SetUpTestCase(void);
  static  void TearDownTestCase(void); 
};

void CreateDFDTest::SetUp(void)
{
}

void CreateDFDTest::TearDown(void)
{
}

void CreateDFDTest::SetUpTestCase(void)
{
}

void CreateDFDTest::TearDownTestCase(void)
{
}

TEST_F( CreateDFDTest, SingleTest )
{
	std::string input( "Test[A][B]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << "\tA -> Test -> B" << std::endl;
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}

TEST_F( CreateDFDTest, Single2Test )
{
	std::string input( "Func[C][D]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << "\tC -> Func -> D" << std::endl;
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}

