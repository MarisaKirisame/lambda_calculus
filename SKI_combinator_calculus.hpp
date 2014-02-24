#ifndef LAMBDA_CALCULUS_SKI_COMBINATOR_CALCULUS
#define LAMBDA_CALCULUS_SKI_COMBINATOR_CALCULUS
#include "lambda_calculus.hpp"
#include "propositional_logic.hpp"
#include "parser.hpp"
namespace lambda_calculus
{
	namespace SKI_combinator_logic
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
						application
						<
							variable< -3 >,
							variable< -1 >
						>,
						application
						<
							variable< -2 >,
							variable< -1 >
						>
					>
				>
			>
		> S;
		typedef True K;
		typedef abstraction< variable< -1 > > I;
		typedef
		boost::mpl::map
		<
			boost::mpl::pair< boost::mpl::char_< 'S' >, S >,
			boost::mpl::pair< boost::mpl::char_< 'K' >, K >,
			boost::mpl::pair< boost::mpl::char_< 'I' >, I >
		> SKI_map;
		typedef typename parser::parser_generator::apply< SKI_map >::type SKI_parser;
	}
}
#endif //LAMBDA_CALCULUS_SKI_COMBINATOR_CALCULUS
