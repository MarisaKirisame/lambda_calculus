#ifndef LAMBDA_CALCULUS
#define LAMBDA_CALCULUS
#include <type_traits>
namespace lambda_calculus
{
	using namespace std;
	template< typename x, typename y >
	struct application
	{
		template< typename t >
		struct apply
		{ typedef typename x::template apply< y >::type::template apply< t >::type type; };
		template< int depth, typename t >
		struct rebound
		{ typedef application< typename x::template rebound< depth, t >::type, typename y::template rebound< depth, t >::type > type; };
	};

	template< int x >
	struct variable
	{
		template< int depth, typename t >
		struct rebound
        { typedef typename conditional< x == depth, t, variable >::type type; };
	};

	template< typename x >
	struct abstraction
	{
		template< typename t >
		struct apply
		{ typedef typename x::template rebound< 1, t >::type type; };
		template< int depth, typename t >
		struct rebound
        { typedef abstraction< typename x::template rebound< depth + 1, t >::type > type; };
	};
}
#endif //LAMBDA_CALCULUS
