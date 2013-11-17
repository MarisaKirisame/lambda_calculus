#pragma once
#include "lambda_calculus.hpp"
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	typedef
	abstraction
	<
		abstraction
		<
			abstraction
			<
				application
				<
					application
					<
						variable< -1 >,
						variable< -3 >
					>,
					variable< -2 >
				>
			>
		>
	> Pair;
	typedef
	abstraction
	<
		application
		<
			variable< -1 >,
			True
		>
	> First;
	typedef
	abstraction
	<
		application
		<
			variable< -1 >,
			False
		>
	> Second;
}
