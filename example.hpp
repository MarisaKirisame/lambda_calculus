#pragma once
#include <iostream>
using namespace std;
struct True
{
	template< typename x >
	struct apply
	{
		struct value
		{
			template< typename y >
			struct apply
			{
				typedef x value;
			};
		};
	};
};
struct False
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
struct And
{
	template< typename x >
	struct apply
	{
		struct value
		{
			template< typename y >
			struct apply
			{
				typedef typename x::template apply< y >::value::template apply< x >::value value;
			};
		};
	};
};
struct Or
{
	template< typename x >
	struct apply
	{
		struct value
		{
			template< typename y >
			struct apply
			{
				typedef typename x::template apply< x >::value::template apply< y >::value value;
			};
		};
	};
};
struct Not
{
	template< typename x >
	struct apply
	{
		struct value
		{
			template< typename a >
			struct apply
			{
				struct value
				{
					template< typename b >
					struct apply
					{
						typedef typename x::template apply< b >::value::template apply< a >::value value;
					};
				};
			};
		};
	};
};
template< typename t >
struct ToBool;
template< >
struct ToBool< True >
{
	static constexpr bool value = true;
};
template< >
struct ToBool< False >
{
	static constexpr bool value = false;
};
template< typename t >
struct ToBool
{
	static constexpr bool value = ToBool< typename t::template apply< True >::value::template apply< False >::value >::value;
};
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
		struct Nest
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
		typedef typename x::template apply< Nest >::value value;
	};
};
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
struct Int : Next::apply< Int< n - 1 > >::value { };
struct Plus
{
	template< typename a >
	struct apply
	{
		struct Nest
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
		typedef Nest value;
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
template< typename t >
struct ToInt;
template< int t >
struct ToInt< Int< t > >
{
	static constexpr int value = t;
};

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
int example( )
{
	cout << ToBool< Not::apply< True >::value >::value;
	cout << ToBool< Not::apply< Not::apply< True >::value >::value >::value;
	cout << ToBool< And::apply< True >::value::apply< False >::value >::value;
	cout << ToBool< Or::apply< True >::value::apply< False >::value >::value;
	cout << ToBool< First::apply< Pair::apply< True >::value::apply< False >::value >::value >::value;
	cout << ToBool< Null::apply< Pair::apply< True >::value::apply< False >::value >::value >::value;
	cout << ToBool< Null::apply< Nil >::value >::value;
	cout << ToInt< Seven >::value;
	cout << ToInt< Next::apply< Seven >::value >::value;
	cout << ToInt< Plus::apply< Two >::value::apply< Three >::value >::value;
	return 0;
}
