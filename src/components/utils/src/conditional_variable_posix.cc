/**
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef MODIFY_FUNCTION_SIGN
#include <global_first.h>
#endif
#include "utils/conditional_variable.h"

#include <errno.h>
#include <time.h>

#include "utils/lock.h"
#include "utils/logger.h"
#ifdef OS_WIN32
#include "utils/date_time.h"
//#pragma warning(disable : 4390)
#elif defined(OS_MAC)
#include "utils/date_time.h"
#else
#endif

namespace {
const long kNanosecondsPerSecond = 1000000000;
const long kMillisecondsPerSecond = 1000;
const long kNanosecondsPerMillisecond = 1000000;
}

namespace sync_primitives {

CREATE_LOGGERPTR_GLOBAL(logger_, "Utils")

ConditionalVariable::ConditionalVariable() {
  pthread_condattr_t attrs;
  int32_t initialized  = pthread_condattr_init(&attrs);
  if (initialized != 0)
    LOG4CXX_ERROR(logger_, "Failed to initialize "
                            "conditional variable attributes");
#ifdef OS_WIN32
//
#elif defined(OS_MAC)
//
#elif defined(OS_ANDROID)
//
#else
  pthread_condattr_setclock(&attrs, CLOCK_MONOTONIC);
#endif
  initialized = pthread_cond_init(&cond_var_, &attrs);
  if (initialized != 0)
    LOG4CXX_ERROR(logger_, "Failed to initialize "
                            "conditional variable");
  int32_t rv = pthread_condattr_destroy(&attrs);
  if (rv != 0)
    LOG4CXX_ERROR(logger_, "Failed to destroy "
                            "conditional variable attributes");
}

ConditionalVariable::~ConditionalVariable() {
  pthread_cond_destroy(&cond_var_);

}

void ConditionalVariable::NotifyOne() {
  int32_t signaled = pthread_cond_signal(&cond_var_);
  if (signaled != 0)
    LOG4CXX_ERROR(logger_, "Failed to signal conditional variable");

}

void ConditionalVariable::Broadcast() {
  int32_t signaled = pthread_cond_broadcast(&cond_var_);
  if (signaled != 0)
    LOG4CXX_ERROR(logger_, "Failed to broadcast conditional variable");

}

void ConditionalVariable::Wait(AutoLock& auto_lock) {
  Lock& lock = auto_lock.GetLock();
  lock.AssertTakenAndMarkFree();
  int32_t wait_status = pthread_cond_wait(&cond_var_,
                                      &lock.mutex_);
  lock.AssertFreeAndMarkTaken();
  if (wait_status != 0)
    LOG4CXX_ERROR(logger_, "Failed to wait for conditional variable");
}

ConditionalVariable::WaitStatus ConditionalVariable::WaitFor(
    AutoLock& auto_lock, int32_t milliseconds){
  struct timespec now;
#ifdef OS_WIN32
  clock_gettime(CLOCK_REALTIME, &now);
#elif defined(OS_MAC)
  clock_gettime(CLOCK_MONOTONIC, &now);
#else
  clock_gettime(CLOCK_MONOTONIC, &now); 
#endif
  timespec wait_interval;
  wait_interval.tv_sec = now.tv_sec +
      (milliseconds / kMillisecondsPerSecond);
  wait_interval.tv_nsec = now.tv_nsec +
      (milliseconds % kMillisecondsPerSecond) * kNanosecondsPerMillisecond;
  wait_interval.tv_sec += wait_interval.tv_nsec / kNanosecondsPerSecond;
  wait_interval.tv_nsec %= kNanosecondsPerSecond;

  Lock& lock = auto_lock.GetLock();
  lock.AssertTakenAndMarkFree();
  int32_t timedwait_status = pthread_cond_timedwait(&cond_var_,
                                                &lock.mutex_,
                                                &wait_interval);
  lock.AssertFreeAndMarkTaken();
  WaitStatus wait_status = kNoTimeout;
  switch(timedwait_status) {
    case 0: {
      wait_status = kNoTimeout;
    } break;
    case EINTR: {
      wait_status = kNoTimeout;
    } break;
    case ETIMEDOUT: {
      wait_status = kTimeout;
    } break;
    default: {
      LOG4CXX_ERROR(logger_, "Failed to timewait for conditional variable");
    }
  }

  return wait_status;
}

} // namespace sync_primitives
