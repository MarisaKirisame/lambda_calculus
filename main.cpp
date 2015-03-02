#include "Compiletime/example.hpp"
#include "Runtime/lambda_calculus.hpp"
int main( )
{
    using Runtime_lambda_calculus::abs;
    using Runtime_lambda_calculus::app;
    using Runtime_lambda_calculus::ind;
    std::shared_ptr< const Runtime_lambda_calculus::expression >
            S( abs( abs( abs( app( app( ind( 3 ), ind( 1 ) ), app( ind( 2 ), ind( 1 ) ) ) ) ) ) ),
            K( abs( abs( ind( 2 ) ) ) ),
            I( abs( ind( 1 ) ) );
    auto SKI = app( app( S, K ), I );
    auto SKISKI = app( SKI, SKI );
    std::cout << static_cast< std::string >(*SKISKI->eval_step( ));
}
