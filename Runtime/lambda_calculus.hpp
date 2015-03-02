#ifndef lambda_calculus_Runtime_lambda_calculus
#define lambda_calculus_Runtime_lambda_calculus
#include <memory>
#include <string>
#include <boost/variant.hpp>
namespace Runtime_lambda_calculus
{
    struct expression;
    std::shared_ptr< const expression > ind( size_t i );
    std::shared_ptr< const expression > abs( const std::shared_ptr< const expression > & exp );
    std::shared_ptr< const expression > app( const std::shared_ptr< const expression > & fst, const std::shared_ptr< const expression > & snd );
    struct expression : std::enable_shared_from_this< expression >
    {
        struct abstraction
        {
            std::shared_ptr< const expression > abs;
            abstraction( const std::shared_ptr< const expression > & abs ) : abs( abs ) { }
            std::shared_ptr< const expression > apply( const expression & exp ) { return abs->substitute( 1, exp ); }
        };
        struct index
        {
            size_t i;
            index( size_t i ) : i( i ) { }
        };
        struct application
        {
            std::shared_ptr< const expression > fst, snd;
            application( const std::shared_ptr< const expression > & fst, const std::shared_ptr< const expression > & snd ) : fst( fst ), snd( snd ) { }
        };
        boost::variant< abstraction, index, application > v;
        expression( const abstraction & abs ) : v( abs ) { }
        expression( const index & i ) : v( i ) { }
        expression( const application & app ) : v( app ) { }
        operator std::string( ) const
        {
            struct string_visitor : boost::static_visitor< std::string >
            {
                std::string operator( )( const abstraction & abs ) const { return "\\." + static_cast< std::string >(*abs.abs); }
                std::string operator( )( const index & i ) const { return std::to_string( i.i ); }
                std::string operator( )( const application & app ) const
                { return "(" + static_cast< std::string >(*app.fst) + static_cast< std::string >(*app.snd) + ")"; }
            };
            string_visitor sv;
            return v.apply_visitor( sv );
        }
        std::shared_ptr< const expression > substitute( size_t i, const expression & exp ) const
        {
            struct substitute_visitor : boost::static_visitor< std::shared_ptr< const expression > >
            {
                size_t i;
                const expression & exp;
                substitute_visitor( size_t i, const expression & exp ) : i( i ), exp( exp ) { }
                std::shared_ptr< const expression > operator( )( const abstraction & abs ) const
                { return Runtime_lambda_calculus::abs( abs.abs->substitute( i + 1, exp ) ); }
                std::shared_ptr< const expression > operator( )( const application & app ) const
                { return Runtime_lambda_calculus::app( app.fst->substitute( i, exp ), app.snd->substitute( i, exp ) ); }
                std::shared_ptr< const expression > operator( )( const index & i ) const
                { return i.i == this->i ? ind( i.i ) : exp.shared_from_this( ); }
            };
            substitute_visitor sv { i, exp };
            return v.apply_visitor( sv );
        }
        bool operator == ( const expression & cmp ) const //it is impossible to decide semantically, so this decide if two expression are structrually equal
        {
            struct equal_visitor_out : boost::static_visitor< bool >
            {
                const expression & cmp;
                equal_visitor_out( const expression & cmp ) : cmp( cmp ) { }
                bool operator( )( const abstraction & abs ) const
                {
                    struct abstraction_equal_visitor : boost::static_visitor< bool >
                    {
                        const std::shared_ptr< const expression > & abs;
                        abstraction_equal_visitor( const std::shared_ptr< const expression > & abs ) : abs( abs ) { }
                        bool operator( )( const abstraction & abs ) const { return *this->abs == *abs.abs; }
                        bool operator( )( const application & ) const { return false; }
                        bool operator( )( const index & ) const { return false; }
                    };
                    abstraction_equal_visitor aev( abs.abs );
                    return cmp.v.apply_visitor( aev );
                }
                bool operator( )( const index & i ) const
                {
                    struct index_equal_visitor : boost::static_visitor< bool >
                    {
                        size_t i;
                        index_equal_visitor( size_t i ) : i( i ) { }
                        bool operator( )( const abstraction & ) const { return false; }
                        bool operator( )( const application & ) const { return false; }
                        bool operator( )( const index & i ) const { return this->i == i.i; }
                    };
                    index_equal_visitor iev { i.i };
                    return cmp.v.apply_visitor( iev );
                }
                bool operator( )( const application & app ) const
                {
                    struct application_equal_visitor : boost::static_visitor< bool >
                    {
                        const std::shared_ptr< const expression > & fst, snd;
                        application_equal_visitor( const std::shared_ptr< const expression > & fst, const std::shared_ptr< const expression > & snd ) :
                            fst( fst ), snd( snd ) { }
                        bool operator( )( const abstraction & ) const { return false; }
                        bool operator( )( const application & app ) const { return *this->fst == *app.fst && *this->snd == *app.snd; }
                        bool operator( )( const index & ) const { return false; }
                    };
                    application_equal_visitor aev( app.fst, app.snd );
                    return cmp.v.apply_visitor( aev );
                }
            };
            equal_visitor_out evo { cmp };
            return v.apply_visitor( evo );
        }
        bool operator != ( const expression & cmp ) const { return ! (*this == cmp); }
        abstraction eval_abstraction( ) const
        {
            struct eval_abstraction_visitor : boost::static_visitor< abstraction >
            {
                abstraction operator( )( const abstraction & abs ) const { return abs; }
                abstraction operator( )( const application & app ) const { return app.fst->eval_abstraction( ).apply( app )->eval_abstraction( ); }
                std::shared_ptr< const expression > operator( )( const index & ) const { throw std::runtime_error( "unexpected index" ); }
            };
            eval_abstraction_visitor eav;
            return v.apply_visitor( eav );
        }
        std::shared_ptr< const expression > eval_step( ) const
        {
            struct eval_step_visitor : boost::static_visitor< std::shared_ptr< const expression > >
            {
                std::shared_ptr< const expression > operator( )( const abstraction & abs ) const
                { return std::make_shared< const expression >( abs ); }
                std::shared_ptr< const expression > operator( )( const application & app ) const
                { return std::make_shared< const expression >( app.fst->eval_abstraction( ).apply( *app.snd ) ); }
                std::shared_ptr< const expression > operator( )( const index & ) const { throw std::runtime_error( "unexpected index" ); }
            };
            eval_step_visitor esv;
            return v.apply_visitor( esv );
        }
    };
    std::shared_ptr< const expression > ind( size_t i ) { return std::make_shared< expression >( expression::index( i ) ); }
    std::shared_ptr< const expression > abs( const std::shared_ptr< const expression > & exp )
    { return std::make_shared< const expression >( expression::abstraction( exp ) ); }
    std::shared_ptr< const expression > app( const std::shared_ptr< const expression > & fst, const std::shared_ptr< const expression > & snd )
    { return std::make_shared< const expression >( expression::application( fst, snd ) ); }
}
#endif
