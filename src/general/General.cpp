#include "General.h"
#include <cstdlib>
#include <unistd.h>
//initial the obj
General::General(){
	acceptorStatus=NONE;
	promisedProposal = new Proposal();
	acceptedProposal = new Proposal();
}
//release the space
General::~General(){
	acceptorStatus=NONE;
	delete promisedProposal;
	delete acceptedProposal;
}
//this method handle the staff's proposal which is preparing.
Result* General::handlePrepareToCommit(Proposal* proposal){
	//return the result info.
	Result *result = new Result();

	//Analog information is intercepted.
	if(rand()%4==0){
		delete result;
		return nullptr;
	}

	//use the acceptorStatus to determine the current state
	/*
	 *If acceptorStatus is NONE, this denotes that there is no proposal that has prepared to commit.
	 *If acceptorStatus is PROMISED, this denotes that there has been a promised proposal.
	 *If acceprotStatus is ACCEPTED, this denotes that there has benn a accepted proposal.
	 */
	if(acceptorStatus == NONE){
		//store the info to result.
		result->setStatus(acceptorStatus);
		result->setPromise(true);
		result->setProposal(nullptr);
		//set the acceptorStatus to PROMISED
		acceptorStatus=PROMISED;
		//record the promised proposal.
		promisedProposal->setId(proposal->getId());
		promisedProposal->setAttackTime(proposal->getAttackTime());
		return result;
	}
	if(acceptorStatus == PROMISED){
		//generals only update the promised proposal when the new proposal's id is bigger.
		if(promisedProposal->getId() > proposal->getId()){
			result->setStatus(acceptorStatus);
			result->setPromise(false);
			result->setProposal(promisedProposal);
		}else{
			promisedProposal->setId(proposal->getId());
			promisedProposal->setAttackTime(proposal->getAttackTime());

			result->setStatus(acceptorStatus);
			result->setPromise(true);
			result->setProposal(promisedProposal);
		}
		return result;
	}

	if(acceptorStatus==ACCEPTED){
		//when there is final decision, general update the proposal if only the id has been update.
		if(promisedProposal->getId() < proposal->getId() && promisedProposal->getAttackTime() == proposal->getAttackTime()){
			promisedProposal->setId(proposal->getId());

			result->setStatus(acceptorStatus);
			result->setPromise(true);
			result->setProposal(promisedProposal);
		}
		else{
			result->setStatus(acceptorStatus);
			result->setPromise(false);
			result->setProposal(acceptedProposal);
		}
		return result;
	}

	return nullptr;
}

Result* General::handleCommit(Proposal *proposal){
	Result *result = new Result();

	//Analog information is intercepted.
	if(rand()%4==0){
		delete result;
		return nullptr;
	}

	//now the acceptorStatus can only be equal to PROMISED or ACCEPTED
	if(acceptorStatus==PROMISED){
		//when there is not the accepted proposal, the new committing proposal
		//can be update only its id isn't smaller than promised proposal
		if(proposal->getId() >= promisedProposal->getId()){
			promisedProposal->setId(proposal->getId());
			promisedProposal->setAttackTime(proposal->getAttackTime());

			//set the accepted proposal.
			acceptedProposal->setId(proposal->getId());
			acceptedProposal->setAttackTime(proposal->getAttackTime());
			//set the acceptorStatus to ACCEPTED
			//set the result
			acceptorStatus=ACCEPTED;
			result->setAccepted(true);
			result->setStatus(acceptorStatus);
			result->setProposal(proposal);
		}else{
			result->setAccepted(false);
			result->setStatus(acceptorStatus);
			result->setProposal(proposal);
		}
		return result;
	}

	if(acceptorStatus==ACCEPTED){
		//if the decision has been made, general update the proposal if only the id has been update.
		if(proposal->getId() > acceptedProposal->getId() && proposal->getAttackTime() == acceptedProposal->getAttackTime()){
			acceptedProposal->setId(proposal->getId());
			result->setAccepted(true);
			result->setStatus(acceptorStatus);
			result->setProposal(acceptedProposal);
		}else{
			result->setAccepted(false);
			result->setStatus(acceptorStatus);
			result->setProposal(acceptedProposal);
		}
		return result;
	}
	return nullptr;
}