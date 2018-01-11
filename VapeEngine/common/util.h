//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_UTIL_H
#define VAPEENGINE_UTIL_H

/*
 * This is Java now!
 *
 * CAUTION: use this as little as you can; dynamic_cast is costly.
 */
template<typename Base, typename T>
inline bool instanceOf(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif //VAPEENGINE_UTIL_H