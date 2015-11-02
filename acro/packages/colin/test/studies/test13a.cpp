/*  _________________________________________________________________________
 *
 *  Acro: A Common Repository for Optimizers
 *  Copyright (c) 2008 Sandia Corporation.
 *  This software is distributed under the BSD License.
 *  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
 *  the U.S. Government retains certain rights in this software.
 *  For more information, see the README.txt file in the top Acro directory.
 *  _________________________________________________________________________
 */


#include <acro_config.h>
#ifdef ACRO_HAVE_TEMPLATES_AS_TEMPLATE_ARGUMENTS
#undef ACRO_HAVE_TEMPLATES_AS_TEMPLATE_ARGUMENTS
#endif
#include <colin/OptProblemFrag_Base.h>
#include <colin/AppResponse.h>

using namespace std;
using namespace colin;

int main()
{
   colin::OptProblemFragment_Base< vector<double>, AppResponse<> > foo;


   return 0;
}
