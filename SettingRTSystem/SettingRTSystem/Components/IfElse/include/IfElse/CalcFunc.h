// -*- C++ -*-
/*!
 * @file  DyPortBase.h
 * @brief 
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef CALCFUNC_H
#define CALCFUNC_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <vector>
#include <coil/stringutil.h>

using namespace boost::spirit;
using namespace boost;

template<typename Iterator, class dataType>
struct bool_grammar : qi::grammar<Iterator, bool(), ascii::space_type>{
	bool_grammar() : bool_grammar::base_type(expr){ // formulaから開始
    using qi::lit;
	expr = b0[_val = _1] >> *("||" >> b0[_val |= _1]);
	b0 = b1[_val = _1] >> *("&&" >> b1[_val &= _1]);
	b1 = '!' >> b1[_val = !_1] | b2[_val = _1];
	b2 = bool_[_val = _1] | b3[_val = _1] | '(' >> expr[_val = _1] >> ')';
	b3 = (v0 >> '<' >> v0)[_val = _1 < _2] | (v0 >> '>' >> v0)[_val = _1 > _2];
	v0 = v1[_val = _1] >> *('+' >> v1[_val += _1] | '-' >> v1[_val -= _1]);
	v1 = v2[_val = _1] >> *('*' >> v2[_val *= _1] | '/' >> v2[_val /= _1]);
	v2 = double_[_val = _1] | '(' >> v0[_val = _1] >> ')';
  }
	qi::rule<Iterator, dataType(), ascii::space_type> v0, v1, v2;
	qi::rule<Iterator, bool(), ascii::space_type> expr, b0, b1, b2, b3;
};

template<typename Iterator, class dataType>
struct calc_grammar : qi::grammar<Iterator, dataType(), ascii::space_type>{
	calc_grammar() : calc_grammar::base_type(v0){
		using qi::lit;

		v0 = v1[_val = _1] >> *('+' >> v1[_val += _1] | '-' >> v1[_val -= _1]);
		v1 = v2[_val = _1] >> *('*' >> v2[_val *= _1] | '/' >> v2[_val /= _1]);
		v2 = double_[_val = _1] | '(' >> v0[_val = _1] >> ')';
	}
	qi::rule<Iterator, dataType(), ascii::space_type>  v0, v1, v2;
};

template<class dataType>
std::string getTextReplaceVal(std::vector<dataType> v, std::string text)
{
	std::string ans = text;

	std::vector<std::string> vn;
	int count = 0;
	for (std::vector<dataType>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::string value = coil::otos<dataType>(*it);
		
		std::string num = "u" + coil::otos<int>(count);
		
		coil::replaceString(ans, num, value);
		count += 1;
	}
	return ans;
}

#endif 
