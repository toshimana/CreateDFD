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
createFNode( const std::string& A )
{
	std::stringstream ss;
	ss << '\t' << A << "[shape=diamond]" << std::endl;
	return ss.str();
}

static std::string
createEdge( const std::string& A, const std::string& B )
{
	std::stringstream ss;
	ss << '\t' << A << " -> " << B << std::endl;
	return ss.str();
}

#define FNODE(A)  createFNode(#A)
#define EDGE(A,B) createEdge(#A,#B)

TEST_F( CreateDFDTest, SingleTest )
{
	std::string input( "Test[A][B]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << FNODE( Test );
	ss << EDGE( A, Test );
	ss << EDGE( Test, B );
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}

TEST_F( CreateDFDTest, Single2Test )
{
	std::string input( "Func[C][D]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << FNODE( Func );
	ss << EDGE( C, Func );
	ss << EDGE( Func, D );
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}

TEST_F( CreateDFDTest, MultiNodeTest )
{
	std::string input( "Test[A,B][C,D]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << FNODE( Test );
	ss << EDGE( A, Test );
	ss << EDGE( B, Test );
	ss << EDGE( Test, C );
	ss << EDGE( Test, D );
	ss << "}" << std::endl;

	ASSERT_THAT( actual, StrEq( ss.str() ) );
}