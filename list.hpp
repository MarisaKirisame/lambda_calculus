#pragma once
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	typedef abstraction< True > Nil;
	typedef
	abstraction
	<
		application
		<
			variable< -1 >,
			abstraction
			<
				abstraction< False >
			>
		>
	> Null;
}
