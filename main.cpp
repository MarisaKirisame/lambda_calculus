#include "Compiletime/example.hpp"
#include "Runtime/lambda_calculus.hpp"
#include "Runtime/Compiletime_Runtime.hpp"
#include "cassert"
#define Bridge( Name ) exp Name ## _ = Compiletime_Runtime_converter< Name >( )( )
int main( )
{
    using Runtime_lambda_calculus::abs;
    using Runtime_lambda_calculus::app;
    using Runtime_lambda_calculus::var;
    using Runtime_lambda_calculus::exp;
    using Runtime_lambda_calculus::Compiletime_Runtime_converter;
    using namespace Compiletime_lambda_calculus;
    using namespace SKI_combinator_logic;
    //Bridge( Null );
    //Bridge( Nil );
    //Bridge( Pair );
    //Bridge( Y );
    //Bridge( First );
    //Bridge( Second );
    //Bridge( Conditional );
    //Bridge( True );
    //Bridge( False );
    exp in = var< >( 1 );
    exp I_ = abs< >( in );
    //Bridge( I );
    //Bridge( K );
    //Bridge( S );
    /*exp program_inner = abs< >( abs< int >( abs< >( app< >(
        Conditional_,
        app< >( Null_, var< >( 1 ) ),
        Nil_,
        app< >(
          Conditional_,
            app< >( var< >( 3 ), app< >( First_, var< >( 1 ) ) ),
            app< >( var< >( 2 ), app< >( Second_, var< >( 1 ) ) ),
            app< >( Pair_, app< >( First_, var< >( 1 ) ), app< >( var< >( 2 ), app< >( Second_, var< >( 1 ) ) ) ) ) ) ) ) );
    exp list_i = app< >( Pair_, Nil_, Nil_ );
    exp list_ = app< >( Pair_, list_i, app< >( Pair_, Nil_, list_i ) );
    exp program = abs< int >( abs< >( app< >( Y_, app< >( eval( program_inner ), var< >( 2 ) ), var< >( 1 ) ) ) );
    exp current = app< >( program, Null_, list_ );
    std::cout << show( program ) << std::endl;
    std::cout << show( current ) << std::endl;
    while ( true )
    {
        current = eval_step( current );
        std::cout << show( current ) << std::endl;
        std::cin.get( );
    }*/
}
