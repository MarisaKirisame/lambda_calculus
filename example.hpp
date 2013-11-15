#pragma once
#include "propositional_logic.hpp"
#include "pair.hpp"
#include "list.hpp"
#include "int.hpp"
#include <iostream>
namespace lambda_calculus
{
	using namespace std;
	int example( )
	{
		cout << ToBool< Not::apply< True >::value >::value;
		cout << ToBool< Not::apply< Not::apply< True >::value >::value >::value;
		cout << ToBool< And::apply< True >::value::apply< False >::value >::value;
		cout << ToBool< Or::apply< True >::value::apply< False >::value >::value;
		cout << ToBool< First::apply< Pair::apply< True >::value::apply< False >::value >::value >::value;
		cout << ToBool< Null::apply< Pair::apply< True >::value::apply< False >::value >::value >::value;
		cout << ToBool< Null::apply< Nil >::value >::value;
		cout << ToInt< Seven >::value;
		cout << ToInt< Next::apply< Seven >::value >::value;
		cout << ToInt< Plus::apply< Two >::value::apply< Three >::value >::value;
		cout << ToInt< Multiply::apply< Zero >::value::apply< One >::value >::value;
		cout << ToInt< Multiply::apply< Two >::value::apply< Three >::value >::value;
		cout << ToInt< Power::apply< Two >::value::apply< Three >::value >::value;
		return 0;
	}

}
