// atom_table.h - The atom table is a hash table providing a fast search
//		  through the string table.
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
// $Id: atom_table.h,v 1.10 2006/02/20 03:18:51 qp Exp $

#ifndef ATOM_TABLE_H
#define ATOM_TABLE_H

#include <iostream>
#include <string>


#include "config.h"

#include "area_offsets.h"
#include "defs.h"
#include "hash_table.h"
#include "magic.h"
#include "qem_options.h"
//#include "string_qp.h"
#include "string_table.h"

class Atom;
class Object;

//
// Package up the information that are needed for hashing.
//
class AtomKey
{
private:
  const char *string;
  
public:
  //
  // Assign values.
  //
  AtomKey(const char *s)
    : string(s) { }
  
  //
  // Using the string to hash into the name table.
  //
  AtomLoc hashFn(void) const;

  //
  // The two entries are equal if strings are the same.
  //
  inline bool operator==(const Atom& entry) const;
};



//
// Each entry in the atom table points to the string in the string table and
// hashing is based on the string.
//	Atom Table    String Table 
//
//	|        |     |        |
//	+--------+     +--------+
//	|        |-->  |   h    | 
//	|        |     +--------+
//	|        |     |   e    |
//	+--------+     +--------+
//	|        |     |   l    |
//	               +--------+
//	               |   l    |
//	               +--------+
//	               |   o    |
//	               +--------+
//	               |   \0   |
//	               +--------+
//	               |        |
//
class  AtomTable : public HashTable <Atom, AtomKey>
{
private:
  StringTab stringTable; // Where the strings are stored.
  
  //
  // Calculate the hash value for a given entry.
  //
  AtomLoc hashFunction(const AtomKey key) const
    { return(key.hashFn()); }

  //
  // Return the name of the table.
  //
  virtual const char *getAreaName(void) const
    { return("atom table"); }

public:

  //
  // Pre-assigned atoms.
  // Because these are declared statically, there can only ever be one
  // instance of AtomTable.  
  //
  static Atom *nil;
  static Atom *cons;
  static Atom *comma;
  static Atom *success;
  static Atom *failure;
  
  static Atom *unsure;
  static Atom *colon;
  static Atom *dollar;
  static Atom *at;

  static Atom *obra;
  static Atom *cbra;
  static Atom *spobra;
  static Atom *ospra;
  static Atom *cspra;
  static Atom *semi;
  static Atom *arrow;
  
  static Atom *equal;
  static Atom *is;
  static Atom *nfi;
  static Atom *checkBinder;
  static Atom *delays;
  static Atom *equalVar;
  static Atom *equalObjectVariable;
  static Atom *arrayIP;
  static Atom *cut_atom;
  static Atom *neckcut;
  static Atom *delayneckcut;
  static Atom *psi0_call;
  static Atom *psi1_call;
  static Atom *psi2_call;
  static Atom *psi3_call;
  static Atom *psi4_call;
  static Atom *psi5_call;
  static Atom *psi0_resume;
  static Atom *psi1_resume;
  static Atom *psi2_resume;
  static Atom *psi3_resume;
  static Atom *psi4_resume;
  static Atom *psi5_resume;
  static Atom *psi0_error_handler;
  static Atom *psi1_error_handler;
  static Atom *psi2_error_handler;
  static Atom *psi3_error_handler;
  static Atom *psi4_error_handler;
  static Atom *psi5_error_handler;

  static Atom *unify_ref;
  static Atom *xreg;
  static Atom *yreg;
  static Atom *put;
  static Atom *get;
  static Atom *meta;
  static Atom *variable;
  static Atom *value;
  static Atom *substitution;
  static Atom *empty_substitution;
  static Atom *sub_term;
  static Atom *call_pred;
  static Atom *execute_pred;
  static Atom *ccut;
  static Atom *cneck_cut;
  static Atom *cut_ancestor;
  static Atom *allocate;
  static Atom *deallocate;
  static Atom *do_cleanup;
  static Atom *cproceed;
  static Atom *get_level_ancestor;
  static Atom *get_level;
  static Atom *structure;
  static Atom *structure_frame;
  static Atom *list;
  static Atom *quantifier;
  static Atom *constant;
  static Atom *noarg;
  static Atom *object;
  static Atom *unify;
  static Atom *set;
  static Atom *piarg;
  static Atom *pieq;
  static Atom *psi_life;
  static Atom *cpseudo_instr0;
  static Atom *cpseudo_instr1;
  static Atom *cpseudo_instr2;
  static Atom *cpseudo_instr3;
  static Atom *cpseudo_instr4;
  static Atom *cpseudo_instr5;
  static Atom *start;


  static Atom *maxi;
  static Atom *min;
  static Atom *plus;
  static Atom *minus;
  static Atom *multiply;
  static Atom *divide;
  static Atom *intdivide;
  static Atom *mod;
  static Atom *power;
  static Atom *bitwiseand;
  static Atom *bitwiseor;
  static Atom *shiftl;
  static Atom *shiftr;
  static Atom *bitneg;
  static Atom *lt;
  static Atom *gt;
  static Atom *le;
  static Atom *ge;
  static Atom *pi;
  static Atom *e;
  static Atom *abs;
  static Atom *round;
  static Atom *floor;
  static Atom *truncate;
  static Atom *ceiling;
  static Atom *sqrt;
  static Atom *sin;
  static Atom *cos;
  static Atom *tan;
  static Atom *asin;
  static Atom *acos;
  static Atom *atan;
  static Atom *log;
  static Atom *int64;

  static Atom *block;
  static Atom *poll;

  // Used in thread naming.
  static Atom *anonymous;

  static Atom *ipc_send_options;
  static Atom *tcp_recv_options;
  static Atom *thread_defaults;
  static Atom *thread_wait_conditions;

  static Atom *undefined_predicate;
  static Atom *recoverable;
  static Atom *retry_woken_delays;
  static Atom *exception;
  static Atom *throw_call;
  static Atom *out_of_heap;
  static Atom *call_exception;
  static Atom *default_atom;
  static Atom *qup_shorten;
  static Atom *signal_exception;
  static Atom *query;

  static Atom *debug_write;

  static Atom *stream_user;
  static Atom *stream_stdin;
  static Atom *stream_stdout;
  static Atom *stream_stderr;
  static Atom *stream_user_input;
  static Atom *stream_user_output;
  static Atom *stream_user_error;

  // TCP
  static Atom *inaddr_any;

  static Atom *sock_stream;
  static Atom *sock_dgram;
  static Atom *sock_raw;
  static Atom *ipproto_ip;
  static Atom *ipproto_udp;
  static Atom *ipproto_tcp;
  static Atom *ipproto_icmp;
  static Atom *ipproto_raw;
  static Atom *so_debug;
  static Atom *so_reuseaddr;
  static Atom *so_keepalive;
  static Atom *so_dontroute;
  static Atom *so_broadcast;
  static Atom *so_oobinline;
  static Atom *so_sndbuf;
  static Atom *so_rcvbuf;
  static Atom *so_sndtimeo;
  static Atom *so_rcvtimeo;
  static Atom *so_error;
  static Atom *so_type;
  static Atom *poll_read;
  static Atom *poll_write;

  // Tracing
  static Atom *trace_instr;
  static Atom *trace_backtrack;
  static Atom *trace_env;
  static Atom *trace_choice;
  static Atom *trace_cut;
  static Atom *trace_heap;
  static Atom *trace_regs;
  static Atom *trace_all;

  // Locking
  static Atom *code;
  static Atom *record_db;
  static Atom *a_d_none_;

  AtomTable(word32 TableSize,
	  word32 StringSize,
	  word32 StringBoundary) :
    HashTable <Atom, AtomKey> (TableSize),
    stringTable(StringSize, StringBoundary)
  {
    //
    // Pre-assigned atoms.
    //
    nil = add("[]");
    cons = add(".");
    comma = add(",");
    success = add("true");
    failure = add("fail");
    
    unsure = add("unsure");
    colon = add(":");
    dollar = add("$");
    at = add("@");


    obra = add("(");
    cbra = add(")");
    spobra = add(" (");
    ospra = add("[");
    cspra = add("]");
    semi = add(";");
    arrow = add("->");

    equal = add("=");
    is = add("is");
    nfi = add("not_free_in");
    checkBinder = add("check_binder");
    delays = add("$delayed_problems");
    equalVar = add("$equal_var");
    equalObjectVariable = add("$equal_ObjectVariable");
    arrayIP = add("$array_ip");
    neckcut = add("$$neckcut");
    cut_atom = add("$cut");
    delayneckcut = add("$delayneckcut");
    do_cleanup = add("$do_cleanup");
    psi0_call = add("$psi0_calls$");
    psi1_call = add("$psi1_calls$");
    psi2_call = add("$psi2_calls$");
    psi3_call = add("$psi3_calls$");
    psi4_call = add("$psi4_calls$");
    psi5_call = add("$psi5_calls$");
    psi0_resume = add("$psi0_resume");
    psi1_resume = add("$psi1_resume");
    psi2_resume = add("$psi2_resume");
    psi3_resume = add("$psi3_resume");
    psi4_resume = add("$psi4_resume");
    psi5_resume = add("$psi5_resume");
    psi0_error_handler = add("$psi0_error_handler");
    psi1_error_handler = add("$psi1_error_handler");
    psi2_error_handler = add("$psi2_error_handler");
    psi3_error_handler = add("$psi3_error_handler");
    psi4_error_handler = add("$psi4_error_handler");
    psi5_error_handler = add("$psi5_error_handler");
    
    unify_ref = add("unify_ref");
    xreg = add("$xreg");
    yreg = add("$yreg");
    put = add("put");
    get = add("get");
    meta = add("meta");
    variable = add("variable");
    value = add("value");
    substitution = add("substitution");
    empty_substitution = add("empty_substitution");
    sub_term = add("sub_term");
    call_pred = add("call_predicate");
    execute_pred = add("execute_predicate");
    ccut = add("$$cut$$");
    cneck_cut = add("neck_cut");
    cut_ancestor = add("$$cut_ancestor$$");
    allocate = add("allocate");
    deallocate = add("deallocate");
    cproceed = add("proceed");
    get_level_ancestor = add("$$get_level_ancestor$$");
    get_level = add("$$get_level$$");
    structure = add("structure");
    structure_frame = add("structure_frame");
    list = add("list");
    quantifier = add("quantifier");
    constant = add("constant");
    noarg = add("noarg");
    object = add("object");
    unify = add("unify");
    set = add("set");
    piarg = add("$piarg");
    pieq = add("$pieq");
    psi_life = add("$psi_life");
    cpseudo_instr0 = add("$pseudo_instr0");
    cpseudo_instr1 = add("$pseudo_instr1");
    cpseudo_instr2 = add("$pseudo_instr2");
    cpseudo_instr3 = add("$pseudo_instr3");
    cpseudo_instr4 = add("$pseudo_instr4");
    cpseudo_instr5 = add("$pseudo_instr5");
    start = add("start");

    maxi = add("max");
    min = add("min");
    plus = add("+");
    minus = add("-");
    multiply = add("*");
    divide = add("/");
    intdivide = add("//");
    mod = add("mod");
    power = add("**");
    bitwiseand = add("/\\");
    bitwiseor = add("\\/");
    shiftl = add("<<");
    shiftr = add(">>");
    bitneg = add("\\");
    lt = add("<");
    gt = add(">");
    le = add("=<");
    ge = add(">=");
    pi = add("pi");
    e = add("e");
    abs = add("abs");
    round = add("round");
    floor = add("floor");
    truncate = add("truncate");
    ceiling = add("ceiling");
    sqrt = add("sqrt");
    sin = add("sin");
    cos = add("cos");
    tan = add("tan");
    asin = add("asin");
    acos = add("acos");
    atan = add("atan");
    log = add("log");
    int64 = add("$int64");


    stream_stdin = add("stdin");
    stream_stdout = add("stdout");
    stream_stderr = add("stderr");
    stream_user = add("user");
    stream_user_input = add("user_input");
    stream_user_output = add("user_output");
    stream_user_error = add("user_error");

    block = add("block");
    poll = add("poll");

    anonymous = add("anonymous");

    ipc_send_options = add("$ipc_send_options");
    tcp_recv_options = add("$tcp_recv_options");
    thread_defaults = add("$thread_defaults");
    thread_wait_conditions = add("$thread_wait_conditions");

    undefined_predicate = add("undefined_predicate");
    recoverable = add("recoverable");
    retry_woken_delays = add("retry_woken_delays");
    exception = add("exception");
    throw_call = add("throw");
    out_of_heap = add("out_of_heap");
    call_exception = add("$call_exception");
    default_atom = add("default");
    qup_shorten = add("$qup_shorten");
    signal_exception = add("$signal_exception");
    query = add("$query");

    debug_write = add("$debug_write");

    inaddr_any = add("inaddr_any");
    
    sock_stream = add("sock_stream");
    sock_dgram = add("sock_dgram");
    sock_raw = add("sock_raw");
    ipproto_ip = add("ipproto_ip");
    ipproto_udp = add("ipproto_udp");
    ipproto_tcp = add("ipproto_tcp");
    ipproto_icmp = add("ipproto_icmp");
    ipproto_raw = add("ipproto_raw");
    so_debug = add("so_debug");
    so_reuseaddr = add("so_reuseaddr");
    so_keepalive = add("so_keepalive");
    so_dontroute = add("so_dontroute");
    so_broadcast = add("so_broadcast");
    so_oobinline = add("so_oobinline");
    so_sndbuf = add("so_sndbuf");
    so_rcvbuf = add("so_rcvbuf");
    so_sndtimeo = add("so_sndtimeo");
    so_rcvtimeo = add("so_rcvtimeo");
    so_error = add("so_error");
    so_type = add("so_type");
    poll_read = add("poll_read");
    poll_write = add("poll_write");
    
    trace_instr = add("trace_instr");
    trace_backtrack = add("trace_backtrack");
    trace_env = add("trace_env");
    trace_choice = add("trace_choice");
    trace_cut = add("trace_cut");
    trace_heap = add("trace_heap");
    trace_regs = add("trace_regs");
    trace_all = add("trace_all");

    code = add("code");
    record_db = add("record_db");
    a_d_none_ = add("$none_");
  }
  
  //
  // Check whether the entry is empty or not.
  //
  inline bool isEntryEmpty(const AtomLoc index) const;

  //
  // Get the atom from the offset
  //
  Atom* getAtom(const AtomLoc loc);

  //
  // Look up the entry in the atom table and return it.
  //
  inline AtomLoc lookUp(const char *string);
  //
  // Add a new entry to the atom table.
  //
  Atom *add(const char *string);

  inline Atom *add(const string& s)
    {
      return add(s.c_str());
    }

  bool atomToBool(Object* c);

  //
  // Return the size of the table.
  //
  word32  size(void) const { return(allocatedSize()); }
  
  //
  // Return the string table for inspection.
  //
  const StringTab& getStringTable(void) const { return(stringTable); }
  
  char* getStringTableBase() {return (stringTable.getString(0)); }

  //
  // Save the atom table.
  //
  void save(std::ostream& ostrm) const
    {
      saveTable(ostrm, ATOM_TABLE_MAGIC_NUMBER);
    }
  
  //
  // Restore the atom table.
  //
  void load(std::istream& istrm)
    {
      loadTable(istrm);
    }
  
  //
  // Save the string table.
  //
  void saveStringTable(std::ostream& ostrm) const
    {
      stringTable.save(ostrm);
    }
  
  //
  // Restore the string table.
  //
  void loadStringTable(std::istream& istrm)
    {
      stringTable.load(istrm);
    }

  void shiftStringPtrs(char* old_string_base);

};

#endif // ATOM_TABLE_H


#ifndef ATOM_TABLE_INLINE
#define ATOM_TABLE_INLINE

#include "objects.h"

//
// The two entries are equal if strings are the same.
//
inline bool AtomKey::operator==(const Atom& entry) const
{
  assert(entry.isAtom());
  return streq(string, entry.getStringTablePtr());
}


//
// Check whether the entry is empty or not.
//
inline bool AtomTable::isEntryEmpty(const AtomLoc index) const
{ return(inspectEntry(index).isEmpty()); }

//
// Look up the entry in the atom table and return it.
//
inline AtomLoc AtomTable::lookUp(const char *string)
{
  AtomKey key(string);
  return(lookUpTable(key));
} 

#endif // ATOM_TABLE_INLINE










