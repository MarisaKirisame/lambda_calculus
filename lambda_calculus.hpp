#pragma once
#include <type_traits>
namespace lambda_calculus
{
	using namespace std;
	template< typename x, typename y >
	struct application
	{
		template< typename t >
		struct apply
		{
			typedef typename x::template apply< y >::value::template apply< t >::value value;
		};
		template< int depth, typename t >
		struct rebound
		{
			typedef application< typename x::template rebound< depth, t >::value, typename y::template rebound< depth, t >::value > value;
		};
	};

	template< int x >
	struct variable
	{
		template< int depth, typename t >
		struct rebound
		{
			typedef typename conditional< -x == depth, t, variable >::type value;
		};
	};

	template< typename x >
	struct abstraction
	{
		template< typename t >
		struct apply
		{
			typedef typename x::template rebound< 1, t >::value value;
		};
		template< int depth, typename t >
		struct rebound
		{
			typedef abstraction< typename x::template rebound< depth + 1, t >::value > value;
		};
	};
}
