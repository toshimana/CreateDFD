#include "CreateDFD.h"
#include "CreateDFD_Impl.h"

#include <sstream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

static std::string
outputDot( const std::string& body )
{
	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << body;
	ss << "}" << std::endl;

	return ss.str();
}

namespace CreateDFD
{
	struct DFD
	{
		typedef std::pair<std::string, std::string> Edge;
		std::vector<std::string> nodes;
		std::vector<Edge> edges;

		void push_back( const FuncEdge& fe )
		{
			nodes.push_back( fe.func );
			BOOST_FOREACH( const std::string& node, fe.inNodes ) {
				edges.push_back( std::make_pair( node, fe.func ) );
			}
			BOOST_FOREACH( const std::string& node, fe.outNodes ) {
				edges.push_back( std::make_pair( fe.func, node ) );
			}
		}

		std::string output() const
		{
			std::stringstream ss;
			BOOST_FOREACH( const std::string& node, nodes ){
				ss << '\t' << node << "[shape=diamond]" << std::endl;
			}
			BOOST_FOREACH( const Edge& edge, edges ){
				ss << '\t' << edge.first << " -> " << edge.second << std::endl;
			}
			return ss.str();
		}
	};
}

static void
convertToDFD( const std::vector<CreateDFD::FuncEdge>& edges, CreateDFD::DFD& dfd )
{
	BOOST_FOREACH( const CreateDFD::FuncEdge& edge, edges ){
		dfd.push_back( edge ); 
	}
}

std::string 
CreateDFD::convert( const std::string& in )
{
	std::vector<FuncEdge> edges;
	bool ret = CreateDFD::Impl::parse( in, edges );

	if ( !ret ) return "";

	DFD dfd;
	convertToDFD( edges, dfd );

	return outputDot( dfd.output() );
}
