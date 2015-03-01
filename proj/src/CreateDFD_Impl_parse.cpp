#include "CreateDFD_Impl.h"

/*****************************************************************************/
// 構造体定義
/*****************************************************************************/
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT (
	CreateDFD::FuncEdge,
	( std::string, func )
	( std::vector<std::string>, inNodes )
	( std::vector<std::string>, outNodes )
	)

/*****************************************************************************/
// Boost.Spirit.Qi
// パース処理
/*****************************************************************************/
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

namespace qi = boost::spirit::qi;

namespace CreateDFD
{
	namespace Impl
	{
		template<typename Iterator>
		struct parseFuncEdge
			: qi::grammar<Iterator,std::vector<FuncEdge>()>
		{
			qi::rule<Iterator, std::vector<FuncEdge>()> result;
			qi::rule<Iterator, FuncEdge()> edge;
			qi::rule<Iterator, std::string()> func;
			qi::rule<Iterator, std::vector<std::string>()> nodes;
			qi::rule<Iterator, std::string()> node;

			parseFuncEdge()
				: parseFuncEdge::base_type(result)
			{
				result = edge % qi::eol >> *qi::eol;
				edge = func >> nodes >> nodes;
				func %= qi::lexeme[+(qi::char_ - qi::lit( '[' ))];
				nodes %= qi::lit( '[' ) >> ( node % qi::lit( ',' ) >> qi::lit( ']' ) | qi::lit( ']' ) );
				node  %= qi::lexeme[+(qi::char_ - (qi::lit( ',' ) | qi::lit( ']' )))];
			}
		};
	};
};

bool
CreateDFD::Impl::parse( const std::string& in, std::vector<FuncEdge>& edges )
{
	parseFuncEdge<std::string::iterator> parseFE;

	std::string str( in );
	auto it = str.begin();
	bool ret = qi::parse( it, str.end(), parseFE, edges );
	return ( ret && ( it == str.end() ) );
}

