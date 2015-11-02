// $Id: ExampleLinkedEvaluator.hpp 220 2014-01-02 21:24:59Z tplante $
// $URL: https://software.sandia.gov/svn/hopspack/trunk/examples/linked-evaluator-example/ExampleLinkedEvaluator.hpp $

//@HEADER
// ************************************************************************
// 
//         HOPSPACK: Hybrid Optimization Parallel Search Package
//                 Copyright 2009-2014 Sandia Corporation
// 
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
// 
// This file is part of HOPSPACK.
//
// HOPSPACK is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
//  
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//  
// You should have received a copy of the GNU Lesser General Public
// License along with this library.  If not, see http://www.gnu.org/licenses/.
// 
// Questions? Contact Tammy Kolda (tgkolda@sandia.gov)
//                 or Todd Plantenga (tplante@sandia.gov) 
// 
// ************************************************************************
//@HEADER

/*!
  @file ExampleLinkedEvaluator.hpp
  @brief Declaration for ExampleLinkedEvaluator, subclass of Evaluator.
*/

#ifndef EXAMPLELINKEDEVALUATOR_HPP
#define EXAMPLELINKEDEVALUATOR_HPP

#include "HOPSPACK_common.hpp"
#include "HOPSPACK_Evaluator.hpp"
#include "HOPSPACK_ParameterList.hpp"
#include "HOPSPACK_Vector.hpp"


//----------------------------------------------------------------------
//! Implements HOPSPACK::Evaluator as a linked application.
/*!
 *  This example illustrates one way to link an application directly with
 *  HOPSPACK, instead of accessing it through a system call from HOPSPACK.
 *  Evaluation of the objective function and nonlinear constraints occurs
 *  directly in this class.
 *
 *  To use this class, modify HOPSPACK_EvaluatorFactory to register an
 *  Evaluator Type parameter.
 *
 *  See README_linked_evaluator.txt for more information.
 */
//----------------------------------------------------------------------
class ExampleLinkedEvaluator : public HOPSPACK::Evaluator
{
  public:

    //! Constructor.
    /*!
     *  New evaluator parameters can be defined for this implementation
     *  and passed in the configuration parameters file.
     *
     *  @param[in] cEvalParams  Parameters in the "Evaluator" sublist.
     *                          Parameter value "Evaluator Type" is used
     *                          by HOPSPACK_EvaluatorFactory to find
     *                          and execute this constructor method.
     *  @throws string if parameter error is detected.
     */
    ExampleLinkedEvaluator (const HOPSPACK::ParameterList &  cEvalParams);

    //! Destructor.
    ~ExampleLinkedEvaluator (void);


    //! Evaluate the objective function(s) at a point x.
    /*!
     *  @param[in] nTag   Contains a unique tag for the evaluation which can be
     *                    used to name files, etc.
     *  @param[in] cX     The point at which to evaluate the function(s).
     *  @param[out] cFns  On output, contains a vector of objective function
     *                    values computed at X.  Multiple objectives are allowed.
     *                    If an evaluation failed, return an empty vector or set
     *                    individual elements of the vector to HOPSPACK::dne().
     *  @param[out] sMsg  On output, contains a message about the evaluation;
     *                    typically the word "Success" or an error message.
     */
    void  evalF (const int                 nTag,
                 const HOPSPACK::Vector &  cX,
                       HOPSPACK::Vector &  cFns,
                       string &            sMsg);

    //! Evaluate the objective functions and nonlinear constraints at a point x.
    /*!
     *  @param[in] nTag     Contains a unique tag for the evaluation which can be
     *                      used to name files, etc.
     *  @param[in] cX       The point at which to evaluate the function(s).
     *  @param[out] cFns    On output, contains a vector of objective function
     *                      values computed at X.  Multiple objectives are
     *                      allowed.  If an evaluation failed, return an empty
     *                      vector or set individual function elements of the
     *                      vector to HOPSPACK::dne().
     *  @param[out] cEqs    On output, contains a vector of nonlinear equality
     *                      constraint function values computed at X.  If an
     *                      evaluation failed, return an empty vector or set
     *                      individual elements of the vector to HOPSPACK::dne().
     *  @param[out] cIneqs  On output, contains a vector of nonlinear inequality
     *                      constraint function values computed at X.  If an
     *                      evaluation failed, return an empty vector or set
     *                      individual elements of the vector to HOPSPACK::dne().
     *  @param[out] sMsg    On output, contains a message about the evaluation;
     *                      typically the word "Success" or an error message.
     */
    void  evalFC (const int                 nTag,
                  const HOPSPACK::Vector &  cX,
                        HOPSPACK::Vector &  cFns,
                        HOPSPACK::Vector &  cEqs,
                        HOPSPACK::Vector &  cIneqs,
                        string &            sMsg);

    //! Return the string from parameter 'Evaluator Type'.
    string  getEvaluatorType (void) const;

    //! Print debug information about the Evaluator instance.
    void  printDebugInfo (void) const;

  private:

    //! By design, there is no copy constructor.
    ExampleLinkedEvaluator (const ExampleLinkedEvaluator &);
    //! By design, there is no assignment operator.
    ExampleLinkedEvaluator & operator= (const ExampleLinkedEvaluator &);

    double  evaluateF_ (const HOPSPACK::Vector &  cX) const;
    void    evaluateCIneqs_ (const HOPSPACK::Vector &  cX,
                                   HOPSPACK::Vector &  cIneqs) const;

};

#endif     //-- EXAMPLELINKEDEVALUATOR_HPP
