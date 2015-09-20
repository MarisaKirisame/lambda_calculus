#ifndef lambda_calculus_Runtime_Compiletime_Runtime
#define lambda_calculus_Runtime_Compiletime_Runtime
#include "./Runtime/lambda_calculus.hpp"
#include "./Compiletime/lambda_calculus.hpp"
namespace Runtime_lambda_calculus
{
    template< typename type_expression >
    struct Compiletime_Runtime_converter;

    template< typename fst, typename snd >
    struct Compiletime_Runtime_converter< Compiletime_lambda_calculus::application< fst, snd > >
    {
        exp operator ( )( ) const
        { return app< >( Compiletime_Runtime_converter< fst >( )( ), Compiletime_Runtime_converter< snd >( )( ) ); }
    };

    template< typename abst >
    struct Compiletime_Runtime_converter< Compiletime_lambda_calculus::abstraction< abst > >
    {
        exp operator ( )( ) const
        { return abs< >( Compiletime_Runtime_converter< abst >( )( ) ); }
    };

    template< size_t i >
    struct Compiletime_Runtime_converter< Compiletime_lambda_calculus::variable< i > >
    {
        exp operator ( )( ) const
        { return var< >( i ); }
    };
}
#endif //lambda_calculus_Runtime_Compiletime_Runtime
