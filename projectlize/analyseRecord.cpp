//
// Created by zken on 2024/11/4.
//

#include "analyseRecord.h"

analyseRecord::analyseRecord() {

}

analyseRecord::analyseRecord(stack<int> status, stack<string> characterStatus, queue<string> inputQueueStatus) {
    this->statusStackStatus = util::stackToString(status,1);
    this->characterStackStatus = util::stackToString(characterStatus,1);
    this->inputQueueStatus = util::queueToString(inputQueueStatus);
}

string analyseRecord::getDetails() {
    string detail = to_string(lineId) + "\t" + statusStackStatus + "\t" + characterStackStatus +
                    "\t" + inputQueueStatus + "\t" + action + "\t" + gotoContent;
    return detail;
}
