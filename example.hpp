#ifndef LAMBDA_CALCULUS_EXAMPLE
#define LAMBDA_CALCULUS_EXAMPLE
#include "type_traits"
#include "boost/mpl/same_as.hpp"
#include "boost/mpl/string.hpp"
#include "lambda_calculus.hpp"
#include "propositional_logic.hpp"
#include "pair.hpp"
#include "list.hpp"
#include "church_numeral.hpp"
#include "SKI_combinator_calculus.hpp"
#include <iostream>
namespace lambda_calculus
{
	using namespace std;
	using namespace SKI_combinator_calculus;
	using namespace church_numeral;
	static_assert( ToBool< True >::value, "" );
	static_assert( ToBool< Not::apply< True >::type >::value == false, "" );
	static_assert( ToBool< Not::apply< Not::apply< True >::type >::type >::value, "" );
	static_assert( ToBool< True::apply< True >::type::apply< False >::type >::value, "" );
	static_assert( ToBool< And::apply< True >::type::apply< False >::type >::value == false, "" );
	static_assert( ToBool< Or::apply< True >::type::apply< False >::type >::value, "" );
	static_assert( ToBool< First::apply< Pair::apply< True >::type::apply< False >::type >::type >::value, "" );
	static_assert( ToBool< Second::apply< Pair::apply< True >::type::apply< False >::type >::type >::value == false, "" );
	static_assert( ToBool< Null::apply< Pair::apply< True >::type::apply< False >::type >::type >::value == false, "" );
	static_assert( ToBool< Null::apply< Nil >::type >::value, "" );
	static_assert( ToInt< Zero >::value == 0, "" );
	static_assert( ToInt< One >::value == 1, "" );
	static_assert( ToInt< Two >::value == 2, "" );
	static_assert( ToInt< Next::apply< Seven >::type >::value == 8, "" );
	static_assert( ToInt< Plus::apply< Two >::type::apply< Three >::type >::value == 5, "" );
	static_assert( ToInt< Multiply::apply< Zero >::type::apply< One >::type >::value == 0, "" );
	static_assert( ToInt< Multiply::apply< Two >::type::apply< Three >::type >::value == 6, "" );
	static_assert( ToInt< Power::apply< Two >::type::apply< Three >::type >::value == 8, "" );
	static_assert( ToInt< Power::apply< Three >::type::apply< Three >::type >::value == 27, "" );
	static_assert( ToBool< I::apply< True >::type >::value, "" );
	static_assert( ToBool< K::apply< True >::type::apply< False >::type >::value, "" );
	typedef S::apply< K >::type::apply< S >::type::apply< K >::type SKSK;
	static_assert( ToBool< SKSK >::value, "" );
	static_assert( ToBool< SKI_combinator_calculus::SKI_parser::apply< boost::mpl::string< '(SK)','(I(I','S)) ',' K  ' > >::type >::value, "" );
	static_assert( ToInt< Int< 12 >::type >::value == 12, "" );
	int example( )
	{
		cout << "hello world";
		return 0;
	}
}
#endif //LAMBDA_CALCULUS_EXAMPLE
