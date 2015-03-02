#ifndef lambda_calculus_CompileTime_BCKW_SYSTEM
#define lambda_calculus_CompileTime_BCKW_SYSTEM
#include "lambda_calculus.hpp"
#include "SKI_combinator_calculus.hpp"
#include "boost/mpl/char.hpp"
#include "boost/mpl/map.hpp"
#include "parser.hpp"
namespace CompileTime_lambda_calculus
{
    namespace BCKW_combinator_logic
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
                        variable< 3 >,
                        application
                        <
                            variable< 2 >,
                            variable< 1 >
                        >
                    >
                >
            >
        >B;
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
                            variable< 3 >,
                            variable< 1 >
                        >,
                        variable< 2 >
                    >
                >
            >
        > C;
        typedef SKI_combinator_logic::K K;
        typedef
        abstraction
        <
            abstraction
            <
                application
                <
                    application
                    <
                        variable< 2 >,
                        variable< 1 >
                    >,
                    variable< 1 >
                >
            >
        >W;
        typedef
        boost::mpl::map
        <
            boost::mpl::pair< boost::mpl::char_< 'B' >, B >,
            boost::mpl::pair< boost::mpl::char_< 'C' >, C >,
            boost::mpl::pair< boost::mpl::char_< 'K' >, K >,
            boost::mpl::pair< boost::mpl::char_< 'W' >, W >
        > BCKW_map;
        typedef typename parser::parser_generator::apply< BCKW_map >::type BCKW_parser;
    }
}
#endif //lambda_calculus_CompileTime_BCKW_SYSTEM
