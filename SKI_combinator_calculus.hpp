#pragma once
#include "boost/mpl/at.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/contains.hpp"
#include "boost/mpl/find.hpp"
#include "boost/mpl/set_c.hpp"
#include "boost/mpl/set.hpp"
#include "boost/mpl/empty.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/char.hpp"
#include "boost/mpl/map.hpp"
#include "boost/mpl/pair.hpp"
#include "boost/mpl/string.hpp"
#include "boost/mpl/pop_front.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/switch.hpp"
#include "lambda_calculus.hpp"
#include "propositional_logic.hpp"
namespace lambda_calculus
{
	namespace SKI_combinator_calculus
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
		typedef boost::mpl::set
		<
			boost::mpl::char_< 'S' >,
			boost::mpl::char_< 'K' >,
			boost::mpl::char_< 'I' >,
			boost::mpl::char_< '(' >,
			boost::mpl::char_< ')' >
		> valid_token;
		template< typename str >
		struct is_end
		{ static const bool value = boost::mpl::empty< str >::value || boost::mpl::front< str >::type::value == boost::mpl::char_< ')' >::value; };
		struct parse_error{ };
		template< typename str >
		struct ignore_invalid
		{
			template< typename s, bool b = boost::mpl::empty< str >::value >
			struct recurse;

			template< typename s >
			struct recurse< s, true > { typedef parse_error type; };

			template< typename s >
			struct recurse< s, false >
			{ typedef typename ignore_invalid< typename boost::mpl::pop_front< s >::type >::type type; };

			static_assert( boost::mpl::contains< valid_token, boost::mpl::char_< 'S' > >::value, "" );
			typedef typename
			boost::mpl::if_c
			<
				boost::mpl::empty< str >::value,
				parse_error,
				typename boost::mpl::if_c
				<
					boost::mpl::contains< valid_token, typename boost::mpl::front< str >::type >::value,
					str,
					typename recurse< str >::type
				>::type
			>::type type;
		};
		template< typename str >
		struct parse_single
		{
			typedef typename boost::mpl::front< str >::type first;
			typedef typename
			boost::mpl::if_c
			<
				boost::mpl::contains< valid_token, first >::value,
				typename boost::mpl::at< SKI_map, first >::type,
				parse_error
			>::type type;
			typedef typename
			boost::mpl::if_c
			<
				boost::mpl::contains< valid_token, first >::value,
				typename boost::mpl::pop_front< str >::type,
				parse_error
			>::type next;
		};
		template< typename before, typename str, bool b = is_end< str >::value >
		struct parse_continue;
		template< typename before, typename str >
		struct parse_continue< before, str, false >
		{
			typedef typename ignore_invalid< str >::type string;
			typedef parse_single< string > parse_next;
			typedef typename parse_continue< typename before::template apply< typename parse_next::type >::value, typename parse_next::next >::type type;
		};
		template< typename before, typename str >
		struct parse_continue< before, str, true > { typedef before type; };

		struct SKI_parser
		{
			template< typename str >
			struct apply
			{
				typedef typename ignore_invalid< str >::type string;
				typedef typename
				boost::mpl::if_c
				<
					is_end< string >::value,
					parse_error,
					typename parse_continue< typename parse_single< string >::type, typename parse_single< string >::next >::type
				>::type value;
			};
		};
	}
}
