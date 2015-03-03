#ifndef lambda_calculus_Compiletime_lambda_calculus
#define lambda_calculus_Compiletime_lambda_calculus
#include <type_traits>
namespace Compiletime_lambda_calculus
{
    using namespace std;
    template< typename x, typename y >
    struct application
    {
        template< typename t >
        struct apply
        { typedef typename x::template apply< y >::type::template apply< t >::type type; };
        template< int depth, typename t >
        struct rebound
        { typedef application< typename x::template rebound< depth, t >::type, typename y::template rebound< depth, t >::type > type; };
    };

    template< size_t x >
    struct variable
    {
        template< int depth, typename t >
        struct rebound
        { typedef typename conditional< x == depth, t, variable >::type type; };
    };

    template< typename x >
    struct abstraction
    {
        template< typename t >
        struct apply
        { typedef typename x::template rebound< 1, t >::type type; };
        template< int depth, typename t >
        struct rebound
        { typedef abstraction< typename x::template rebound< depth + 1, t >::type > type; };
    };
}
#endif //lambda_calculus_Compiletime_lambda_calculus
