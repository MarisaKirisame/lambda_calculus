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
    typedef algebraic_data_type< size_t, recursive_indicator, std::tuple< recursive_indicator, recursive_indicator > > exp;
    DECLARE_CONSTRUCTOR( exp, 0, var, T );
    DECLARE_CONSTRUCTOR( exp, 1, abs, T );
    DECLARE_CONSTRUCTOR( exp, 2, app, T );

    template< typename INIT, typename FUNCTION, typename FIRST >
    auto pack_fold_l( const INIT & init, const FUNCTION & function, const FIRST & first ) { return function( init, first ); }

    template< typename INIT, typename FUNCTION, typename FIRST, typename ... REST >
    auto pack_fold_l( const INIT & init, const FUNCTION & function, const FIRST & first, const REST & ... rest )
    { return pack_fold_l( function( init, first ), function, rest ... ); }

    exp update_index( const exp & self, size_t i, size_t current_depth )
    {
        return
            self.match(
                with( var( arg ), [&]( size_t ii ) { return var( ii > current_depth ? ii + i - 1 : ii ); } ),
                with(
                    app( arg, arg ),
                    [&]( const exp & l, const exp & r )
                    { return app( update_index( l, i, current_depth ), update_index( r, i, current_depth ) ); } ),
                with(
                    abs( arg ),
                    [&]( const exp & ex ) { return abs( update_index( ex, i, current_depth + 1 ) ); } ) );
    }

    exp substitute( const exp & self, size_t i, const exp & ex )
    {
        return
            self.match(
                with( var( arg ), [&]( size_t ii ) { return ii == i ? update_index( ex, i, 0 ) : var( ii > i ? ii - 1 : ii ); } ),
                with( app( arg, arg ), [&]( const exp & l, const exp & r ) { return app( substitute( l, i, ex ), substitute( r, i, ex ) ); } ),
                with( abs( arg ), [&]( const exp & l ) { return abs( substitute( l, i + 1, ex ) ); } ) );
    }
    bool closed_expression( const exp & self, size_t current_depth )
    {
        return
            self.match(
                with( var( arg ), [&]( size_t ii ) { return ii <= current_depth; } ),
                with(
                    app( arg, arg ),
                    [&]( const exp & l, const exp & r )
                    { return closed_expression( l, current_depth ) && closed_expression( r, current_depth ); } ),
                with( abs( arg ), [&]( const exp & ex ) { return closed_expression( ex, current_depth + 1 ); } ) );
    }

    exp eval_step( const exp & ex )
    {
        return
            ex.match(
                with( var( arg ), []( size_t ii ) { return var( ii ); } ),
                with( abs( arg ), []( const exp & e ) { return abs( eval_step( e ) ); } ),
                with( app( abs( arg ), arg ), []( const exp & l, const exp & r ) { return substitute( l, 1, r ); } ),
                with( app( arg, arg ), []( const exp & l, const exp & r ) { return app( eval_step( l ), eval_step( r ) ); } ) );
    }

    bool operator == ( const exp & l, const exp & r )
    {
        return
            l.match(
                with(
                    var( arg ),
                    [&]( size_t li )
                    {
                        return
                            r.match(
                                with( var( arg ), [&]( size_t ri ) { return li == ri; } ),
                                with( wildstar, []( ) { return false; } ) );
                    } ),
                with(
                    abs( arg ),
                    [&]( const exp & lexp )
                    {
                        return
                            r.match(
                                with( abs( arg ), [&]( const exp & rexp ) { return lexp == rexp; } ),
                                with( wildstar, []( ) { return false; } ) );
                    } ),
                with(
                    app( arg, arg ),
                    [&]( const exp & llexp, const exp & lrexp )
                    {
                        return
                            r.match(
                                with( app( arg, arg ), [&]( const exp & rlexp, const exp & rrexp ) { return llexp == rlexp && lrexp == rrexp; } ),
                                with( wildstar, []( ) { return false; } ) );
                    } ) );
    }

    std::string show( const exp & ex )
    {
        return
            ex.match(
                with( app( arg, arg ), []( const exp & l, const exp & r ) { return "(" + show( l ) + " " + show( r ) + ")"; } ),
                with( var( arg ), []( size_t i ) { return std::to_string( i ) + " "; } ),
                with( abs( arg ), []( const exp & i ) { return "(\\." + show( i ) + ")"; } ) );
    }

    exp eval( const exp & ex )
    {
        exp ret = eval_step( ex );
        return ret == ex ? ret : eval( ret );
    }
}
#endif
