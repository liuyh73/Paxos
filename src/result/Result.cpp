#include "Result.h"
//realize all the mothod
Result::Result(){
	promise=false;
	accepted=false;
	status=NONE;
	proposal=new Proposal();
}
Result::~Result(){
	promise=false;
	accepted=false;
	status=NONE;
}

void Result::setPromise(bool _promise){
	promise=_promise;
}

bool Result::getPromise(){
	return promise;
}

void Result::setAccepted(bool _accepted){
	accepted=_accepted;
}

bool Result::getAccepted(){
	return accepted;
}

void Result::setProposal(Proposal* _proposal){
	if(_proposal!=nullptr){
		proposal->setId(_proposal->getId());
		proposal->setAttackTime(_proposal->getAttackTime());
	}
}

Proposal* Result::getProposal(){
	return proposal;
}

void Result::setStatus(Status _status){
	status=_status;
}

int Result::getStatus(){
	return status;
}