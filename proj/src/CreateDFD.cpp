#include "CreateDFD.h"
#include "CreateDFD_Impl.h"

#include <sstream>
#include <map>
#include <numeric>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

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

template<typename T> static void
addRenamedFuncEdge( CreateDFD::FuncEdge fe, boost::basic_format<T> format, std::vector<CreateDFD::FuncEdge>& out, std::map<std::string,int>& idCounter )
{
	if ( idCounter.find( fe.func ) == idCounter.end() ){
		idCounter[fe.func] = 0;
	}
	std::stringstream ss;
	ss << ( format % idCounter[fe.func]++).str();

	fe.func = ss.str();
	out.push_back( fe );
}

static void
renameDuplicateEdges( const std::vector<CreateDFD::FuncEdge>& in, std::vector<CreateDFD::FuncEdge>& out )
{
	// ŠÖ”‚Ì“oê•p“x‚Ì‹L˜^
	std::map<std::string, int> counter;
	BOOST_FOREACH( const CreateDFD::FuncEdge& fe, in ) {
		if ( counter.find( fe.func ) == counter.end() ) {
			counter[fe.func] = 1;
		}
		else {
			++counter[fe.func];
		}
	}
	
	// 2‰ñˆÈã“oê‚·‚éŠÖ”‚ÍID‚ğŠ„‚è“–‚Ä‚é
	std::map<std::string, int> idCounter;
	BOOST_FOREACH( const CreateDFD::FuncEdge& fe, in ) {
		if ( fe.func == "" ) {
			addRenamedFuncEdge( fe, boost::format("%03d"), out, idCounter );
		}
		else {
			if ( counter[fe.func] == 1 ) {
				out.push_back( fe );
			}
			else {
				addRenamedFuncEdge( fe, boost::format( "%s_%03d" ) % fe.func, out, idCounter );
			}
		}
	}
}

std::string 
CreateDFD::convert( const std::string& in )
{
	std::vector<FuncEdge> edges;
	bool ret = CreateDFD::Impl::parse( in, edges );

	if ( !ret ) return "";

	std::vector<FuncEdge> renamedEdges;
	renameDuplicateEdges( edges, renamedEdges );

	DFD dfd;
	convertToDFD( renamedEdges, dfd );

	return outputDot( dfd.output() );
}
