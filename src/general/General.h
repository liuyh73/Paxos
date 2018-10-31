#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <iostream>
#include <string>
#include <cstring>
#include "../result/Result.h"
#include "../proposal/Proposal.h"
#include "../proposalStatus/ProposalStatus.h"
using namespace std;

//this is the General class, in which the attack time is decided.
class General{
private:
	//the acceptorStatus represents General’s acceptance of the current attack time proposal.
	//promisedProposal represents the proposal that has been promised.
	//acceptedProposal represents the proposal that has been accepted.
	Status acceptorStatus;
	Proposal *promisedProposal;
	Proposal *acceptedProposal;

public:
	//initial the obj and release the space.
	General();
	~General();

	//this method will return the info whether the proposal has been promised and the promised proposal.
	Result *handlePrepareToCommit(Proposal *proposal);
	//this method will return the info whether the proposal has been accepted and the accepted proposal.
	Result *handleCommit(Proposal *proposal);
};

#endif