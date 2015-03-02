#ifndef lambda_calculus_Compiletime_Y_COMBINATOR
#define lambda_calculus_Compiletime_Y_COMBINATOR
#include "lambda_calculus.hpp"
namespace Compiletime_lambda_calculus
{
    typedef
    abstraction
    <
        application
        <
            abstraction
            <
                application
                <
                    variable< 2 >,
                    application
                    <
                        variable< 1 >,
                        variable< 1 >
                    >
                >
            >,
            abstraction
            <
                application
                <
                    variable< 2 >,
                    application
                    <
                        variable< 1 >,
                        variable< 1 >
                    >
                >
            >
        >
    > Y;
}
#endif //lambda_calculus_Compiletime_Y_COMBINATOR
