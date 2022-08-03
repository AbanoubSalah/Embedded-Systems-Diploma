/**
 * @file collision_avoidance.h
 * @brief This file is the interface to collision avoidance module
 *
 * @author Abanoub Salah
 * @date August 2, 2022
 *
 */

#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_

#include "state.h"

/* Collision avoidance current state */
extern void (*CollisionAvoidance_state)(void);

/* Collision avoidance states prototypes */
STATE_define(CollisionAvoidance_state_waiting);
STATE_define(CollisionAvoidance_state_driving);

#endif /* COLLISION_AVOIDANCE_H_ */
