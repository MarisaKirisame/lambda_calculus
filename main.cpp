#include "Compiletime/example.hpp"
#include "Runtime/lambda_calculus.hpp"
#include "Runtime/Compiletime_Runtime.hpp"
#include "cassert"
#define Bridge( Name ) auto Name ## _ = Compiletime_Runtime_converter< Name >( )( )
int main( )
{
    using Runtime_lambda_calculus::abs;
    using Runtime_lambda_calculus::app;
    using Runtime_lambda_calculus::var;
    using Runtime_lambda_calculus::expression;
    using Runtime_lambda_calculus::Compiletime_Runtime_converter;
    using namespace Compiletime_lambda_calculus;
    using namespace SKI_combinator_logic;
    Bridge( Null );
    Bridge( Nil );
    Bridge( Pair );
    Bridge( Y );
    Bridge( First );
    Bridge( Second );
    Bridge( Conditional );
    Bridge( True );
    Bridge( False );
    Bridge( I );
    Bridge( K );
    Bridge( S );
    auto program_inner = abs( abs( abs( app(
        Conditional_,
        app( Null_, var( 1 ) ),
        Nil_,
        app(
          Conditional_,
            app( var( 3 ), app( First_, var( 1 ) ) ),
            app( var( 2 ), app( Second_, var( 1 ) ) ),
            app( Pair_, app( First_, var( 1 ) ), app( var( 2 ), app( Second_, var( 1 ) ) ) ) ) ) ) ) );
    auto list_i = app( Pair_, Nil_, Nil_ );
    auto list_ = app( Pair_, list_i, app( Pair_, Nil_, list_i ) );
    auto program = abs( abs( app( Y_, app( program_inner->eval( ), var( 2 ) ), var( 1 ) ) ) );
    auto current = app( program, Null_, list_ );
    std::cout << static_cast< std::string >(*program) << std::endl;
    std::cout << static_cast< std::string >(*current) << std::endl;
    while ( true )
    {
        current = current->eval_step( );
        std::cout << static_cast< std::string >(*current) << std::endl;
        std::cin.get( );
    }
}
