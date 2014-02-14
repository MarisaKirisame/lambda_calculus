#pragma once
#include "lambda_calculus.hpp"
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	namespace SKI_combinator_calculus
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
							variable< -3 >,
							variable< -1 >
						>,
						application
						<
							variable< -2 >,
							variable< -1 >
						>
					>
				>
			>
		> S;
		typedef True K;
		typedef abstraction< variable< -1 > > I;
	}
}
