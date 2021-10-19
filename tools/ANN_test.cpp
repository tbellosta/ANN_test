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
//      Copyright:   2021, Tommaso Bellosta and the ANN_test contributors.
//                   This software is distributed under the MIT license, see LICENSE.txt
//
//============================================================
#include "test.h"
#include <iostream>
#include <omp.h>
#include <assert.h>

int main() {

    /*-- generate point cloud --*/
    const size_t nPoints = 100;
    vector<array<double,2>> pointCloud(nPoints);

    /*-- fill it --*/
    for (int iPoint = 0; iPoint < nPoints; ++iPoint) {
        for (int iDim = 0; iDim < 2; ++iDim) {
            pointCloud[iPoint][iDim] = RNG.selectDouble(-10.0, 10.0);
        }
    }

    /*-- generate query points --*/
    const size_t nQueries = 1000000;
    vector<array<double,2>> queryPoints(nQueries);
    for (int iQuery = 0; iQuery < nQueries; ++iQuery) {
        for (int iDim = 0; iDim < 2; ++iDim) {
            queryPoints[iQuery][iDim] = RNG.selectDouble(-10.0, 10.0);
        }
    }

    /*-- search and check --*/
    ANNTest ANN;
    ANN.buildTree(pointCloud);

    int NNID, BFID;
#pragma omp parallel for private(NNID, BFID)
    for (int iQuery = 0; iQuery < nQueries; ++iQuery) {
        NNID = ANN.findNN(queryPoints[iQuery].data());
        BFID = ANN.findNNBruteForce(queryPoints[iQuery].data());
        assert(NNID == BFID);
    }
    cout << nQueries << "/" << nQueries << " TESTS PASSED!" << endl;
    cout << "Completed using " << omp_get_max_threads() << " threads." << endl;


}
