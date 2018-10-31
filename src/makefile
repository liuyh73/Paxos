GENERAL_DIR=general
PROPOSAL_DIR=proposal
RESULT_DIR=result
STAFF_DIR=staff
PROPOSALSTATUS_DIR=./proposalStatus

#INC_DIR = -I${GENERAL_DIR} \
		  -I${PROPOSAL_DIR} \
		  -I${RESULT_DIR} \
		  -I${STAFF_DIR} \
		  -I${PROPOSALSTATUS_DIR}

SRC = ${wildcard ${GENERAL_DIR}/*.cpp} \
	  ${wildcard ${PROPOSAL_DIR}/*.cpp} \
	  ${wildcard ${RESULT_DIR}/*.cpp} \
	  ${wildcard ${STAFF_DIR}/*.cpp}

OBJ = ${patsubst %.cpp, %.o, ${SRC}}

TARGET=Paxos.exe
FALGS=-lpthread

${TARGET}: ${OBJ} Paxos.o 
	g++ ${OBJ} Paxos.o -o ${TARGET} ${FALGS}
	@echo "Compile done."

${OBJ}: ${SRC} 
	g++ -c $?
	@mv General.o ${GENERAL_DIR}
	@mv Proposal.o ${PROPOSAL_DIR}
	@mv Result.o ${RESULT_DIR}
	@mv Staff.o ${STAFF_DIR}

Paxos.o: Paxos.cpp
	g++ Paxos.cpp -c

clean:
	@rm ${OBJ}
	@rm Paxos.o
	@rm Paxos.exe
	@echo "Clean done."
