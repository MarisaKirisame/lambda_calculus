#ifndef lambda_calculus_Compiletime_IOTA
#define lambda_calculus_Compiletime_IOTA
#include "SKI_combinator_calculus.hpp"
#include "parser.hpp"
#include "boost/mpl/map.hpp"
#include "boost/mpl/pair.hpp"
#include "boost/mpl/char.hpp"
#include "lambda_calculus.hpp"
namespace Compiletime_lambda_calculus
{
    namespace Iota_combinator_logic
    {
        typedef
            abstraction
            <
                application
                <
                    application
                    <
                        variable< 1 >,
                        SKI_combinator_logic::S
                    >,
                    SKI_combinator_logic::K
                >
            > U;
        typedef boost::mpl::map< boost::mpl::pair< boost::mpl::char_< 'U' >, U > > Iota_map;
        typedef typename parser::parser_generator::apply< Iota_map >::type Iota_parser;
    }
}
#endif //lambda_calculus_Compiletime_IOTA
