#ifndef lambda_calculus_CompileTime_LIST
#define lambda_calculus_CompileTime_LIST
#include "propositional_logic.hpp"
#include "lambda_calculus.hpp"
namespace CompileTime_lambda_calculus
{
    typedef abstraction< True > Nil;
    typedef
    abstraction
    <
        application
        <
            variable< 1 >,
            abstraction
            <
                abstraction< False >
            >
        >
    > Null;
}
#endif //lambda_calculus_CompileTime_LIST
