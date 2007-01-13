

/* Portions copyright (c) 2006 Stanford University and Jack Middleton.
 * Contributors:
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "LBFGSOptimizer.h"

using std::cout;
using std::endl;

namespace SimTK {
const int NUMBER_OF_CORRECTIONS = 5;

     LBFGSOptimizer::LBFGSOptimizer( OptimizerSystem& sys )
        : OptimizerRep( sys ) 
{
          int n,m;
          char buf[1024];


      /* internal flags for LBFGS */
         iprint[0] = iprint[1] = 0; // no output generated
         xtol[0] = 1e-16; // from itk/core/vnl/algo/vnl_lbfgs.cxx

// TODO option for xtol  ??

         if( sys.getNumParameters() < 1 ) {
             char *where = "Optimizer Initialization";
             char *szName= "dimension";
             SimTK_THROW5(SimTK::Exception::ValueOutOfRange, szName, 1,  sys.getNumParameters(), INT_MAX, where); 
         }
         n = sys.getNumParameters();
         m = NUMBER_OF_CORRECTIONS;
     } 


     Real LBFGSOptimizer::optimize(  Vector &results ) {

         int i,info;
         int iflag[1] = {0};
         Real f;
         const OptimizerSystem& sys = getOptimizerSystem();
         int n = sys.getNumParameters();
         int m = NUMBER_OF_CORRECTIONS;

//printf("\n ***** LBFGSOptimizer ***** \n\n");

         iprint[0] = iprint[1] = iprint[2] = diagnosticsLevel; 

          lbfgs_( n, m, &results[0], &f, iprint, &convergenceTolerance,  xtol );

          objectiveFuncWrapper( n, &results[0], true, &f, (void*)this );
          return f;

   }

} // namespace SimTK
