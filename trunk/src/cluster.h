/**
 * cluster.h
 *
 * Author: Damian Eads
 * Date:   September 22, 2007
 *
 * Copyright (c) 2007, Damian Eads
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *   - Redistributions of source code must retain the above
 *     copyright notice, this list of conditions and the
 *     following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer
 *     in the documentation and/or other materials provided with the
 *     distribution.
 *   - Neither the name of the author nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CPY_CLUSTER_H
#define _CPY_CLUSTER_H

#define CPY_LINKAGE_SINGLE 0
#define CPY_LINKAGE_COMPLETE 1
#define CPY_LINKAGE_AVERAGE 2
#define CPY_LINKAGE_CENTROID 3
#define CPY_LINKAGE_MEDIAN 4
#define CPY_LINKAGE_WARD 5
#define CPY_LINKAGE_WEIGHTED 6

typedef struct cnode {
  int n;
  int id;
  double d;
  struct cnode *left;
  struct cnode *right;
} cnode;

typedef struct clnode {
  struct clnode *next;
  struct cnode *val;
} clnode;

typedef struct clist {
  struct clnode *head;
  struct clnode *tail;
} clist;

typedef struct cinfo {
  struct cnode *nodes;
  struct clist *lists;
  int *ind;
  double *dmt;
  double *dm;
  double *buf;
  double **rows;
  double **centroids;
  double *centroidBuffer;
  const double *X;
  int *rowsize;
  int m;
  int n;
  int nid;
} cinfo;

typedef void (distfunc) (cinfo *info, int mini, int minj, int np, int n); 

void dist_to_squareform_from_vector(double *M, const double *v, int n);
void dist_to_vector_from_squareform(const double *M, double *v, int n);

void pdist_euclidean(const double *X, double *dm, int m, int n);
void pdist_seuclidean(const double *X,
		      const double *var, double *dm, int m, int n);
void pdist_hamming(const double *X, double *dm, int m, int n);
void pdist_hamming_bool(const char *X, double *dm, int m, int n);
void pdist_city_block(const double *X, double *dm, int m, int n);
void pdist_cosine(const double *X, double *dm, int m, int n, const double *norms);
void pdist_chebyshev(const double *X, double *dm, int m, int n);
void pdist_jaccard(const double *X, double *dm, int m, int n);
void pdist_jaccard_bool(const char *X, double *dm, int m, int n);
void pdist_minkowski(const double *X, double *dm, int m, int n, double p);

void inconsistency_calculation(const double *Z, double *R, int n, int d);

double dot_product(const double *u, const double *v, int n);

void chopmins(int *ind, int mini, int minj, int np);
void chopmins_ns_i(double *ind, int mini, int np);
void chopmins_ns_ij(double *ind, int mini, int minj, int np);

void dist_single(cinfo *info, int mini, int minj, int np, int n);
void dist_average(cinfo *info, int mini, int minj, int np, int n);
void dist_complete(cinfo *info, int mini, int minj, int np, int n);
void dist_centroid(cinfo *info, int mini, int minj, int np, int n);
void dist_ward(cinfo *info, int mini, int minj, int np, int n);
void dist_weighted(cinfo *info, int mini, int minj, int np, int n);

void linkage(double *dm, double *Z, double *X, int m, int n, int ml, int kc, distfunc dfunc, int method);

void cophenetic_distances(const double *Z, double *d, int n);
void cophenetic_distances_nonrecursive(const double *Z, double *d, int n);
void cpy_to_tree(const double *Z, cnode **tnodes, int n);
void calculate_cluster_sizes(const double *Z, double *CS, int n);

#endif