/*************************************************************************
 * Copyright (c) 2017-2018 by the mfmg authors                           *
 * All rights reserved.                                                  *
 *                                                                       *
 * This file is part of the mfmg libary. mfmg is distributed under a BSD *
 * 3-clause license. For the licensing terms see the LICENSE file in the *
 * top-level directory                                                   *
 *                                                                       *
 * SPDX-License-Identifier: BSD-3-Clause                                 *
 *************************************************************************/

#include <mfmg/common/instantiation.hpp>
#include <mfmg/dealii/dealii_matrix_free_mesh_evaluator.hpp>

namespace mfmg
{
template <int dim>
DealIIMatrixFreeMeshEvaluator<dim>::DealIIMatrixFreeMeshEvaluator(
    dealii::DoFHandler<dim> &dof_handler,
    dealii::AffineConstraints<double> &constraints)
    : DealIIMeshEvaluator<dim>(dof_handler, constraints,
                               "DealIIMatrixFreeMeshEvaluator")
{
}

template <int dim>
std::shared_ptr<dealii::TrilinosWrappers::SparseMatrix>
DealIIMatrixFreeMeshEvaluator<dim>::get_matrix()
{
  if (!_sparse_matrix)
  {
    _sparse_matrix = std::make_shared<dealii::TrilinosWrappers::SparseMatrix>();

    this->evaluate_global(this->get_dof_handler(), this->get_constraints(),
                          *_sparse_matrix);
  }
  return _sparse_matrix;
}
} // namespace mfmg

// Explicit Instantiation
INSTANTIATE_DIM(TUPLE(DealIIMatrixFreeMeshEvaluator))
