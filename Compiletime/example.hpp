#ifndef lambda_calculus_Compiletime_EXAMPLE
#define lambda_calculus_Compiletime_EXAMPLE
#include "type_traits"
#include "boost/mpl/same_as.hpp"
#include "boost/mpl/string.hpp"
#include "lambda_calculus.hpp"
#include "propositional_logic.hpp"
#include "pair.hpp"
#include "list.hpp"
#include "church_numeral.hpp"
#include "SKI_combinator_calculus.hpp"
#include "BCKW_system.hpp"
#include "parser.hpp"
#include "Iota.hpp"
#include "Y_combinator.hpp"
#include <iostream>
namespace Compiletime_lambda_calculus
{
    using namespace SKI_combinator_logic;
    using namespace church_numeral;
    static_assert( ToBool< True >::value );
    static_assert( ToBool< Not::apply< True >::type >::value == false );
    static_assert( ToBool< Not::apply< Not::apply< True >::type >::type >::value );
    static_assert( ToBool< True::apply< True >::type::apply< False >::type >::value );
    static_assert( ToBool< And::apply< True >::type::apply< False >::type >::value == false );
    static_assert( ToBool< Or::apply< True >::type::apply< False >::type >::value );
    static_assert( ToBool< First::apply< Pair::apply< True >::type::apply< False >::type >::type >::value );
    static_assert( ToBool< Second::apply< Pair::apply< True >::type::apply< False >::type >::type >::value == false );
    static_assert( ToBool< Null::apply< Pair::apply< True >::type::apply< False >::type >::type >::value == false );
    static_assert( ToBool< Null::apply< Nil >::type >::value );
    static_assert( ToInt< Zero >::value == 0 );
    static_assert( ToInt< One >::value == 1 );
    static_assert( ToInt< Two >::value == 2 );
    static_assert( ToInt< Next::apply< Seven >::type >::value == 8 );
    static_assert( ToInt< Plus::apply< Two >::type::apply< Three >::type >::value == 5 );
    static_assert( ToInt< Multiply::apply< Zero >::type::apply< One >::type >::value == 0 );
    static_assert( ToInt< Multiply::apply< Two >::type::apply< Three >::type >::value == 6 );
    static_assert( ToInt< Power::apply< Two >::type::apply< Three >::type >::value == 8 );
    static_assert( ToBool< Equal::apply< Power::apply< Three >::type::apply< Two >::type >::type::apply< Nine >::type >::value );
    static_assert( ToBool< I::apply< True >::type >::value );
    static_assert( ToBool< K::apply< True >::type::apply< False >::type >::value );
    typedef S::apply< K >::type::apply< S >::type::apply< K >::type SKSK;
    static_assert( ToBool< SKSK >::value );
    static_assert( ToBool< SKI_parser::apply< boost::mpl::string< '(SK)','(I(I',' )) ',' K  ' > >::type >::value );
    static_assert( ToInt< Int< 12 >::type >::value == 12 );
    static_assert( ToBool< BCKW_combinator_logic::BCKW_parser::apply< boost::mpl::string< 'B(B(', 'BW)C', ')(BB',')','KKK' > >::type >::value );
    static_assert( ToBool< Iota_combinator_logic::Iota_parser::apply< boost::mpl::string< '(U(U', '(UU)', ') ) '> >::type >::value );
    static_assert( ToInt< Conditional::apply< False >::type::apply< church_numeral::Int< 12 >::type >::type::apply< church_numeral::Int< 15 >::type >::type >::value == 15 );
    static_assert( ToInt< church_numeral::Before::apply< church_numeral::Eight >::type >::value == 7 );
    static_assert( ! ToBool< church_numeral::IsZero::apply< church_numeral::Eight >::type >::value );
    static_assert( ToBool< church_numeral::IsZero::apply< church_numeral::Zero >::type >::value );
    typedef
    abstraction
    <
        abstraction
        <
            application
            <
                application
                <
                    application
                    <
                        Conditional,
                        application
                        <
                            application
                            <
                                Equal,
                                variable< 1 >
                            >,
                            Four
                        >
                    >,
                    Four
                >,
                application
                <
                    application
                    <
                        Plus,
                        application
                        <
                            variable< 2 >,
                            application
                            <
                                Next,
                                variable< 1 >
                            >
                        >
                    >,
                    variable< 1 >
                >
            >
        >
    >recursive_test;
    static_assert( ToInt< Y::apply< recursive_test >::type::apply< One >::type >::value == 10 );
}
#endif //lambda_calculus_Compiletime_EXAMPLE
