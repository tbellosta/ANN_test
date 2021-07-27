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
#ifndef ANN_TEST_TEST_H
#define ANN_TEST_TEST_H

#include "ANN/ANN.h"
#include <vector>
#include  <random>
#include <array>

using namespace std;

class RandomGen {
private:
    std::random_device rd;
    std::mt19937 gen;

public:
    RandomGen() : gen(rd()) {}
//    RandomGen() : gen(1) {}

    template<typename Iter>
    Iter selectRandomly(Iter start, Iter end) {
        return select_randomly(start, end, gen);
    }

    int selectInt(const int& a, const int& b) {
        std::uniform_int_distribution<> dis(a, b);
        return dis(gen);
    }

    double selectDouble(const double& a, const double& b) {
        std::uniform_real_distribution<> dis(a, b);
        return dis(gen);
    }

};

static RandomGen RNG;

class ANNTest {
private:
ANNkd_tree *tree;
ANNpointArray points;
size_t nPoints;

public:

    ANNTest();
    ~ANNTest();

    void buildTree(const vector<array<double, 2>>& pnts);
    int findNN(const double* pnt);
    int findNNBruteForce(const double* pnt);

};

inline double dist2(const double* pnt1, const double* pnt2, const int& dim) {
    double dist2 = 0.0;
    for (int iDim = 0; iDim < dim; ++iDim) {
        dist2 += std::pow(pnt1[iDim] - pnt2[iDim],2);
    }
    return dist2;
}


#endif //ANN_TEST_TEST_H
