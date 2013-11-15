#pragma once
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	template< int n >
	struct Int;
	template< >
	struct Int< 0 >
	{
		template< typename x >
		struct apply
		{
			struct value
			{
				template< typename y >
				struct apply
				{
					typedef y value;
				};
			};
		};
	};
	struct Next
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
							typedef typename y::template apply< typename x::template apply< y >::value::template apply< z >::value >::value value;
						};
					};
				};
			};
		};
	};
	template< int n >
	struct Int
	{
		template< typename x >
		struct apply
		{
			typedef typename Next::apply< Int< n - 1 > >::value::template apply< x >::value value;
		};
	};
	struct Plus
	{
		template< typename a >
		struct apply
		{
			struct value
			{
				template< typename b >
				struct apply
				{
					struct value
					{
						template< typename c >
						struct apply
						{
							struct value
							{
								template< typename d >
								struct apply
								{
									typedef typename a::template apply< c >::value::template apply< typename b::template apply< c >::value::template apply< d >::value >::value value;
								};
							};
						};
					};
				};
			};
		};
	};
	struct Multiply
	{
		template< typename x >
		struct apply
		{
			struct value
			{
				template< typename y >
				struct apply
				{
					typedef typename x::template apply< typename Plus::template apply< y >::value >::value::template apply< Int< 0 > >::value value;
				};
			};
		};
	};
	struct Power
	{
		template< typename x >
		struct apply
		{
			struct value
			{
				template< typename y >
				struct apply
				{
					typedef typename y::template apply< x >::value value;
				};
			};
		};
	};
	typedef Int< 0 > Zero;
	typedef Int< 1 > One;
	typedef Int< 2 > Two;
	typedef Int< 3 > Three;
	typedef Int< 4 > Four;
	typedef Int< 5 > Five;
	typedef Int< 6 > Six;
	typedef Int< 7 > Seven;
	typedef Int< 8 > Eight;
	typedef Int< 9 > Nine;
	typedef Int< 10 > Ten;
	typedef Int< 11 > Eleven;
	typedef Int< 12 > Twelve;
	template< typename x >
	struct ToInt
	{
		template< int n >
		struct num
		{
			static constexpr int count = n;
			typedef num value;
		};
		struct accumulate
		{
			template< typename y >
			struct apply
			{
				typedef num< y::count + 1 > value;
			};
		};
		static constexpr int value = x::template apply< accumulate >::value::template apply< num< 0 > >::value::count;
	};
}
