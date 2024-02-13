//
// Created by özgür yalçın on 13.02.2024.
//

#include "common.h"

const char* toString(const CharType& value) {
    switch (value) {
        case CharType::ARCHER:
            return "ARCHER";
        case CharType::WARIOR:
            return "WARIOR";
        case CharType::MAGE:
            return "MAGE";
    }

    return "UNKNOWN";
}