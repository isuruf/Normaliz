/*
 * Normaliz
 * Copyright (C) 2007-2014  Winfried Bruns, Bogdan Ichim, Christof Soeger
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As an exception, when this program is distributed through (i) the App Store
 * by Apple Inc.; (ii) the Mac App Store by Apple Inc.; or (iii) Google Play
 * by Google Inc., then that store may impose any digital rights management,
 * device limits and/or redistribution restrictions that are required by its
 * terms of service.
 */

//---------------------------------------------------------------------------
#ifndef REDUCTION_HPP
#define REDUCTION_HPP
//---------------------------------------------------------------------------
#include <vector>
#include <list>
#include <iostream>
#include <string>

#include "full_cone.h"

//---------------------------------------------------------------------------

namespace libnormaliz {
using std::list;
using std::vector;
using std::string;

template<typename Integer> class CandidateList;
template<typename Integer> class Full_Cone;

template<typename Integer>
class Candidate { // for reduction

friend class CandidateList<Integer>;

public:

vector<Integer> cand;  // the vector
vector<Integer> values; // values under support forms
long sort_deg;  // the sorting degree
bool reducible;    // indicates reducibility

// construct candidate from given components
Candidate(const vector<Integer>& v, const vector<Integer>& val, long sd);

// construct candidate from a vector and the support forms of C
Candidate(const vector<Integer>& v, const Full_Cone<Integer>& C);

}; //end class

template<typename Integer>
bool cand_compare(const Candidate<Integer>& a, const Candidate<Integer>& b);

template<typename Integer>
class CandidateList {

friend class Full_Cone<Integer>;

public:

list <Candidate<Integer> > Candidates;


CandidateList();
// not used at present:
CandidateList(const list<vector<Integer> >& V_List, Full_Cone<Integer>& C);

// Checks for irreducibility
bool is_reducible(const vector<Integer>& v, const vector<Integer>& values, const long sort_deg) const; // basic function
bool is_reducible(Candidate<Integer>& c) const;
// including construction of candidate
bool is_reducible(vector<Integer> v,Candidate<Integer>& cand, const Full_Cone<Integer>& C) const;

// reduction against Reducers and insertion into *this. returns true if inserted
bool reduce_by_and_insert(Candidate<Integer>& cand, const CandidateList<Integer>& Reducers);
// including construction of candidate
bool reduce_by_and_insert(const vector<Integer>& v, Full_Cone<Integer>& C, CandidateList<Integer>& Reducers); 

// reduce *this against Reducers
void reduce_by(CandidateList<Integer>& Reducers);
// reduce *this against itself
void auto_reduce();


void sort_it();
void merge(CandidateList<Integer>& NewCand);
void splice(CandidateList<Integer>& NewCand);
void extract(list<vector<Integer> >& V_List);

}; // end class

template<typename Integer>
class CandidateTable {  // for parallelized reduction with moving of reducer to the front

friend class CandidateList<Integer>;

public:

list <Candidate<Integer>* > CandidatePointers;

CandidateTable(CandidateList<Integer>& CandList);

bool is_reducible(Candidate<Integer>& c);
bool is_reducible(const vector<Integer>& v, const vector<Integer>& values, const long sort_deg);

}; // end class


} // namespace libnormaliz

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
