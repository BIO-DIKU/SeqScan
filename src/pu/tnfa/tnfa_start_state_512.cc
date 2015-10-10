#include "tnfa_start_state_512.h"

TNFAStartState512::TNFAStartState512(uint64_t e[8]) : TNFAState512(0) {
  for (int i = 0; i < 8; i++)
    stateErrorCode_[ i ] = e[ i ];
}

void TNFAStartState512::addEpsilonTransitions(
    bool listNo,
    std::string::const_iterator pos,
    std::vector< TNFAState512 * > stateLists[],
    std::unordered_map<int, int> &matchMap,
    uint32_t listID)
{
  out_->addToList(stateErrorCode_, listNo, pos, stateLists, matchMap, listID);
}

void TNFAStartState512::addOutStates(bool listNo,
                                  std::string::const_iterator pos,
                                  std::vector< TNFAState512 * > stateLists[],
                                  std::unordered_map<int, int> &matchMap,
                                  uint32_t listID)
{
  if (insertions(errorCode_[!listNo]))
    addToList(
        decrementInsertions(errorCode_[!listNo]),
        listNo,
        pos,
        stateLists,
        matchMap,
        listID
    );
}

void TNFAStartState512::display(bool) {
  printf("StartState %p points to %p with error code %llu\n",
    (void *) this, (void *) out_, stateErrorCode_[0]);
}
