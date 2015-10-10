#include "tnfa_start_state_64.h"

TNFAStartState64::TNFAStartState64(uint64_t e) : TNFAState64(0), stateErrorCode_(e) {}

void TNFAStartState64::addEpsilonTransitions(
    bool listNo,
    std::string::const_iterator pos,
    std::vector< TNFAState64 * > stateLists[],
    std::unordered_map<int, int> &matchMap,
    uint32_t listID)
{
  out_->addToList(stateErrorCode_, listNo, pos, stateLists, matchMap, listID);
}

void TNFAStartState64::addOutStates(bool listNo,
                                  std::string::const_iterator pos,
                                  std::vector< TNFAState64 * > stateLists[],
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

void TNFAStartState64::display(bool) {
  printf("StartState %p points to %p with error code %llu\n",
    (void *) this, (void *) out_, stateErrorCode_);
}
