#ifndef PREPARERESULT_H
#define PREPARERESULT_H

#include "../proposal/Proposal.h"
#include "../proposalStatus/ProposalStatus.h"
//this is the result class that used by general to deliver result to staff
class Result{
private:
	Proposal* proposal;
	bool promise;
	bool accepted;
	Status status;

public:
	Result();
	~Result();

	//accepted represents whether the current proposal has been promised or not.
	void setPromise(bool _promise);
	bool getPromise();

	//accepted represents whether the current proposal has been accepted or not.
	void setAccepted(bool _accepted);
	bool getAccepted();

	//result contains the current promised proposal or accepted proposal
	void setProposal(Proposal* _proposal);
	Proposal* getProposal();
	
	//status denotes the general's status
	void setStatus(Status _status);
	int getStatus();
};

#endif