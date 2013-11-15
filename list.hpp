#pragma once
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	struct Nil
	{
		template< typename x >
		struct apply
		{
			typedef True value;
		};
	};
	struct Null
	{
		template< typename x >
		struct apply
		{
			struct inner
			{
				template< typename y >
				struct apply
				{
					struct value
					{
						template< typename z >
						struct apply
						{
							typedef False value;
						};
					};
				};
			};
			typedef typename x::template apply< inner >::value value;
		};
	};
}
