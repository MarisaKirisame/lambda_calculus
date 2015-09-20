#ifndef lambda_calculus_Runtime_lambda_calculus
#define lambda_calculus_Runtime_lambda_calculus
#include <memory>
#include <string>
#include <boost/variant.hpp>
#include <boost/optional/optional.hpp>
#include <utility>
#include <map>
#include <../algebraic_data_type/algebraic_data_type.hpp>
namespace Runtime_lambda_calculus
{
    using namespace algebraic_data_type;
    typedef algebraic_data_type< size_t, recursive_indicator, std::pair< recursive_indicator, recursive_indicator > > exp;
    DECLARE_CONSTRUCTOR( exp, 0, var, T );
    DECLARE_CONSTRUCTOR( exp, 1, abs, T );
    DECLARE_CONSTRUCTOR( exp, 2, app, T );

    template< typename INIT, typename FUNCTION, typename FIRST >
    auto pack_fold_l( const INIT & init, const FUNCTION & function, const FIRST & first ) { return function( init, first ); }

    template< typename INIT, typename FUNCTION, typename FIRST, typename ... REST >
    auto pack_fold_l( const INIT & init, const FUNCTION & function, const FIRST & first, const REST & ... rest )
    { return pack_fold_l( function( init, first ), function, rest ... ); }

    /*struct expression : std::enable_shared_from_this< expression >
    {
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
                std::shared_ptr< const expression > operator( )( const var & i ) const
                { return i.i == this->i ? exp.update_index( this->i, 0 ) : ::Runtime_lambda_calculus::var( ( i.i > this->i ) ? ( i.i - 1 ) : ( i.i ) ); }
            };
            substitute_visitor sv { i, exp };
            auto res = v.apply_visitor( sv );
            return res;
        }
        size_t num_of_abstraction_needed_to_form_closed_expression( size_t current_depth ) const
        {
            struct visitor : boost::static_visitor< size_t >
            {
                size_t current_depth;
                visitor( size_t current_depth ) : current_depth( current_depth ) { }
                size_t operator( )( const abstraction & abs ) const
                { return abs.abs->num_of_abstraction_needed_to_form_closed_expression( current_depth + 1 ); }
                size_t operator( )( const application & app ) const
                {
                    return std::max(
                                app.fst->num_of_abstraction_needed_to_form_closed_expression( current_depth ),
                                app.snd->num_of_abstraction_needed_to_form_closed_expression( current_depth ) );
                }
                size_t operator( )( const var & i ) const
                { return ( i.i > current_depth ) ? ( i.i - current_depth ) : 0; }
            };
            visitor vi { current_depth };
            return v.apply_visitor( vi );
        }
        bool closed_expression( size_t current_depth ) const
        {
            struct closed_expression_visitor : boost::static_visitor< bool >
            {
                size_t current_depth;
                closed_expression_visitor( size_t current_depth ) : current_depth( current_depth ) { }
                bool operator( )( const abstraction & abs ) const
                { return abs.abs->closed_expression( current_depth + 1 ); }
                bool operator( )( const application & app ) const
                { return app.fst->closed_expression( current_depth ) && app.snd->closed_expression( current_depth ); }
                bool operator( )( const var & i ) const
                { return i.i <= current_depth; }
            };
            closed_expression_visitor uiv { current_depth };
            return v.apply_visitor( uiv );
        }
        std::shared_ptr< const expression > update_index( size_t i, size_t current_depth ) const
        {
            struct update_index_visitor : boost::static_visitor< std::shared_ptr< const expression > >
            {
                size_t i;
                size_t current_depth;
                update_index_visitor( size_t i, size_t current_depth ) : i( i ), current_depth( current_depth ) { }
                std::shared_ptr< const expression > operator( )( const abstraction & abs ) const
                { return Runtime_lambda_calculus::abs( abs.abs->update_index( i, current_depth + 1 ) ); }
                std::shared_ptr< const expression > operator( )( const application & app ) const
                { return Runtime_lambda_calculus::app( app.fst->update_index( i, current_depth ), app.snd->update_index( i, current_depth ) ); }
                std::shared_ptr< const expression > operator( )( const var & i ) const
                { return ::Runtime_lambda_calculus::var( ( i.i > current_depth ) ? ( i.i + this->i - 1 ) : i.i ); }
            };
            update_index_visitor uiv { i, current_depth };
            return v.apply_visitor( uiv );
        }
        bool operator < ( const expression & cmp ) const //for sorting
        {
            struct lesser_visitor_out : boost::static_visitor< bool >
            {
                const expression & cmp;
                lesser_visitor_out( const expression & cmp ) : cmp( cmp ) { }
                bool operator( )( const abstraction & abs ) const
                {
                    struct abstraction_lesser_visitor : boost::static_visitor< bool >
                    {
                        const std::shared_ptr< const expression > & abs;
                        abstraction_lesser_visitor( const std::shared_ptr< const expression > & abs ) : abs( abs ) { }
                        bool operator( )( const abstraction & abs ) const { return *this->abs < *abs.abs; }
                        bool operator( )( const application & ) const { return false; }
                        bool operator( )( const var & ) const { return false; }
                    };
                    abstraction_lesser_visitor alv { abs.abs };
                    return cmp.v.apply_visitor( alv );
                }
                bool operator( )( const var & i ) const
                {
                    struct var_lesser_visitor : boost::static_visitor< bool >
                    {
                        size_t i;
                        var_lesser_visitor( size_t i ) : i( i ) { }
                        bool operator( )( const abstraction & ) const { return true; }
                        bool operator( )( const application & ) const { return false; }
                        bool operator( )( const var & i ) const { return this->i < i.i; }
                    };
                    var_lesser_visitor iev { i.i };
                    return cmp.v.apply_visitor( iev );
                }
                bool operator( )( const application & app ) const
                {
                    struct application_lesser_visitor : boost::static_visitor< bool >
                    {
                        const std::shared_ptr< const expression > & fst, snd;
                        application_lesser_visitor( const std::shared_ptr< const expression > & fst, const std::shared_ptr< const expression > & snd ) :
                            fst( fst ), snd( snd ) { }
                        bool operator( )( const abstraction & ) const { return true; }
                        bool operator( )( const application & app ) const { return std::tie( *this->fst, *this->snd ) < std::tie( *app.fst, *app.snd ); }
                        bool operator( )( const var & ) const { return true; }
                    };
                    application_lesser_visitor alv { app.fst, app.snd };
                    return cmp.v.apply_visitor( alv );
                }
            };
            lesser_visitor_out lvo { cmp };
            return v.apply_visitor( lvo );
        }
        boost::optional< abstraction > eval_abstraction( ) const
        {
            struct eval_abstraction_visitor : boost::static_visitor< boost::optional< abstraction > >
            {
                boost::optional< abstraction > operator( )( const abstraction & abs ) const { return abs; }
                boost::optional< abstraction > operator( )( const application & app ) const
                {
                    auto fstabs = app.fst->eval_abstraction( );
                    return fstabs ? fstabs->apply( *app.snd )->eval_abstraction( ) : boost::optional< abstraction >( );
                }
                boost::optional< abstraction >operator( )( const var & ) const { return boost::optional< abstraction >( ); }
            };
            eval_abstraction_visitor eav;
            return v.apply_visitor( eav );
        }
        std::shared_ptr< const expression > eval_step( ) const
        {
            struct eval_step_visitor : boost::static_visitor< std::shared_ptr< const expression > >
            {
                std::shared_ptr< const expression > operator( )( const abstraction & abs ) const
                { return std::make_shared< const expression >( abstraction(abs.abs->eval_step( ) ) ); }
                std::shared_ptr< const expression > operator( )( const application & app ) const
                {
                    auto fstabs = app.fst->eval_abstraction( );
                    return fstabs ?
                                std::make_shared< const expression >( *fstabs->apply( *app.snd->eval_step( ) ) ) :
                                ::Runtime_lambda_calculus::app( app.fst->eval_step( ), app.snd->eval_step( ) );
                }
                std::shared_ptr< const expression > operator( )( const var & i ) const { return std::make_shared< const expression >( i ); }
            };
            eval_step_visitor esv;
            return v.apply_visitor( esv );
        }
        std::shared_ptr< const expression > eval( ) const
        {
            auto ret = eval_step( );
            return *ret == *this ? ret : ret->eval( );
        }
    };*/
}
#endif
