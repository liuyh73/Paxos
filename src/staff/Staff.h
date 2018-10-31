#ifndef PROPOSER_H
#define PROPOSER_H
#include "../result/Result.h"
#include "../general/General.h"
#include "../proposal/Proposal.h"
#include <vector>
#include <iostream>
using namespace std;
//the class Staff the used to propose proposals including attack time.
class Staff{
private:
	//this id is used to distinguish different staff
	int staffId;
	//propose the proposal
	Proposal* proposal;
	//every staff need to deliver the proposal to all generals
	vector<General*>generals;
	//record the half count of generals
	int halfGeneralsCount;
	int staffsCount;
	//record the cycles that the staff has trid to prepare and commit. 
	int cycleCount;
public:
	Staff(int _proposerId, vector<General*>_generals, int _proposersCount, string _attackTime);
	~Staff();
	int getId();
	Proposal *getProposal();
	//in this method, the staff prepare to propose the attack time. 
	bool prepareToCommit();
	//in this method, the staff commit the attack time.
	void commit();
};


#endif