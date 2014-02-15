#ifndef LAMBDA_CALCULUS_CHURCH_NUMERAL
#define LAMBDA_CALCULUS_CHURCH_NUMERAL
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	namespace church_numeral
	{
		typedef
		abstraction
		<
			abstraction
			<
				abstraction
				<
					application
					<
						variable< -2 >,
						application
						<
							application
							<
								variable< -3 >,
								variable< -2 >
							>,
							variable< -1 >
						>
					>
				>
			>
		> Next;
		typedef False Zero;
		typedef Next::apply< Zero >::type One;
		typedef Next::apply< One >::type Two;
		typedef Next::apply< Two >::type Three;
		typedef Next::apply< Three >::type Four;
		typedef Next::apply< Four >::type Five;
		typedef Next::apply< Five >::type Six;
		typedef Next::apply< Six >::type Seven;
		typedef Next::apply< Seven >::type Eight;
		typedef Next::apply< Eight >::type Nine;
		typedef Next::apply< Nine >::type Ten;
		typedef Next::apply< Ten >::type Eleven;
		typedef Next::apply< Eleven >::type Twelve;
		template< unsigned int i >
		struct Int { typedef typename Next::apply< typename Int< i - 1 >::type >::type type; };
		template< > struct Int< 0 > { typedef Zero type; };
		typedef
		abstraction
		<
			abstraction
			<
				abstraction
				<
					abstraction
					<
						application
						<
							application
							<
								variable< -4 >,
								variable< -2 >
							>,
							application
							<
								application
								<
									variable< -3 >,
									variable< -2 >
								>,
								variable< -1 >
							>
						>
					>
				>
			>
		> Plus;
		typedef
		abstraction
		<
			abstraction
			<
				application
				<
					application
					<
						variable< -2 >,
						application
						<
							Plus,
							variable< -1 >
						>
					>,
					Zero
				>
			>
		> Multiply;
		typedef
		abstraction
		<
			abstraction
			<
				application
				<
					variable< -1 >,
					variable< -2 >
				>
			>
		> Power;
		template< typename x >
		struct ToInt
		{
			template< int n >
			struct num
			{
				static constexpr int count = n;
				template< typename y >
				struct apply
				{
					typedef num type;
				};
			};

			template< typename a >
			struct rem_application { typedef a type; };

			template< typename a, typename b >
			struct rem_application< application< a, b > > { typedef typename rem_application< typename a::template apply< b >::type >::type type; };

			struct accumulate
			{
				static constexpr int value = 0;
				template< typename y >
				struct apply { typedef num< rem_application< y >::type::count + 1 > type; };
				template< int d, typename i >
				struct rebound { typedef accumulate type; };
			};
			static constexpr int value = rem_application< typename x::template apply< accumulate >::type::template apply< num< 0 > >::type >::type::count;
		};
	}
}
#endif //LAMBDA_CALCULUS_CHURCH_NUMERAL
