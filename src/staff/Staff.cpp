#include "Staff.h"
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <unistd.h>
using namespace std;
//this function can ensure to generate an sequence of unique and incremental ids.
//use the staffId to generate proposalId
int generateId(int staffId, int cycleCount, int staffsCount){
	return staffId+cycleCount*staffsCount;
}

Staff::Staff(int _staffId, vector<General*>_generals, int _staffsCount, string _attackTime){
	cycleCount=0;
	staffId=_staffId;
	staffsCount=_staffsCount;
	generals.assign(_generals.begin(), _generals.end());
	halfGeneralsCount=generals.size()/2;

	//define the content of proposal 
	proposal=new Proposal(generateId(staffId, cycleCount, staffsCount), _attackTime);
}

Staff::~Staff(){
	cycleCount=0;
	staffId=0;
	staffsCount=0;
	generals.clear();
	halfGeneralsCount=0;
	delete proposal;
	proposal=nullptr;
}

int Staff::getId(){
	return staffId;
}
Proposal *Staff::getProposal(){
	return proposal;
}

bool Staff::prepareToCommit(){
	int promisedCount=0;
	//this loop will be break if the staff's proposal has been promised by more than 
	//half of generals or there is an accepted proposal.
	while(true){
		//use map to count how many generals has accepted the proposals
		map<Proposal*, int> acceptedProposals;
		promisedCount=0;
		for(auto general:generals){
			Result* result = general->handlePrepareToCommit(proposal);

			//Analog the cost of time when deliver the information
			sleep(rand()%2);

			//if the information was lost, the continue
			if(nullptr == result)
				continue;

			//if the staff's proposal has been promised, the count increases by 1.
			if(result->getPromise())
				promisedCount++;
			else{
				//judge if there is a proposal has been accepted.
				if (result->getStatus() == ACCEPTED){
					acceptedProposals[result->getProposal()]++;
				}
			}
			delete result;
		}

		//if more than half generals has promised the proposal, the loop can break.
		if(promisedCount >= halfGeneralsCount){
			for(auto iter=acceptedProposals.begin(); iter!=acceptedProposals.end(); iter++)
				delete iter->first;
			break;
		}

		//traverse the entire map, try to find a proposal that has been accpted by more than half gengerals.
		for(auto iter=acceptedProposals.begin(); iter!=acceptedProposals.end(); iter++)
			if(iter->second >= halfGeneralsCount){
				std::cout<<"Staff"<<staffId<<": attack time has been determined! ["<<proposal->getAttackTime()<<"]"<<std::endl;
				for(auto iter=acceptedProposals.begin(); iter!=acceptedProposals.end(); iter++)
					delete iter->first;
				return true;
			}

		//update the propsoal's id, then the staff can prepare to commit again.
		proposal->setId(generateId(staffId, cycleCount, staffsCount));
		//find the proposal that in acceptedProposals which has the max id.
		//then the staff use its attackTime, because with our method, the proposal with max id more likely to be accepted.
		if(acceptedProposals.size()>0){
			auto iter=acceptedProposals.begin();
			int maxxId=(iter->first)->getId();
			proposal->setAttackTime((iter->first)->getAttackTime());

			for(; iter!=acceptedProposals.end(); iter++){
				if((iter->first)->getId()>maxxId)
					proposal->setAttackTime((iter->first)->getAttackTime());
			}
		}
		cycleCount++;

		for(auto iter=acceptedProposals.begin(); iter!=acceptedProposals.end(); iter++)
			delete iter->first;
	}
	return false;
}

void Staff::commit(){
	int acceptedCount=0;
	//this loop will be break if there is an accepted proposal.
	while(true){
		//similarly, use map to count how many generals has accepted the proposals
		map<Proposal*, int> acceptedProposals;
		acceptedCount=0;

		for(auto general:generals){
			Result* result = general->handleCommit(proposal);

			//Analog the cost of time when deliver the information
			sleep(rand()%2);
			//if the information was lost, the continue
			if(nullptr == result)
				continue;

			//if the staff's proposal has been accepted, the count increases by 1.
			if(result->getAccepted())
				acceptedCount++;
			else{
				//record the accepted proposal and increase the count.
				acceptedProposals[result->getProposal()]++;
			}
			delete result;
		}
		//if more than half generals has accepted the proposal, the loop can break.
		if(acceptedCount>=halfGeneralsCount){
			std::cout<<"Staff"<<staffId<<": attack time has been determined! ["<<proposal->getAttackTime()<<"]"<<std::endl;
			for(auto iter=acceptedProposals.begin(); iter!=acceptedProposals.end(); iter++)
				delete iter->first;
			return;
		}else{
			//update the propsoal's id, then the staff can commit again.
			proposal->setId(generateId(staffId, cycleCount, staffsCount));
			//find the proposal that in acceptedProposals which has the max id.
			//then the staff use its attackTime, because with our method, the proposal with max id more likely to be accepted.
			if(acceptedProposals.size()>0){
				auto iter=acceptedProposals.begin();
				int maxxId=(iter->first)->getId();
				proposal->setAttackTime((iter->first)->getAttackTime());

				for(; iter!=acceptedProposals.end(); iter++){
					if((iter->first)->getId()>maxxId)
						proposal->setAttackTime((iter->first)->getAttackTime());
				}
			}
			cycleCount++;
			for(auto iter=acceptedProposals.begin(); iter!=acceptedProposals.end(); iter++)
				delete iter->first;
			//if the attack time has not been made, the staff can prepare and commit again. 
			if(prepareToCommit())
				return ;
		}
	}
}