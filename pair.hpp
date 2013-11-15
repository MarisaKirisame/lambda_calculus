#pragma once
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	struct Pair
	{
		template< typename x >
		struct apply
		{
			struct value
			{
				template< typename y >
				struct apply
				{
					struct value
					{
						template< typename z >
						struct apply
						{
							typedef typename z::template apply< x >::value::template apply< y >::value value;
						};
					};
				};
			};
		};
	};
	struct First
	{
		template< typename x >
		struct apply
		{
			typedef typename x::template apply< True >::value value;
		};
	};
	struct Second
	{
		template< typename x >
		struct apply
		{
			typedef typename x::template apply< False >::value value;
		};
	};
}
