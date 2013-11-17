#pragma once
#include "lambda_calculus.hpp"
#include "propositional_logic.hpp"
#include "pair.hpp"
#include "list.hpp"
#include "int.hpp"
#include <iostream>
namespace lambda_calculus
{
	using namespace std;
	static_assert( ToBool< True >::value, "" );
	static_assert( ToBool< Not::apply< True >::value >::value == false, "" );
	static_assert( ToBool< Not::apply< Not::apply< True >::value >::value >::value, "" );
	static_assert( ToBool< True::apply< True >::value::apply< False >::value >::value, "" );
	static_assert( ToBool< And::apply< True >::value::apply< False >::value >::value == false, "" );
	static_assert( ToBool< Or::apply< True >::value::apply< False >::value >::value, "" );
	static_assert( ToBool< First::apply< Pair::apply< True >::value::apply< False >::value >::value >::value, "" );
	static_assert( ToBool< Second::apply< Pair::apply< True >::value::apply< False >::value >::value >::value == false, "" );
	static_assert( ToBool< Null::apply< Pair::apply< True >::value::apply< False >::value >::value >::value == false, "" );
	static_assert( ToBool< Null::apply< Nil >::value >::value, "" );
	static_assert( ToInt< Zero >::value == 0, "" );
	static_assert( ToInt< One >::value == 1, "" );
	static_assert( ToInt< Two >::value == 2, "" );
	static_assert( ToInt< Next::apply< Seven >::value >::value == 8, "" );
	static_assert( ToInt< Plus::apply< Two >::value::apply< Three >::value >::value == 5, "" );
	static_assert( ToInt< Multiply::apply< Zero >::value::apply< One >::value >::value == 0, "" );
	static_assert( ToInt< Multiply::apply< Two >::value::apply< Three >::value >::value == 6, "" );
	static_assert( ToInt< Power::apply< Two >::value::apply< Three >::value >::value == 8, "" );
	int example( )
	{
		cout << "hello world";
		return 0;
	}
}
