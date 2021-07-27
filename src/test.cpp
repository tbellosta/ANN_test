//============================================================
//
//      Type:        ANN_test include file
//
//      Author:      Tommaso Bellosta on 7/27/21.
//                   Dipartimento di Scienze e Tecnologie Aerospaziali
//                   Politecnico di Milano
//                   Via La Masa 34, 20156 Milano, ITALY
//                   e-mail: tommaso.bellosta@polimi.it
//
//      Copyright:   2021, authors above and the ANN_test contributors.
//                   This software is distributed under the MIT license, see LICENSE.txt
//
//============================================================
#include "../include/test.h"

ANNTest::ANNTest() : tree(nullptr), points(nullptr), nPoints(0) {}

ANNTest::~ANNTest() {

    annDeallocPts(points);
    delete tree;
    annClose();

}

void ANNTest::buildTree(const vector<array<double,2>>& pnts) {

    /*-- Copy points --*/

    nPoints = pnts.size();

    points = annAllocPts(nPoints, 2);

    for (int iPoint = 0; iPoint < nPoints; ++iPoint) {
        for (int iDim = 0; iDim < 2; ++iDim) {
            points[iPoint][iDim] = pnts[iPoint][iDim];
        }
    }

    /*-- allocate tree structure --*/
    tree = new ANNkd_tree(points, nPoints, 2);

}


int ANNTest::findNN(const double* pnt) {

    double  eps = 1e-6;         // error bound

    const int k = 1;

//    ANNpoint        queryPt;	// query point
//    ANNidxArray		nnIdx;		// near neighbor indices
//    ANNdistArray	dists;		// near neighbor distances
//
//    queryPt = annAllocPt(2);				// allocate query points
//
//    nnIdx = new ANNidx[k];					// allocate near neigh indices
//    dists = new ANNdist[k];					// allocate near neighbor dists

    double queryPt[2] = {0.0, 0.0};
    double dists[1];
    int    nnIdx[1];


    for (int iDim = 0; iDim < 2; ++iDim) queryPt[iDim] = pnt[iDim];
    // Search
    tree->annkSearch(queryPt, k, nnIdx, dists, eps);

    int out;
    out = nnIdx[0];

    return out;
}

int ANNTest::findNNBruteForce(const double *pnt) {

    int closestID = -1;
    double closestDist = 1e6;

    double distance;

    for (int iPoint = 0; iPoint < nPoints; ++iPoint) {
        distance = dist2(pnt, points[iPoint], 2);
        if (distance <= closestDist) {
            closestDist = distance;
            closestID = iPoint;
        }
    }

    return closestID;

}

