#ifndef lambda_calculus_Compiletime_int
#define lambda_calculus_Compiletime_int
#include "propositional_logic.hpp"
#include "lambda_calculus.hpp"
namespace Compiletime_lambda_calculus
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
                    variable< 2 >,
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
        >
    > Next;
    typedef False Zero;
    typedef Next::apply< Zero >::value One;
    typedef Next::apply< One >::value Two;
    typedef Next::apply< Two >::value Three;
    typedef Next::apply< Three >::value Four;
    typedef Next::apply< Four >::value Five;
    typedef Next::apply< Five >::value Six;
    typedef Next::apply< Six >::value Seven;
    typedef Next::apply< Seven >::value Eight;
    typedef Next::apply< Eight >::value Nine;
    typedef Next::apply< Nine >::value Ten;
    typedef Next::apply< Ten >::value Eleven;
    typedef Next::apply< Eleven >::value Twelve;
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
                            variable< 4 >,
                            variable< 2 >
                        >,
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
                    variable< 2 >,
                    application
                    <
                        Plus,
                        variable< 1 >
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
                variable< 1 >,
                variable< 2 >
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
                typedef num value;
            };
        };

        template< typename a >
        struct rem_application
        {
            typedef a value;
        };

        template< typename a, typename b >
        struct rem_application< application< a, b > >
        {
            typedef typename rem_application< typename a::template apply< b >::value >::value value;
        };

        struct accumulate
        {
            static constexpr int value = 0;
            template< typename y >
            struct apply { typedef num< rem_application< y >::value::count + 1 > value; };
            template< int d, typename i >
            struct rebound { typedef accumulate value; };
            template < size_t l, size_t r >
            struct update< l, r > { typedef accumulate type; };
        };
        template < size_t l, size_t r >
        struct update< l, r > { typedef ToInt< x > type; };
        static constexpr int value = rem_application< typename x::template apply< accumulate >::value::template apply< num< 0 > >::value >::value::count;
    };
}
#endif //lambda_calculus_Compiletime_int
