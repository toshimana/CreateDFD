#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <CreateDFD.h>

using namespace ::testing;

class CreateDFDTest : public ::testing::Test
{
};

static std::string
createDot( const std::string& body )
{
	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << body;
	ss << "}" << std::endl;

	return ss.str();
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
	ss << FNODE( Test );
	ss << EDGE( A, Test );
	ss << EDGE( Test, B );
	
	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, Single2Test )
{
	std::string input( "Func[C][D]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( Func );
	ss << EDGE( C, Func );
	ss << EDGE( Func, D );

	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, MultiNodeTest )
{
	std::string input( "Test[A,B][C,D]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( Test );
	ss << EDGE( A, Test );
	ss << EDGE( B, Test );
	ss << EDGE( Test, C );
	ss << EDGE( Test, D );

	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, MultiEdgeTest )
{
	std::string input( "Test[A][B]\nFunc[B][C]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( Test );
	ss << FNODE( Func );
	ss << EDGE( A, Test );
	ss << EDGE( Test, B );
	ss << EDGE( B, Func );
	ss << EDGE( Func, C );

	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, ParseFailTest )
{
	std::string input( "Test[A][][]" );
	
	std::string actual = CreateDFD::convert( input );

	ASSERT_THAT( actual, StrEq( "" ) );
}

TEST_F( CreateDFDTest, SingleInputOnlyTest )
{
	std::string input( "Test[A][]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( Test );
	ss << EDGE( A, Test );
	
	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, SingleOutputOnlyTest )
{
	std::string input( "Test[][A]" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( Test );
	ss << EDGE( Test, A );
	
	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, AnyEOLTest )
{
	std::string input( "Test[A][B]\n\n\n" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( Test );
	ss << EDGE( A, Test );
	ss << EDGE( Test, B );
	
	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, DuplicateTest )
{
	std::string input( "Test[A][B]\nTest[C][D]\n" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( Test_000 );
	ss << FNODE( Test_001 );
	ss << EDGE( A, Test_000 );
	ss << EDGE( Test_000, B );
	ss << EDGE( C, Test_001 );
	ss << EDGE( Test_001, D );
	
	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, NoNameFuncTest )
{
	std::string input( "[A][B]\n" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( 000 );
	ss << EDGE( A, 000 );
	ss << EDGE( 000, B );
	
	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

TEST_F( CreateDFDTest, NoNameMultiFuncTest )
{
	std::string input( "[A][B]\n[C][D]\n" );
	
	std::string actual = CreateDFD::convert( input );

	std::stringstream ss;
	ss << FNODE( 000 );
	ss << FNODE( 001 );
	ss << EDGE( A, 000 );
	ss << EDGE( 000, B );
	ss << EDGE( C, 001 );
	ss << EDGE( 001, D );
	
	ASSERT_THAT( actual, StrEq( createDot( ss.str() ) ) );
}

