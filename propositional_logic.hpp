#pragma once
namespace lambda_calculus
{
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
}
