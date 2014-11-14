#ifndef LAMBDA_CALCULUS_LIST
#define LAMBDA_CALCULUS_LIST
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	typedef abstraction< True > Nil;
	typedef
	abstraction
	<
		application
		<
            variable< 1 >,
			abstraction
			<
				abstraction< False >
			>
		>
	> Null;
}
#endif //LAMBDA_CALCULUS_LIST
