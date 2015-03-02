#ifndef lambda_calculus_CompileTime_PROPOSITIONAL_LOGIC
#define lambda_calculus_CompileTime_PROPOSITIONAL_LOGIC
#include "lambda_calculus.hpp"
namespace CompileTime_lambda_calculus
{
    typedef
    abstraction
    <
        abstraction
        <
            variable< 2 >
        >
    > True;
    typedef
    abstraction
    <
        abstraction
        <
            variable< 1 >
        >
    > False;
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
                variable< 2 >
            >
        >
    > And;
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
                    variable< 2 >
                >,
                variable< 1 >
            >
        >
    > Or;
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
    > Not;
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
                        variable< 2 >
                    >,
                    variable< 1 >
                >
            >
        >
    > Conditional;
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
        static constexpr bool value =
                ToBool< typename t::template apply< True >::type::template apply< False >::type >::value;
    };
}
#endif //lambda_calculus_CompileTime_PROPOSITIONAL_LOGIC
