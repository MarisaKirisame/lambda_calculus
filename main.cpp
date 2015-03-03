//#include "Compiletime/example.hpp"
#include "Runtime/lambda_calculus.hpp"
int main( )
{
    using Runtime_lambda_calculus::abs;
    using Runtime_lambda_calculus::app;
    using Runtime_lambda_calculus::ind;
    using Runtime_lambda_calculus::expression;
    std::shared_ptr< const expression >
            S( abs( abs( abs( app( app( ind( 3 ), ind( 1 ) ), app( ind( 2 ), ind( 1 ) ) ) ) ) ) ),
            K( abs( abs( ind( 2 ) ) ) ),
            I( abs( ind( 1 ) ) );
    auto SI = app( S, I );
    auto SII = app( SI, I );
    auto SIISII = app( SII, SII );
    auto KK = app( K, K );
    auto KKK = app( app( K, K ), K );
    auto II = app( I, I );
    auto IK = app( I, K );
    auto current = SIISII;
    while ( true )
    {
        std::cout << static_cast< std::string >(*current) << std::endl;
        current = current->eval_step( );
        std::cin.get( );
    }
}
