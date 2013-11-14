#pragma once
#include <iostream>
using namespace std;
struct True
{
	struct Nest
	{
		template< typename x >
		struct apply
		{
			struct Nest
			{
				template< typename y >
				struct apply
				{
					typedef x value;
				};
			};
		};
	};
};
struct False
{
	struct Nest
	{
		template< typename x >
		struct apply
		{
			struct Nest
			{
				template< typename y >
				struct apply
				{
					typedef y value;
				};
			};
		};
	};
};
struct And
{
	struct Nest
	{
		template< typename x >
		struct apply
		{
			struct Nest
			{
				template< typename y >
				struct apply
				{
					typedef typename x::Nest::template apply< y >::Nest::template apply< x >::value value;
				};
			};
		};
	};
};
struct Or
{
	struct Nest
	{
		template< typename x >
		struct apply
		{
			struct Nest
			{
				template< typename y >
				struct apply
				{
					typedef typename x::Nest::template apply< x >::Nest::template apply< y >::value value;
				};
			};
		};
	};
};
struct Not
{
	struct Nest
	{
		template< typename x >
		struct apply
		{
			struct Reverse
			{
				struct Nest
				{
					template< typename a >
					struct apply
					{
						struct Nest
						{
							template< typename b >
							struct apply
							{
								typedef typename x::Nest::template apply< b >::Nest::template apply< a >::value value;
							};
						};
					};
				};
			};
		typedef Reverse value;
		};
	};
};
template< typename t >
struct IsTrue;
template< >
struct IsTrue< True >
{
	static constexpr bool value = true;
};
template< >
struct IsTrue< False >
{
	static constexpr bool value = false;
};
template< typename t >
struct IsTrue
{
	static constexpr bool value = IsTrue< typename t::Nest::template apply< True >::Nest::template apply< False >::value >::value;
};
int example( )
{
	cout << IsTrue< Not::Nest::apply< True >::value >::value;
	cout << IsTrue< And::Nest::apply< True >::Nest::apply< False >::value >::value;
	cout << IsTrue< Or::Nest::apply< True >::Nest::apply< False >::value >::value;
	return 0;
}

