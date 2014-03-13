#ifndef LAMBDA_CALCULUS_Y_COMBINATOR
#define LAMBDA_CALCULUS_Y_COMBINATOR
#include "lambda_calculus.hpp"
namespace lambda_calculus
{
	typedef
	abstraction
	<
		application
		<
			abstraction
			<
				application
				<
					variable< -2 >,
					application
					<
						variable< -1 >,
						variable< -1 >
					>
				>
			>,
			abstraction
			<
				application
				<
					variable< -2 >,
					application
					<
						variable< -1 >,
						variable< -1 >
					>
				>
			>
		>
	> Y;
}
#endif //LAMBDA_CALCULUS_Y_COMBINATOR
