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

static std::string
createNode( const std::string& A, const std::string& B )
{
	std::stringstream ss;
	ss << '\t' << A << " -> " << B << std::endl;
	return ss.str();
}

#define NODE(A,B) createNode(#A,#B)

TEST_F( CreateDFDTest, SingleTest )
{
	std::string input( "Test[A][B]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << NODE( A, Test );
	ss << NODE( Test, B );
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}

TEST_F( CreateDFDTest, Single2Test )
{
	std::string input( "Func[C][D]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << NODE( C, Func );
	ss << NODE( Func, D );
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}

TEST_F( CreateDFDTest, MultiNodeTest )
{
	std::string input( "Test[A,B][C,D]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << NODE( A, Test );
	ss << NODE( B, Test );
	ss << NODE( Test, C );
	ss << NODE( Test, D );
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}