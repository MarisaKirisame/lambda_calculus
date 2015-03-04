#ifndef lambda_calculus_Compiletime_CHURCH_NUMERAL
#define lambda_calculus_Compiletime_CHURCH_NUMERAL
#include "propositional_logic.hpp"
#include "lambda_calculus.hpp"
namespace Compiletime_lambda_calculus
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
                abstraction
                <
                    application
                    <
                        application
                        <
                            application
                            <
                                variable< 3 >,
                                abstraction
                                <
                                    abstraction
                                    <
                                        application
                                        <
                                            variable< 1 >,
                                            application
                                            <
                                                variable< 2 >,
                                                variable< 4 >
                                            >
                                        >
                                    >
                                >
                            >,
                            abstraction
                            <
                                variable< 2 >
                            >
                        >,
                        abstraction
                        <
                            variable< 1 >
                        >
                    >
                >
            >
        > Before;
        typedef
        abstraction
        <
            abstraction
            <
                application
                <
                    application
                    <
                        variable< 1 >,
                        Before
                    >,
                    variable< 2 >
                >
            >
        > Minus;
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
        typedef
        abstraction
        <
            application
            <
                Not,
                application
                <
                    application
                    <
                        variable< 1 >,
                        application
                        <
                            Or,
                            True
                        >
                    >,
                    False
                >
            >
        > IsZero;
        typedef
        abstraction
        <
            abstraction
            <
                application
                <
                    Not,
                    application
                    <
                        IsZero,
                        application
                        <
                            application
                            <
                                Minus,
                                variable< 2 >
                            >,
                            variable< 1 >
                        >
                    >
                >
            >
        > Larger;
        typedef
        abstraction
        <
            abstraction
            <
                application
                <
                    Not,
                    application
                    <
                        IsZero,
                        application
                        <
                            application
                            <
                                Minus,
                                variable< 1 >
                            >,
                            variable< 2 >
                        >
                    >
                >
            >
        > Smaller;
        typedef
        abstraction
        <
            abstraction
            <
                application
                <
                    application
                    <
                        And,
                        application
                        <
                            Not,
                            application
                            <
                                application
                                <
                                    Larger,
                                    variable< 2 >
                                >,
                                variable< 1 >
                            >
                        >
                    >,
                    application
                    <
                        Not,
                        application
                        <
                            application
                            <
                                Smaller,
                                variable< 2 >
                            >,
                            variable< 1 >
                        >
                    >
                >
            >
        > Equal;
        template< typename x >
        struct ToInt
        {
            template< int n >
            struct num
            {
                static constexpr int count = n;
                template< typename y >
                struct apply
                { typedef num type; };
                template< int depth, typename t >
                struct rebound
                { typedef num< n > type; };
                template< size_t l, size_t r >
                struct update { typedef num type; };
            };

            template< size_t depth, typename t >
            struct rebound { typedef ToInt< typename x::template rebound< depth, t >::type > type; };

            template< typename a >
            struct rem_application { typedef a type; };

            template< typename a, typename b >
            struct rem_application< application< a, b > > { typedef typename rem_application< typename a::template apply< b >::type >::type type; };

            struct accumulate
            {
                static constexpr int value = 0;
                template< typename y >
                struct apply { typedef num< rem_application< y >::type::count + 1 > type; };
                template< size_t d, typename i >
                struct rebound { typedef accumulate type; };
                template< size_t l, size_t r >
                struct update { typedef accumulate type; };
            };
            static constexpr int value = rem_application< typename x::template apply< accumulate >::type::template apply< num< 0 > >::type >::type::count;
        };
    }
}
#endif //lambda_calculus_Compiletime_CHURCH_NUMERAL
