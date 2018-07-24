// global.h -
//
// ##Copyright##
// 
// Copyright 2000-2016 Peter Robinson  (pjr@itee.uq.edu.au)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.00 
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ##Copyright##
//
// $Id: global.h,v 1.6 2006/04/04 02:44:32 qp Exp $

#ifndef	GLOBAL_H
#define	GLOBAL_H

#include "atom_table.h"
#include "objects.h"
#include "code.h"
#include "pred_table.h"
#include "qem_options.h"
#include "scheduler.h"
#include "scheduler_status.h"
#include "signals.h"
#include "thread_options.h"
#include "thread_table.h"


extern AtomTable *atoms;
//extern Object** lib_path;
extern Code *code;
extern IOManager *iom;
extern SocketManager *sockm;
extern PredTab *predicates;
extern QemOptions *qem_options;
extern Scheduler *scheduler;
extern SchedulerStatus *scheduler_status;
extern Signals *signals;
extern ThreadOptions *thread_options;
extern ThreadTable *thread_table;
#ifndef WIN32
extern pthread_t *interrupt_handler_thread;
#endif


#endif	// GLOBAL_H
