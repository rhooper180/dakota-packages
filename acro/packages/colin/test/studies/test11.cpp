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

//
// Solver test w/constraints
//

#include <acro_config.h>

#include <colin/Solver.h>

#include <utilib/stl_auxiliary.h>

using namespace colin;
using namespace std;


#ifdef ACRO_HAVE_TEMPLATES_AS_TEMPLATE_ARGUMENTS
void func(utilib::pvector<double>& vec, UserResponse<utilib::pvector<real > > & response)
#else
void func(utilib::pvector<double>& vec, UserResponse<utilib::BasicArray<real > > & response)
#endif
{
   if (response.evalf_flag)
   {
      double val;
      for (unsigned int i = 0; i < vec.size(); i++)
         val = (i + 1) * vec[i];
      *(response.evalf) = val;
   }

   if (response.evalg_flag)
   {
      for (unsigned int i = 0; i < vec.size(); i++)
         (*(response.evalg))[i] = i + 1;
   }

   if (response.evalcf_flag)
   {
      for (unsigned int i = 0; i < response.evalcf->size(); i++)
      {
         (*(response.evalcf))[i] = vec[i] * vec[i] + i + 1.0;
      }
   }

   if (response.evalcg_flag)
   {
      for (unsigned int i = 0; i < response.evalcf->size(); i++)
      {
         for (unsigned int j = 0; j < vec.size(); j++)
            if (i == j)
               (*(response.evalcg))[i][j] = 2 * vec[i];
            else
               (*(response.evalcg))[i][j] = 0.0;
      }
   }
}



class TestOptSolver : public Solver<utilib::pvector<double> >
{
public:

   void minimize();

   void set_initial_point(utilib::pvector<double>& pt)
   {curr = pt;}

protected:

   void initialize_best_point() {best().point.resize(problem.num_real_params());}
   utilib::pvector<double> curr;
};


void TestOptSolver::minimize()
{
   real tmp;
   problem.EvalF(curr, tmp);
   best().value() = tmp;

#ifdef ACRO_HAVE_TEMPLATES_AS_TEMPLATE_ARGUMENTS
   utilib::pvector<real > g(problem.num_real_params());
   utilib::pvector<real > cf(problem.numConstraints());
   utilib::pvector<utilib::pvector<real > > cg(problem.numConstraints());
#else
   utilib::BasicArray<real > g(problem.num_real_params());
   utilib::BasicArray<real > cf(problem.numConstraints());
   utilib::BasicArray<utilib::BasicArray<real > > cg(problem.numConstraints());
#endif
   for (unsigned int i = 0; i < problem.numConstraints(); i++)
   {
      cg[i].resize(curr.size());
   }

   int j = 0;
   while (best().value() > accuracy)
   {
      for (unsigned int i = 0; i < curr.size(); i++)
         curr[i] -= 0.0001;

      problem.EvalF(curr, tmp);
      best().value() = tmp;
      cout << j << " " << best().value() << " " << curr << endl;

      problem.EvalG(curr, g);
      cout << j << " grad: " << g << endl;

      problem.EvalCF(curr, cf);
      cout << j << " constraints: " << cf << endl;

      problem.EvalCG(curr, cg);
      cout << j << " constraint gradients: " << endl;
      for (unsigned int i = 0; i < problem.numConstraints(); i++)
         cout << " " << i << " " << cg[i] << endl;

      j++;
   }
}



int main()
{
   Problem<utilib::pvector<double> > prob;
   OptSetup(prob, func, "[-10.0,10.0]^3", 1, 2);

   TestOptSolver opt;

   utilib::pvector<double> point(4);
   point << 10.0;

   opt.set_initial_point(point);
   opt.set_problem(prob);
   opt["sufficient_objective_value"] = 37.5;

   opt.reset();
   opt.minimize();

   return 0;
}
