#pragma once
#include "boost/mpl/count.hpp"
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
		template< typename str, bool e = boost::mpl::empty< str >::value >
		struct is_end;
		template< typename str >
		struct is_end< str, false >
		{ static const bool value = boost::mpl::front< str >::type::value == boost::mpl::char_< ')' >::value; };
		template< typename str >
		struct is_end< str, true > { static const bool value = true; };
		struct parse_error{ };
		template< typename str, bool b = boost::mpl::empty< str >::value >
		struct ignore_invalid;
		template< typename str >
		struct ignore_invalid< str, true > { typedef str type; };
		template< typename str >
		struct ignore_invalid< str, false >
		{
			typedef typename
			boost::mpl::if_c
			<
				boost::mpl::contains< valid_token, typename boost::mpl::front< str >::type >::value,
				str,
				typename ignore_invalid< typename boost::mpl::pop_front< str >::type >::type
			>::type type;
		};
		struct SKI_parser
		{
			template< typename ssstr >
			struct apply
			{
				template< typename str, int i = boost::mpl::front< str >::type::value == '(' ? 1 : 0 >
				struct skip_bracket
				{
					typedef typename boost::mpl::pop_front< str >::type next_str;
					typedef typename boost::mpl::front< next_str >::type front;
					typedef typename skip_bracket< next_str, ( front::value == '(' ? i + 1 : ( front::value == ')' ? i - 1 : i ) ) >::type type;
				};

				template< typename str >
				struct skip_bracket< str, 0 >
				{
					typedef typename boost::mpl::pop_front< str >::type type;
				};
				template< typename str, bool b = boost::mpl::front< str >::type::value == '(' >
				struct parse_single;
				template< typename str >
				struct parse_single< str, false >
				{
					typedef typename boost::mpl::front< str >::type first;
					typedef typename boost::mpl::at< SKI_map, first >::type type;
					typedef typename boost::mpl::pop_front< str >::type next;
				};
				template< typename str >
				struct parse_single< str, true >
				{
					typedef typename SKI_parser::apply< typename boost::mpl::pop_front< str >::type >::value type;
					typedef typename skip_bracket< str >::type next;
				};

				template< typename before, typename str, bool b = is_end< typename ignore_invalid< str >::type >::value >
				struct parse_continue;
				template< typename before, typename str >
				struct parse_continue< before, str, false >
				{
					typedef typename ignore_invalid< str >::type string;
					typedef parse_single< string > parse_next;
					typedef typename
					parse_continue
					<
						typename before::template apply< typename parse_next::type >::value,
						typename parse_next::next
					>::type type;
				};
				template< typename before, typename str >
				struct parse_continue< before, str, true > { typedef before type; };

				typedef typename ignore_invalid< ssstr >::type string;
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
