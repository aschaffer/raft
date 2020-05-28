/*
 * Copyright (c) 2020, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

namespace raft {
  
  /// Spectral graph partition
  /** Compute partition for a weighted undirected graph. This
   *  partition attempts to minimize the cost function:
   *    Cost = \sum_i (Edges cut by ith partition)/(Vertices in ith partition)
   *
   *  @param G Weighted graph in CSR format
   *  @param nParts Number of partitions.
   *  @param nEigVecs Number of eigenvectors to compute.
   *  @param maxIter_lanczos Maximum number of Lanczos iterations.
   *  @param restartIter_lanczos Maximum size of Lanczos system before
   *    implicit restart.
   *  @param tol_lanczos Convergence tolerance for Lanczos method.
   *  @param maxIter_kmeans Maximum number of k-means iterations.
   *  @param tol_kmeans Convergence tolerance for k-means algorithm.
   *  @param parts (Output, device memory, n entries) Partition
   *    assignments.
   *  @param iters_lanczos On exit, number of Lanczos iterations
   *    performed.
   *  @param iters_kmeans On exit, number of k-means iterations
   *    performed.
   *  @return error flag.
   */
  template <typename vertex_t,
            typename edge_t,
            typename weight_t,
            template<typename, typename, typename> typename GraphView>
  int partition(GraphView<vertex_t, edge_t, weight_t> const &graph,
                vertex_t nParts,
                vertex_t nEigVecs,
                int maxIter_lanczos,
                int restartIter_lanczos,
                weight_t tol_lanczos,
                int maxIter_kmeans,
                weight_t tol_kmeans,
                vertex_t * __restrict__ parts,
                weight_t *eigVals,
                weight_t *eig_vects);

  /// Compute cost function for partition
  /** This function determines the edges cut by a partition and a cost
   *  function:
   *    Cost = \sum_i (Edges cut by ith partition)/(Vertices in ith partition)
   *  Graph is assumed to be weighted and undirected.
   *
   *  @param G Weighted graph in CSR format
   *  @param nParts Number of partitions.
   *  @param parts (Input, device memory, n entries) Partition
   *    assignments.
   *  @param edgeCut On exit, weight of edges cut by partition.
   *  @param cost On exit, partition cost function.
   *  @return error flag.
   */
  template <typename vertex_t,
            typename edge_t,
            typename weight_t,
            template<typename, typename, typename> typename GraphView>
  int analyzePartition(GraphView<vertex_t, edge_t, weight_t> const &graph,
                       vertex_t nParts,
                       vertex_t const* __restrict__ parts,
                       weight_t& edgeCut, weight_t & cost);

}