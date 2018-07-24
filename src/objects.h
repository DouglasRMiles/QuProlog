// objects.h
//
// A representation of the Prolog-level obejcts for the Qu-Prolog
// Abstract Machine (QuAM). 
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
// $Id: objects.h,v 1.12 2006/01/31 23:17:51 qp Exp $

#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>
#include <strings.h>

//#include "atom_table.h"
#include "debug.h" // Qu-Prolog debug code facilities
#include "defs.h" // Qu-Prolog data type definitions &c.

#include "string_table.h"
#include "truth3.h"

// Dynamic cast doesn't work the way it should.
#define OBJECT_CAST(type, expr) reinterpret_cast<type>(expr)

// Forward references for all the subclasses of Object, inserted so
// that ordering of the subclasses is not important (and also to
// provide a handy reference :-)

class AtomTable;
class Constant; // abstract
class Atom;
class Short;
class Long;
class Double;
class StringObject;
class Reference; // abstract
class Variable;
class ObjectVariable;
class Structure;
class List;	// abstract
class Cons;
class QuantifiedTerm;
class Substitution;
class SubstitutionBlock;

// Garbage collection bit
static const heapobject GC_B    = 0x00000001UL;

//////////////////////////////////////////////////////////////////////
// The Object class specification

class Object
{
  
  // The Heap and Object classes are tightly bound.  
  
  friend class Heap;
  friend class AtomTable;
  
public:
  // Buckybits for the broadest types in the tag
  static const heapobject TypeMask     =  0x000000F0UL;
  static const heapobject TypeVar      =  0x00000000UL;	// variable
  static const heapobject TypeShort    =  0x00000010UL;	// short
  static const heapobject TypeLong     =  0x00000030UL;	// long
  static const heapobject TypeDouble   =  0x00000050UL;	// double
  static const heapobject TypeAtom     =  0x00000040UL;	// atom
  static const heapobject TypeString   =  0x00000020UL;	// string
  static const heapobject TypeStruct   =  0x00000070UL;	// struct
  static const heapobject TypeCons     =  0x00000060UL;	// Cons (list)
  static const heapobject TypeObjVar   =  0x00000080UL;	// object variable
  static const heapobject TypeQuant    =  0x00000090UL;	// quantifier
  static const heapobject TypeSubst    =  0x000000A0UL;	// substitution
  static const heapobject TypeSubBlock =  0x000000B0UL; // substitution block

  // Types for unification switch
  // number = { short, long, double}
  // other = {sub, subblock, obvar, quant, other-var}
  static const heapobject UnifyMask    =  0x0000000EUL;
  static const heapobject UVar         =  0x00000000UL; // variable
  static const heapobject UVarOC       =  0x00000002UL; // var with OC flag set
  static const heapobject UNumber      =  0x00000004UL; // number
  static const heapobject UAtom        =  0x00000006UL; // atom
  static const heapobject UString      =  0x00000008UL; // string
  static const heapobject UStruct      =  0x0000000AUL; // structure
  static const heapobject UCons        =  0x0000000cUL; // cons
  static const heapobject UOther       =  0x0000000EUL; // other

  static const heapobject TypeTagMask  =  0x000000FFUL;
  static const heapobject VarTag       =  GC_B | UVar      | TypeVar;
  static const heapobject VarOCTag     =  GC_B | UVarOC    | TypeVar;
  static const heapobject VarOtherTag  =  GC_B | UOther    | TypeVar;
  static const heapobject ShortTag     =  GC_B | UNumber   | TypeShort;
  static const heapobject LongTag      =  GC_B | UNumber   | TypeLong;
  static const heapobject DoubleTag    =  GC_B | UNumber   | TypeDouble;
  static const heapobject AtomTag      =  GC_B | UAtom     | TypeAtom;
  static const heapobject StringTag    =  GC_B | UString   | TypeString;
  static const heapobject StructTag    =  GC_B | UStruct   | TypeStruct;
  static const heapobject ConsTag      =  GC_B | UCons     | TypeCons;
  static const heapobject ObjVarTag    =  GC_B | UOther    | TypeObjVar;
  static const heapobject QuantTag     =  GC_B | UOther    | TypeQuant;
  static const heapobject SubstTag     =  GC_B | UOther    | TypeSubst;
  static const heapobject SubBlockTag  =  GC_B | UOther    | TypeSubBlock;

  static const heapobject NumberTag        =  0x00000015UL;
  static const heapobject DerefMask        =  0x00000070UL;


  static const heapobject tVar         =  TypeVar >> 4;
  static const heapobject tShort       =  TypeShort >> 4;
  static const heapobject tLong        =  TypeLong >> 4;
  static const heapobject tDouble      =  TypeDouble >> 4;
  static const heapobject tAtom        =  TypeAtom >> 4;
  static const heapobject tString      =  TypeString >> 4;
  static const heapobject tStruct      =  TypeStruct >> 4;
  static const heapobject tCons        =  TypeCons >> 4;
  static const heapobject tObjVar      =  TypeObjVar >> 4;
  static const heapobject tSubst       =  TypeSubst >> 4;
  static const heapobject tSubBlock    =  TypeSubBlock >> 4;
  static const heapobject tQuant       =  TypeQuant >> 4;

protected:			// contents of structure
  heapobject tag;


public:
  // For masking the top bits
  static const heapobject TopMask   =    -256L;          // fff..fff00UL
  static const heapobject TopSBMask =    -4096L;         // fff..ff000UL

  // Special tag for unify_x_ref instruction
  static const heapobject RefTag = 0x000000FEUL;

  inline u_int tTag() const;
  inline heapobject getTag() const;
  inline u_int getType(void) const;

  inline u_int switchOffset() const;
  // Returns the first word of the storage after the tag
  inline heapobject *storage(void);

#ifdef OBJECT_OVERRIDES
  // For mutiterms
  virtual bool OverridesStrictEquals(Object* o2, Thread* ctx, bool &result);
  virtual bool OverridesUnify(Object* o2, Thread* ctx, bool in_quant, bool &result); 
#endif
  
  // Some boolean functions for eliciting the type of Object being
  // pointed to.
  
  inline bool isRefTag(void) const;
  inline bool isVariable(void) const;
  inline bool isVariableExtended(void) const;
  inline bool isNormalVariable(void) const;
  inline bool isFrozenVariable(void) const;
  inline bool isThawedVariable(void) const;
  inline bool isObjectVariable(void) const;
  inline bool isLocalObjectVariable(void) const;
  inline bool isAnyVariable(void) const;
  
  inline bool isStructure(void) const;

  inline bool isList(void) const;	// isCons() || isNil()
  inline bool isCons(void) const;
  inline bool isNil(void) const;	// isAtom() && this == AtomTable::Nil
  inline bool inList(Object*);  

  inline bool isAnyStructure(void) const;
  
  inline bool isQuantifiedTerm(void) const;

  inline bool isConstant(void) const;
  inline bool isNumber(void) const;
  inline bool isInteger(void) const;
  inline bool isAtom(void) const;
  inline bool isString(void) const;
  inline bool isEmptyString(void);
  inline bool isShort(void) const;
  inline bool isLong(void) const;
  inline bool isDouble(void) const;
  inline bool isSubstitution(void) const;
  inline bool isSubstitutionBlock(void) const;
  
  // Returns the value of a Short or Long.
  inline long getInteger(void);
  inline double getDouble(void);

  inline heapobject* last(void);



public:
  // Dummy constructor - needed for atom constructor.
  Object(void) {}

  // Dispatching for the size() message, which returns the size of
  // the Object being pointed to
  size_t size_dispatch(void);
  
#ifndef NDEBUG
public:
  // Testing substitution block lists to see if they are legal
  inline bool isLegalSub(void);
  inline bool hasLegalSub(void);

  // Dispatching for the DEBUG printMe() message, which displays a
  // representation of the Object being pointed to
  inline void printMe_dispatch(AtomTable&, bool all = true);

  bool check_object();

#endif

  //
  // variableDereference() follows the (ob)variable-reference chain from
  // an object -- iteratively, not recursively -- and returns the object
  // at the end of the (ob)variable chain.
  //
  inline Object* variableDereference();
  
  //
  // Check whether the object variable is in the distinctness information list.
  // NOTE:
  //	ObjectVariable should be dereferenced before this function is called.
  //
  bool isObjectVariableInDistinctList(const ObjectVariable *objvar) const;
  
  //
  // Check whether two object variables are distinct. 
  // Return true if object variables are known to be distinct.
  // NOTE:
  //	ObjectVariable1 and ObjectVariable2 should be dereferenced 
  //	before this function is called.
  //
  bool distinctFrom(const Object *objvar) const; 
  
  //
  // The function returns true if the object_variable is distinct from
  // all domains in the i-th to SubSize-th entry of the substitution.
  // 
  bool distinctFromDomains(const SubstitutionBlock *sub_block, size_t i);


  //
  // The substitution is scanned from right to left for the local object 
  // variable on a domain or range place. If the last occurrence of the 
  // local object variable is as a range element, then save the corresponding
  // domain element and the new end of the substitution which 
  // is one where local object variable is found.
  //
  bool containLocalObjectVariable(Object* sub, Object*& domElem, 
				  Object*& newEnd);
  
  inline bool equalConstants(Object* const2);
  inline bool equalUninterp(Object* const2);
  
  //
  // Return the length of the bound variables list.
  //
  size_t boundListLength(void);
  
};


//////////////////////////////////////////////////////////////////////
// The Constant class specification
// (NB. This is intended to be an ``abstract'' class)

class Constant : public Object
{
protected:
  friend class Heap;
  friend class Object;
  friend class AtomTable;

 public:
  // Dummy constructor - needed for atom constructor
  Constant(void):Object() {}

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
  
};

//////////////////////////////////////////////////////////////////////
// The Atom class specification
// (NB. These do not appear on the heap.)

class Atom : public Constant
{
protected:
  // Pointer into the string table for the atom's name
  char* string_table_ptr;

  // Either an Atom * or int, depending on hasAssociatedItem()
  wordptr associatedval;

public:
  // Buckybits 
  static const heapobject AssociatedMask =	0x00000300UL;
  static const heapobject AssociatedNone =	0x00000000UL;
  static const heapobject AssociatedInteger =	0x00000100UL;
  static const heapobject AssociatedAtom =	0x00000200UL;
  
  typedef heapobject AssociatedItem;

public:
  // Constructor - needed to initialize atom table.
  Atom(void):Constant()
    {
      tag = AtomTag;
      string_table_ptr = NULL;
      associatedval = 0;
    }

public:  
  // String related things
  inline void setStringTablePtr(char*);
  inline char* getStringTablePtr(void) const;
  inline char* getName(void) const;

  inline bool isEmpty(void) const;

  inline bool getBool(void) const;

public:
  // Accessors and mutators
  inline bool hasAssociatedItem(void) const;

  inline bool hasAssociatedAtom(void) const;
  inline bool hasAssociatedInteger(void) const;

  inline void associateInteger(const long val);
  inline void associateAtom(Atom *atm);
  inline Atom *getAssociatedAtom(void) const;
  inline long getAssociatedInteger(void) const;


public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Short class specification

class Short : public Constant
{
protected:
  // Value is encoded in tag; no extra elements required
  
public:
  static const heapobject Zero    = ShortTag;
  // Accessors and mutators
  inline long getValue(void) const;
  
public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
  
};

//////////////////////////////////////////////////////////////////////
// The Double class specification

class Double : public Constant
{
public:
  static const size_t DOUBLE_SIZE
    = sizeof(double)/BYTES_PER_WORD;

protected:
  heapobject x[DOUBLE_SIZE];
  
public:
  // Accessor (no mutator)
  inline double getValue(void) const;
  
public:
  static inline size_t size(void);
  inline wordlong hashFn(void) const;
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Long class specification

class Long : public Constant
{
protected:
  // The value of the Long
  wordptr value;
  
public:
  // Accessor (no mutator)
  inline long getValue(void) const;
  
public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

class StringObject : public Object
{
 protected:
  heapobject theChars[1];

 public:
  char* getChars() { return (char*)theChars; }
  inline size_t size(void) const;
  inline wordlong hashFn(void) const;
};

//////////////////////////////////////////////////////////////////////
// The Structure class specification
// (A functor and n arguments.  The functor is argument 0.)

class Structure : public Object 
{
protected:
  // Arity is encoded in the tag
  Object *argument[1]; // arity + 1 arguments (argument[0] is functor)
  
public:
  // Accessor for arity (there is no mutator to avoid realloc() type
  // problems.
  inline size_t getArity(void) const;
  
  // Accessor and mutator for arguments.  Argument 0 is the functor,
  // arguments proper are in the range 1..`arity'.
  inline Object *getArgument(const size_t n) const;
  inline void setArgument(const size_t n, Object * plobj);
  
  // Additional wrappers for argument 0
  inline Object *getFunctor(void) const;
  inline void setFunctor(Object * plobj);
  
public:
  // Note, not static, since the size depends on the number of
  // arguments.
  inline size_t size(void) const;

  // Does the real work of figuring out the size.
  static inline size_t size(size_t arity);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Cons class specification
//

class Cons: public Object
{
protected:
  Object *head;
  Object *tail;

public:
  static const heapobject FlagTypeMask =		0x00000c00UL;

  static const heapobject FlagAnyList =			0x00000000UL;
  static const heapobject FlagObjectVariableList = 	0x00000400UL;
  static const heapobject FlagSubstitutionBlockList =	0x00000800UL;
  static const heapobject FlagDelayedProblemList =	0x00000c00UL;

  static const heapobject FlagInvertibleMask =		0x00000200UL;
  
  static const heapobject FlagNotInvertible =		0x00000000UL;
  static const heapobject FlagInvertible =		0x00000200UL;
  static const u_int TailOffset = 2;

public:
  static inline size_t size(void);
  inline void makeSubstitutionBlockList(void);
  inline void makeObjectVariableList(void);
  inline void makeDelayedProblemList(void);

  inline bool isAnyList(void) const;
  inline bool isSubstitutionBlockList(void) const;
  inline bool isObjectVariableList(void) const;
  inline bool isDelayedProblemList(void) const;

public:
  inline void makeInvertible(void);

  inline bool isInvertible(void) const;

public:
  inline void setHead(Object * const);
  inline Object *getHead(void) const;
  
  inline void setTail(Object * const);
  inline Object *getTail(void) const;
  inline Object **getTailAddress(void);
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The QuantifiedTerm class specification

class QuantifiedTerm : public Object
{
protected:
  Object *quantifier;
  Object *boundvars;
  Object *body;
  
public:
  // Accessors
  inline Object *getQuantifier(void) const;
  inline Object *getBoundVars(void) const; // A list of some sort
  inline Object *getBody(void) const;
  
  // Mutators
  inline void setQuantifier(Object *o);
  inline void setBoundVars(Object *l);
  inline void setBody(Object *o);
  
  
public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Substitution class specification

class Substitution : public Object
{
protected:
  Object *sub_block_list; // A Prolog list of parallel substitutions
  Object *term;

public:
  // Accessors
  inline Object *getSubstitutionBlockList(void) const;
  inline Object *getTerm(void) const;

  // Mutators/
  inline void setSubstitutionBlockList(Object *l);
  inline void setTerm(Object *o);

public:
  static inline size_t size(void);

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The SubstitutionBlock class specification
// (A list of parallel substitutions to be performed on a term)

class SubstitutionBlock: public Object
{  
  friend class Heap;
protected:
  // Size of block is encoded in the tag
  struct {
    ObjectVariable *dom;
    Object *ran;
  } substitution[1];

public:
  // Buckybits
  static const heapobject InvertibleMask =      0x00000200UL;
  static const heapobject FlagInvertible =	0x00000200UL;
  static const heapobject FlagNotInvertible =	0x00000000UL;

  // Accessor type for Invertible
  enum Invertible {
    NotInvertible = 0UL,
    IsInvertible = FlagInvertible
  };

  // Accessors
  inline size_t getSize(void) const;
  inline ObjectVariable *getDomain(const size_t n) const;
  inline Object *getRange(const size_t n) const;

  // Mutators
  inline void decrementSize(void);

  inline void setDomain(const size_t n, Object *dom);
  inline void setRange(const size_t n, Object *ran);
  inline void setSubstitutionPair(const size_t n,
				  Object *dom, Object *ran);

  // Invertibility operations
  inline bool isInvertible(void) const;
  inline void makeInvertible(void);

  // Miscellaneous
  inline bool containsLocal(void) const;


public:
  // Note, not static, as size depends on the size of storage for
  // underlying domain/range pairs.
  inline size_t size(void) const;

  // Does the real work of figuring out the size.
  static inline size_t size(size_t sub_size);

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Reference class specification
// (NB. This is intended to be an ``abstract'' class)

class Reference : public Object
{
protected:
   heapobject info[1];

  // In a Variable that has extra information:
  // info[0] = reference
  // info[1] = name (Atom *)
  // info[2] = delayed problem list (Object *)

  // In an ObjectVariable that has extra information:
  // info[0] = reference
  // info[1] = name (Atom *)
  // info[2] = delayed problem list (Object *)
  // info[3] = distinctness information (Object *)

public:
  static const u_int NameOffset = 2;
  static const u_int DelaysOffset = 3;
  // Buckybits
  static const heapobject FlagExtraMask = 	0x00000F00UL;

  static const heapobject FlagOccurs =		0x00000100UL;
  static const heapobject FlagExtraInfo =	0x00000200UL;
  static const heapobject FlagTemperature =	0x00000400UL;
  static const heapobject FlagCollected =       0x00001000UL;
  static const heapobject FlagPerm =            0x00002000UL;


  // Accessors and mutators
  inline Object *getReference(void) const;
  inline void setReference(Object *plobj);

  inline bool hasExtraInfo(void) const;
  inline void setExtraInfo(void);

  inline Atom *getName(void) const;
  inline heapobject *getNameAddress(void);
  inline void setName(Object*);

  // Delay chains
  inline Object *getDelays(void) const;
  inline heapobject *getDelaysAddress(void);
  inline void setDelays(Object*);



  // Collection operations
  inline bool isCollected(void) const;
  inline void setCollectedFlag(void);
  inline void unsetCollectedFlag(void);

  // Perm vars operations
  inline bool isPerm(void) const;
  inline void setPermFlag(void); 

  inline bool isUnbound(void) const;
};

//////////////////////////////////////////////////////////////////////
// The Variable class specification
// (An Object which is a reference to another Object)

class Variable : public Reference
{
public:
  // No extra functionality required beyond what is inherited from
  // Reference

public:
  // Note, not static, since the size depends on the 
  // possible presence of extra information.
  inline size_t size(void) const;
  
  // Does the real work of figuring out the size.
  static inline size_t size(bool has_extra_info);
  // Temperature operations
  inline void freeze(void);
  inline bool isFrozen(void);
  inline void thaw(void);
  inline bool isThawed(void);

  // OccursCheck operations
  inline bool isOccursChecked(void) const;
  inline void setOccursCheck(void);
  inline void setOccursCheckOther(void);

  inline bool isLifeSet(void) const;
  inline u_int getLife(void) const;
  inline void setLife(u_int); 

  // Copy the tags of another variable (without extra info)
  // to this var (with extra info).

  inline void copyTag(Object*);

  inline heapobject getID(void) const;
  inline void setID(heapobject);
  
#ifdef QP_DEBUG
public:
    inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The ObjectVariable class specification

class ObjectVariable: public Reference
{
public:
  static const u_int DistinctnessOffset = 4;
  static const heapobject FlagLocalMask = 	0x00000800UL;

  static const heapobject FlagLocal =		0x00000800UL;

  // Temperature operations
  inline void freeze(void);
  inline bool isFrozen(void);
  inline void thaw(void);
  inline bool isThawed(void);

  // Accessors and mutators
  inline Object *getDistinctness(void) const;
  inline heapobject *getDistinctnessAddress(void);
  inline void setDistinctness(Object * l);

  inline void setLocal(void);
  inline bool isLocal(void) const;

public:
  // Note, not static, as the size depends on the possible presence of
  // extra information.
  inline size_t size(void) const;

  // Does the real work of figuring out the size.
  static inline size_t size(bool has_extra_info);

  bool isObjectVariableInDomain(SubstitutionBlock *);

  inline void makeLocalObjectVariable(void);

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//
//
// ----------------------------
//  Bodies of inline functions
// ----------------------------
//
//

#endif // OBJECTS_H
#ifndef OBJECTS_H_INLINE // MEGA-KLUDGE!!!!!!
#define OBJECTS_H_INLINE

#include "atom_table.h"

//////////////////////////////////////////////////////////////////////
// Inline functions for the Object class


inline u_int
Object::tTag(void) const
{
  return (tag & TypeMask) >> 4;
}

inline u_int
Object::getType(void) const
{
  return (tag & TypeTagMask);
}

inline heapobject 
Object::getTag(void) const
{
  return tag;
}

inline u_int 
Object::switchOffset() const
{
  switch ((tag & TypeMask) >> 4)
    {
    case tVar:
      return 0;
      break;
    case tShort:
    case tLong:
    case tDouble:
    case tAtom:
    case tString:
      return 5;
      break;
    case tStruct:
      return 3;
      break;
    case tCons:
      return 2;
      break;
    case tObjVar:
      return 1;
      break;
    case tSubst:
      return 6;
      break;
    case tQuant:
      return 4;
      break;
    default:
      assert(false);
      return 0;
      break;
    }
  assert(false);
  return 0;
}

inline heapobject *
Object::storage(void)
{
  return reinterpret_cast<heapobject *>(this) + 1;
}

inline bool Object::isRefTag(void) const
{
  return tag == RefTag;
}

inline bool Object::isVariable(void) const
{
  return (tag & TypeMask) == TypeVar;
}
inline bool Object::isVariableExtended(void) const
{
  return (tag & (TypeMask | Reference::FlagExtraInfo)) == (TypeVar | Reference::FlagExtraInfo);
}


inline bool Object::isFrozenVariable(void) const
{
  return (tag & (TypeMask | Reference::FlagTemperature)) == (TypeVar | Reference::FlagTemperature);
}

inline bool Object::isThawedVariable(void) const
{
  return (tag & (TypeMask | Reference::FlagTemperature)) == TypeVar;
}

inline bool Object::isObjectVariable(void) const
{
  return (tag & TypeMask) == TypeObjVar;
}

inline bool Object::isLocalObjectVariable(void) const
{
  return ((tag & (TypeMask | ObjectVariable::FlagLocalMask))
    == (TypeObjVar | ObjectVariable::FlagLocal));
}

inline bool Object::isAnyVariable(void) const
{
  return isVariable() || isObjectVariable();
}

inline bool Object::isStructure(void) const
{
  return (tag & TypeMask) == TypeStruct;
}

inline bool Object::isCons() const
{
  return (tag & TypeMask) == TypeCons;
}

inline bool Object::isNil(void) const
{
  return this == AtomTable::nil;
}

inline bool Object::isList(void) const
{
  return isCons() || isNil();
}

inline bool Object::isAnyStructure(void) const
{
  return isStructure() || isCons();
}

inline bool Object::isQuantifiedTerm(void) const
{
  return (tag & TypeMask) == TypeQuant;
}

inline bool Object::isConstant(void) const
{
  u_int t = (tag & UnifyMask) >> 1;
  return ((t > 1) && (t < 5));
}

inline bool Object::isShort(void) const
{
  return (tag & TypeMask) == TypeShort;
}

inline bool Object::isString(void) const
{
  return (tag & TypeMask) == TypeString;
}

inline bool Object::isEmptyString(void)
{
  return (this->isString() && 
    (OBJECT_CAST(StringObject*, this)->getChars()[0] == '\0'));
}


inline bool Object::isLong(void) const
{
  return (tag & TypeMask) == TypeLong;
}

inline bool Object::isDouble(void) const
{
  return (tag & TypeMask) == TypeDouble;
}

inline bool Object::isNumber(void) const
{
  return (tag & UnifyMask) == UNumber;
}

inline bool Object::isInteger(void) const
{
  return isShort() || isLong();
}


inline bool Object::isAtom(void) const
{
  return (tag & TypeMask) == TypeAtom;
}

inline bool Object::isSubstitution(void) const
{
  return (tag & TypeMask) == TypeSubst;
}

inline bool Object::isSubstitutionBlock(void) const
{
  return (tag & TypeMask ) == TypeSubBlock;
}

inline heapobject* Object::last(void)
{
  assert(!isNumber());
  assert(size_dispatch() > 1);
  return (reinterpret_cast<heapobject*>(this) + size_dispatch() - 1);
}


#ifdef QP_DEBUG

inline bool Object::isLegalSub(void)
{
   if (isNil())
     {
       return true;
     }
   if (!isCons())
     {
       return false;
     }
   Cons* sub = OBJECT_CAST(Cons*, this);
   if (!sub->isSubstitutionBlockList() || 
       !sub->getTail()->isLegalSub() || !sub->getHead()->isSubstitutionBlock())
     {
       return false;
     }
   SubstitutionBlock* subblock = OBJECT_CAST(SubstitutionBlock*, sub->getHead());
   if (subblock->getSize() == 0)
     {
       return false;
     }
   for (size_t i = 1; i <= subblock->getSize(); i++)
     {
        if (!subblock->getDomain(i)->variableDereference()->isObjectVariable())
         {
           return false;
         }

        if (!subblock->getRange(i)->variableDereference()->hasLegalSub())
         {
           return false;
         }
      }
   return true;
}

inline bool Object::hasLegalSub(void)
{
   if (!isSubstitution())
     {
        return true;
     }
   return (OBJECT_CAST(Substitution*, this)->getSubstitutionBlockList()->isLegalSub());
}
   
// The next best thing to generic dispatching

inline void Object::printMe_dispatch(AtomTable& atoms, bool all)
{
  if (this == NULL)
    {
	    std::cerr << "(undefined)";
      return;
    }
  
  switch (tTag ())
    {
    case tVar:
      OBJECT_CAST(Variable *, this)->printMe(atoms, all);
      break;
    case tShort:
      OBJECT_CAST(Short *, this)->printMe(atoms, all);
      break;
    case tLong:
      OBJECT_CAST(Long *, this)->printMe(atoms, all);
      break;
    case tAtom:
      OBJECT_CAST(Atom *, this)->printMe(atoms, all);
      break;
    case tDouble:
      OBJECT_CAST(Double *, this)->printMe(atoms, all);
      break;
    case tCons:
      OBJECT_CAST(Cons *, this)->printMe(atoms, all);
      break;
    case tStruct:
      OBJECT_CAST(Structure *, this)->printMe(atoms, all);
      break;
    case tSubst:
      OBJECT_CAST(Substitution *, this)->printMe(atoms, all);
      break;
    case tSubBlock:
      OBJECT_CAST(SubstitutionBlock *, this)->printMe(atoms, all);
      break;
    case tObjVar:
      OBJECT_CAST(ObjectVariable *, this)->printMe(atoms, all);
      break;
    case tQuant:
      OBJECT_CAST(QuantifiedTerm *, this)->printMe(atoms, all);
      break;
    default:
      // Not all Tags considered!
      std::cerr << "Bogus type" << std::endl;
      std::cerr << (wordptr)(this) << " -> " << *((heapobject*)(this)) << std::endl;
      assert(false);
    }
}

#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Atom class


inline char* Atom::getStringTablePtr(void) const
{
  return string_table_ptr;
}

inline char* Atom::getName(void) const
{
  return string_table_ptr;
}

inline void Atom::setStringTablePtr(char* stl)
{
  string_table_ptr = stl;
}

inline bool Atom::isEmpty(void) const
{
  return string_table_ptr == NULL;
}

inline bool Atom::getBool(void) const
{
  return this == AtomTable::success;
}

inline bool
Atom::hasAssociatedItem(void) const
{
  return (tag & AssociatedMask) != 0;
}

inline bool
Atom::hasAssociatedAtom(void) const
{
  return (tag & AssociatedMask) == AssociatedAtom;
}

inline bool
Atom::hasAssociatedInteger(void) const
{
  return (tag & AssociatedMask) == AssociatedInteger;
}

inline void Atom::associateInteger(const long val)
{
  tag = (tag & ~AssociatedMask) | AssociatedInteger;
  associatedval = val;
}

inline void Atom::associateAtom(Atom *atm)
{
  tag = (tag & ~AssociatedMask) | AssociatedAtom;
  associatedval = reinterpret_cast<wordptr>(atm);
}

inline Atom *Atom::getAssociatedAtom(void) const
{
  assert(sizeof(void *) == sizeof(heapobject));
  assert(hasAssociatedAtom());

  return reinterpret_cast<Atom *>(associatedval);
}

inline long Atom::getAssociatedInteger (void) const
{
  assert(sizeof(void *) == sizeof(heapobject));
  assert(hasAssociatedInteger());

  return associatedval;
}

inline size_t Atom::size(void)
{
  return sizeof(Atom) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Atom::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << std::hex << (wordptr) this << std::dec << "] Atom: \""
       << this->getName() << "\" ";
  
#ifndef WIN32
  switch (tag & AssociatedMask)
    {
    case AssociatedNone:
	    std::cerr << "(no info)";
      break;
    case AssociatedInteger:
      std::cerr << "int: " << getAssociatedInteger();
      break;
    case AssociatedAtom:
      std::cerr << "atom: [" << std::hex << (wordptr) getAssociatedAtom() << std::dec << "]";
      break;
    }
#endif
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Short class

inline long Short::getValue(void) const
{
  // N.B. The alternative of using >> 8 is apparently not portable
  // in the case of signed quantities.
  return (long)((long)(tag & TopMask) / 256);
}

inline size_t Short::size(void)
{
  return sizeof(Short) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Short::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << std::hex << (wordptr) this 
		  << std::dec << "] Short: \""
		  << getValue() << "\" ";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Double class
inline double Double::getValue(void) const
{
  double res = *((double*)x);
  return res;
}

#ifdef QP_DEBUG
inline void Double::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << hex << (wordptr) this << dec << "] Double: \""
       << getValue() << "\" ";
}
#endif

inline size_t Double::size(void) 
{
  return sizeof(Double) / BYTES_PER_WORD;
}
inline wordlong Double::hashFn(void) const
{
  u_char	s[sizeof(double)];
  double d = getValue();
  memcpy(s, &d, sizeof(double));
  wordlong	value = 0;
  
  u_char* sp = s;
  while (*sp != '\0')
    {
      value *= 167;
      value ^= *sp++;
    }
  return(value);

}
//////////////////////////////////////////////////////////////////////
// Inline functions for the Long class

inline long Long::getValue(void) const
{
  assert(sizeof(long) == sizeof(heapobject));

  return (long)value;
}

inline size_t Long::size(void)
{
  return sizeof(Long) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Long::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << std::hex << (wordptr) this << std::dec 
		  << "] Long: \""
		  << getValue() << "\" ";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the StringObject class

inline size_t StringObject::size() const
{
  return (tag >> 8) - 1 + sizeof(StringObject) / BYTES_PER_WORD;
}

inline wordlong StringObject::hashFn(void) const
{
  char	*s;
  wordlong	value = 0;
  
  s = (char*)theChars;
  while (*s != '\0')
    {
      value *= 167;
      value ^= *s++;
    }
  return(value);

}
//////////////////////////////////////////////////////////////////////
// Inline functions for the Structure class

inline size_t Structure::getArity(void) const
{
  return (tag & TopMask) >> 8;
}


// Returns argument `n' of the Structure, with argument 0 being
// considered as a reference to the functor.

inline Object *Structure::getArgument(const size_t n) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only access valid arguments
  assert(0 <= n && n <= getArity());
  
  return argument[n];
}

inline Object *Structure::getFunctor(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return getArgument(0);
}

// Sets argument `n' of the Structure to `plobj', again, with argument
// 0 being considered the functor.
inline void Structure::setArgument(const size_t n, Object * plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid arguments
  assert(0 <= n && n <= getArity ());
  
  argument[n] = plobj;
}

inline void Structure::setFunctor(Object * plobj)
{
  setArgument(0, plobj);
}

inline size_t Structure::size(void) const
{
  return size(getArity());
}

inline size_t Structure::size(size_t arity)
{
  return arity + sizeof(Structure) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Structure::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (wordptr) this << std::dec << "] Structure:[" 
       << (wordptr)tag << "] arity: " << getArity() << " functor: [ ";
  getFunctor()->printMe_dispatch(atoms, all);
  std::cerr << " ] ";
  for (size_t i = 1; i <= getArity(); i++)
    {
	    std::cerr << i << ": [ ";
      getArgument(i)->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Cons class

inline size_t Cons::size(void)
{
  return(sizeof(Cons) / BYTES_PER_WORD);
}

inline void 
Cons::makeSubstitutionBlockList(void)
{
  assert(isAnyList());

  tag |= FlagSubstitutionBlockList;
}

inline void
Cons::makeObjectVariableList(void)
{
  assert(isAnyList());

  tag |= FlagObjectVariableList;
}

inline void
Cons::makeDelayedProblemList(void)
{
  assert(isAnyList());

  tag |= FlagDelayedProblemList;
}

inline bool
Cons::isAnyList(void) const
{
  return (tag & FlagTypeMask) == FlagAnyList;
}

inline bool
Cons::isSubstitutionBlockList(void) const
{
  return (tag & FlagSubstitutionBlockList) == FlagSubstitutionBlockList;
}

 
inline bool 
Cons::isDelayedProblemList(void) const
{
  return (tag & FlagTypeMask) == FlagDelayedProblemList;
}

inline void
Cons::makeInvertible(void)
{
  assert(isSubstitutionBlockList());

  tag |= FlagInvertible;
}
  
inline bool
Cons::isInvertible(void) const
{
  assert(isSubstitutionBlockList());

  return (tag & FlagInvertibleMask) == FlagInvertible;
}

inline void
Cons::setHead(Object* const plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  head = plobj;
}

inline Object *
Cons::getHead(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return head;
}

inline void 
Cons::setTail(Object* const plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  tail = plobj;
}

inline Object *
Cons::getTail(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return tail;
}

inline Object **
Cons::getTailAddress(void)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return &tail;
}

#ifdef QP_DEBUG
inline void Cons::printMe(AtomTable& atoms, bool all)
{
  std::cerr << "[" << std::hex << (wordptr) this << std::dec << "] Cons: ";
  if (isSubstitutionBlockList()) 
    {
      std::cerr << "(Sub) ";
      if (isInvertible()) std::cerr << "(Invertible) ";
    }
  std::cerr << " head: [ ";
  getHead()->printMe_dispatch(atoms, all);
  std::cerr << " ] tail: [ ";
  getTail()->printMe_dispatch(atoms, all);
  std::cerr << " ]";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the QuantifiedTerm class

inline size_t QuantifiedTerm::size(void)
{
  return sizeof(QuantifiedTerm) / BYTES_PER_WORD;
}

inline Object *QuantifiedTerm::getQuantifier(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return quantifier;
}

inline Object *QuantifiedTerm::getBoundVars(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return boundvars;
}

inline Object *QuantifiedTerm::getBody(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return body;
}

inline void QuantifiedTerm::setQuantifier(Object *o)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  quantifier = o;
}

inline void QuantifiedTerm::setBoundVars(Object *l)
{
  assert(sizeof(Object *) == sizeof(heapobject));
  assert(l->isList() || l->isVariable());

  boundvars = l;
}

inline void QuantifiedTerm::setBody(Object *o)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  body = o;
}

#ifdef QP_DEBUG
inline void QuantifiedTerm::printMe(AtomTable& atoms, bool all)
{
  std::cerr << "[" << std::hex << (wordptr) this << std::dec 
	    << "] QuantifiedTerm: quantifier: [ ";
  getQuantifier()->printMe_dispatch(atoms, all);
  std::cerr << " ] boundvars: [ ";
  getBoundVars()->printMe_dispatch(atoms, all);
  std::cerr << " ] body: [ ";
  getBody()->printMe_dispatch(atoms, all);
  std::cerr << " ]";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Substitution class

inline size_t Substitution::size(void)
{
  return sizeof(Substitution) / BYTES_PER_WORD;
}

inline Object *Substitution::getSubstitutionBlockList(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return sub_block_list;
}

inline Object *Substitution::getTerm(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return term;
}

inline void Substitution::setSubstitutionBlockList(Object *l)
{
  assert(sizeof(Object *) == sizeof(heapobject));
  assert(l->isList());

  sub_block_list = l;
}

inline void Substitution::setTerm(Object *o)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  term = o;
}



#ifdef QP_DEBUG
inline void Substitution::printMe(AtomTable& atoms, bool all)
{
  std::cerr << "[" << std::hex << (wordptr) this << std::dec 
	    << "] Substitution: subst: [ ";
  getSubstitutionBlockList()->printMe_dispatch(atoms, all);
  std::cerr << " ] term: [ ";
  getTerm()->printMe_dispatch(atoms, all);
  std::cerr << " ]";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the SubstitutionBlock class

inline size_t SubstitutionBlock::size(void) const
{
  return size(getSize());
}

inline size_t SubstitutionBlock::size(size_t sub_size)
{
  return sizeof(SubstitutionBlock) / BYTES_PER_WORD + (sub_size - 1) * 2;
}

inline bool
SubstitutionBlock::isInvertible(void) const
{
  return (tag & InvertibleMask) == FlagInvertible;
}

inline void SubstitutionBlock::makeInvertible(void)
{
  tag |= FlagInvertible;
}

inline size_t SubstitutionBlock::getSize(void) const
{
  return tag  >> 12;
}

inline ObjectVariable *SubstitutionBlock::getDomain(const size_t n) const
{
  // Can only access valid pairs
  assert(1 <= n && n <= getSize());
  
  return substitution[n-1].dom;
}



inline Object *SubstitutionBlock::getRange(const size_t n) const
{
  // Can only access valid pairs
  assert(1 <= n && n <= getSize());
  
  return substitution[n-1].ran;
}

inline void SubstitutionBlock::decrementSize(void)
{
  assert(getSize() > 0);

  const size_t new_size = getSize() - 1;

  tag = (tag & ~TopSBMask) | (new_size << 12);
}

inline void SubstitutionBlock::setDomain(const size_t n, Object *dom)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid pairs
//  assert(1 <= n && n <= getSize());
//  assert(dom->isObjectVariable());

  substitution[n-1].dom = OBJECT_CAST(ObjectVariable*, dom);
}

inline void SubstitutionBlock::setRange(const size_t n, Object *ran)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid pairs
//  assert(1 <= n && n <= getSize());

  substitution[n-1].ran = ran;
}

inline void SubstitutionBlock::setSubstitutionPair(const size_t n,
						   Object *dom,
						   Object *ran)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid pairs
  assert(1 <= n && n <= getSize());

  assert(dom->isObjectVariable());

  substitution[n-1].dom = OBJECT_CAST(ObjectVariable*, dom);
  substitution[n-1].ran = ran;
}

//
// Check whether the substitution contains any local object variable on 
// the first range (or domain) position. If it is the case, it means that
// all the other ranges (or domains) are local object variables as well.
//
inline bool SubstitutionBlock::containsLocal(void) const
{
  assert(getSize() > 0);

  return getDomain(1)->isLocalObjectVariable() ||
    getRange(1)->isLocalObjectVariable();
}

#ifdef QP_DEBUG
inline void SubstitutionBlock::printMe(AtomTable& atoms, bool all)
{
  std::cerr << "[" << std::hex << (wordptr) this << " : " << tag << std::dec 
	    << "] SubstitutionBlock: ";
  if (isInvertible()) { std::cerr << "(invertible) "; }
  std::cerr << " size = " << getSize() << " " << endl;
  for (size_t i = 1; i <= getSize(); i++)
    {
	    std::cerr << "dom: [ ";
      getDomain(i)->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
      std::cerr << "ran: [ ";
      getRange(i)->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
}
#endif


inline bool Reference::isCollected(void) const
{
  return (tag & FlagCollected) == FlagCollected;
}

inline void Reference::setCollectedFlag(void)
{
  tag = tag | FlagCollected;
}

inline void Reference::unsetCollectedFlag(void)
{
  tag = tag & ~FlagCollected;
}

inline bool Reference::isPerm(void) const
{
  return (tag & FlagPerm) == FlagPerm;
}
   
inline void Reference::setPermFlag(void)
{
  tag = tag | FlagPerm;
}               

inline Object *Reference::getReference(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return (Object*)(info[0]);
}

inline void Reference::setReference(Object *plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  info[0] = (heapobject)plobj;
}


inline bool Reference::hasExtraInfo(void) const
{
  return tag & FlagExtraInfo;
}

inline void Reference::setExtraInfo(void)
{
  tag |= FlagExtraInfo;
}

inline Atom *
Reference::getName(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  if(hasExtraInfo())
    {
      return OBJECT_CAST(Atom *, (Object*)(info[1]));
    }
  else
    {
      return NULL;
    }
}

inline heapobject*
Reference::getNameAddress(void)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Only a valid operation if Reference has extra information
  assert(hasExtraInfo());
  
  return &info[1];
}

inline void
Reference::setName(Object* name)
{
  assert(name->isAtom());
  assert(hasExtraInfo());
  info[1] = (heapobject)name;
}

inline Object *Reference::getDelays(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  if (hasExtraInfo())
    {
      return (Object*)(info[2]);
    }
  else
    {
      return AtomTable::nil;
    }
}

inline void
Reference::setDelays(Object *delays)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());
  assert(delays->isList() || delays->isVariable());

  info[2] = (heapobject)delays;
}

inline heapobject*
Reference::getDelaysAddress(void)
{
  assert(hasExtraInfo());
  return &info[2];
}

//////////////////////////////////////////////////////////////////////
// Inline functions for the Variable class

inline size_t Variable::size(void) const
{
  return size(hasExtraInfo());
}

//////////////////////////////////////////////////////////////////////
// Inline functions for the (abstract) Reference class

inline void Variable::freeze(void)
{
  tag = (tag & ~TypeTagMask) | VarOtherTag | FlagTemperature;
}

inline bool Variable::isFrozen(void)
{
  return (tag & FlagTemperature) != 0;
}

inline void Variable::thaw(void)
{
  if ((tag & FlagExtraInfo) != 0)
    tag = (tag & ~FlagTemperature);
  else if ((tag & FlagOccurs) == 0)
    tag = (tag & ~(TypeTagMask | FlagTemperature)) | VarTag;
  else
    tag = (tag & ~(TypeTagMask | FlagTemperature)) | VarOCTag;
}

inline bool Variable::isThawed(void)
{
  return (tag & FlagTemperature) == 0;
}

inline bool Variable::isOccursChecked(void) const
{
  return (tag & FlagOccurs) != 0;
}

inline void Variable::setOccursCheck(void)
{
  assert(isVariable());
  tag = tag | FlagOccurs | VarOCTag;
}

inline void Variable::setOccursCheckOther(void)
{
  assert((tag & TypeTagMask) == VarOtherTag);
  tag = tag | FlagOccurs;
}


inline size_t Variable::size(bool has_extra_info)
{
  return sizeof(Variable) / BYTES_PER_WORD + (has_extra_info ? 3 : 0);
}

inline bool Variable::isLifeSet(void) const
{
  return ((tag & 0xffff0000) != 0);
}
   
inline u_int Variable::getLife(void) const
{
  return (tag >> 16);
}
      
inline void Variable::setLife(u_int i)
{
  assert(i != 0);
  tag |= i << 16;
}                 

inline void Variable::copyTag(Object* other)
{
  assert(hasExtraInfo());
  assert(other->isVariable());
  assert(!OBJECT_CAST(Variable*, other)->hasExtraInfo());
  tag |= (other->getTag() & ~TypeTagMask);
}
  
inline heapobject Variable::getID(void) const
{
  return info[3];
}

inline void Variable::setID(heapobject v)
{
  info[3] = v;
}

#ifdef QP_DEBUG
inline void Variable::printMe(AtomTable& atoms, bool all)
{
  std::cerr << "[" << std::hex << (wordptr) this << std::dec 
	    << "] Variable: ";
  if (isFrozen()) { std::cerr << "(frozen) "; }
  if (isOccursChecked()) { std::cerr << "(occurs checked) "; }
  if (getReference() != (Object *) this)
    {
      std::cerr << "<" <<std::hex << (wordptr)(getReference()) << std::dec << ">ref: [ ";
      getReference()->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
  else
    {
      std::cerr << "(unbound)";
      if (hasExtraInfo())
	{
	  std::cerr << "Name {";
	  getName()->printMe_dispatch(atoms, all);
	  if (all)
	    {
	      std::cerr << "} Delays {";
	      getDelays()->printMe_dispatch(atoms, false);
	    }
	  std::cerr << "}";
	}
    }
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the ObjectVariable class

inline Object *ObjectVariable::getDistinctness(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());

  return (Object*)(info[3]);
}

//////////////////////////////////////////////////////////////////////
// Inline functions for the (abstract) Reference class

inline void ObjectVariable::freeze(void)
{
  tag = (tag & ~FlagTemperature) | FlagTemperature;
}

inline bool ObjectVariable::isFrozen(void)
{
  return (tag & FlagTemperature) == FlagTemperature;
}

inline void ObjectVariable::thaw(void)
{
  tag = (tag & ~FlagTemperature);
}

inline bool ObjectVariable::isThawed(void)
{
  return (tag & FlagTemperature) == 0;
}


inline heapobject*
ObjectVariable::getDistinctnessAddress(void)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());

  return &info[3];
}

inline void ObjectVariable::setDistinctness(Object *distinctness)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());
  assert(distinctness->isList() || distinctness->isVariable());

  info[3] = (heapobject)distinctness;
}

inline size_t ObjectVariable::size(void) const
{
  return size(hasExtraInfo());
}

inline size_t ObjectVariable::size(bool has_extra_info)
{
  return sizeof(ObjectVariable) / BYTES_PER_WORD + (has_extra_info ? 3 : 0);
}

inline void ObjectVariable::makeLocalObjectVariable(void)
{
  tag |= ObjectVariable::FlagLocal;
}

/////////////////////////////////////////////////////////
// Other methods

inline long Object::getInteger(void)
{
  assert(isShort() || isLong());

  if (isShort())
    {
      return OBJECT_CAST(Short *, this)->getValue();
    }
  else
    {
      return OBJECT_CAST(Long *, this)->getValue();
    }
}

inline double Object::getDouble(void)
{ 
  assert(isDouble());
  return OBJECT_CAST(Double *, this)->getValue();
}

#ifdef QP_DEBUG
inline void ObjectVariable::printMe(AtomTable& atoms, bool all)
{
  std::cerr << "[" << std::hex << (wordptr) this << std::dec << "] ObjVar: ";
  if (isFrozen()) { std::cerr << "(frozen) "; }
  if (getReference() != OBJECT_CAST(const Object*, this))
    {
	    std::cerr << "ref: [ ";
      getReference()->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
  else
    {
	    std::cerr << "(unbound)";
      if (hasExtraInfo())
	{
		std::cerr << "Name {";
	  getName()->printMe_dispatch(atoms, all);
	  std::cerr << "} Delays {";
	  if (all)
	    {
	      getDelays()->printMe_dispatch(atoms, false);
	      std::cerr << "} Distinctness {";
	      getDistinctness()->printMe_dispatch(atoms, false);
	    }
	  std::cerr << "}";
	}
    }
}
#endif // QP_DEBUG


//
// variableDereference() follows the (ob)variable-reference chain from
// an object -- iteratively, not recursively -- and returns the object
// at the end of the (ob)variable chain.
//
//inline Object*
Object*
Object::variableDereference()
{
  Object* o = this;
  //
  // Ensure we're not about to dereference a NULL pointer
  //
  assert(o != NULL);
#ifdef QP_DEBUG
  if (!o->check_object()) cerr << "object error " << hex << (u_long)o << " -> " << (u_long)(*((heapobject*)o)) << dec << endl;
  assert(o->check_object());

#endif

  while ((o->getTag() & Object::DerefMask) == 0) 
    {
      //
      // While still a (ob)variable, hence referring to something else,
      // move to what it's referring to
      //
      Object* n = OBJECT_CAST(Reference*, o)->getReference();
      assert(n != NULL);
      if ( n == o ) 
          {
	    return o; // An unbound (ob)variable
	  }
      o = n;
   }
  return o;
}


inline bool Object::inList(Object* o) 
{
  for (Object* l = this;
       l->isCons();
       l = OBJECT_CAST(Cons*, l)->getTail()->variableDereference())
    {
      if (o == OBJECT_CAST(Cons*, l)->getHead()->variableDereference())
        {
          return true;
        }
    }
  return false;
}      


//
// Equal constant.
//
inline bool Object::equalConstants(Object* const2)
{
  assert(this->isConstant());
  assert(const2->isConstant());

  if (this == const2) return true;
  if (isAtom()) return false;

  if (getTag() != const2->getTag()) return false;
  size_t s = size_dispatch();
  heapobject* ptr1 = storage();
  heapobject* ptr2 = const2->storage(); 
  for (size_t i = 1; i < s; i++)
    {
      if (*ptr1 != *ptr2) return false;
      ptr1++;
      ptr2++;
    }
  return true;
}

inline bool Object::equalUninterp(Object* const2)
{
  assert(isNumber() || isString());
  if (this == const2) return true;
  if (getTag() != const2->getTag()) return false;
  size_t s = size_dispatch();
  heapobject* ptr1 = storage();
  heapobject* ptr2 = const2->storage(); 
  for (size_t i = 1; i < s; i++)
    {
      if (*ptr1 != *ptr2) return false;
      ptr1++;
      ptr2++;
    }
  return true;
}


// function for GC (threading - Jonker's algorithm
// assumes that what p points at is a pointer
inline void threadGC(heapobject* p)
{
  assert(p != NULL);
  heapobject* tmp = (heapobject*)(*p);
  assert(*tmp != 0);
  *p = *tmp;
  *tmp = (heapobject)p;
}

#ifdef __MINGW32__     
#define bzero(ptr,size) memset (ptr, 0, size);
#endif 

static const int bitsPerWord = 8*sizeof(u_int);

class GCBits
{
private:
  int size;
  u_int* bits;
  static const u_int bitMask = (u_int)-1; 
public:
  GCBits(int s)
  {
    assert(s > 0);
    size = s / bitsPerWord;
    bits = new u_int[size];
    bzero(bits, size*sizeof(u_int));
  }
  ~GCBits() { delete [] bits; }


  void set(int i) 
  { 
    assert(i >= 0); 
    assert((i / bitsPerWord) < size);
    bits[i / bitsPerWord] |= 1 << (bitMask & i);
  }

  void setWord(int i, u_int v)
  {
    assert(i >= 0);
    assert(i < size);
    bits[i] = v;
  }

  bool isSet(int i) 
  { 
    assert(i >= 0); 
    assert((i / bitsPerWord) < size);
    return ((bits[i / bitsPerWord] & (1 << (bitMask & i))) != 0);
  }

  u_int* getBitsPtr() { return bits; }
  
};

class ObjectsStack
{
 private:
  Object** top;
  Object** base;
  Object** high;
  
 public:
  ObjectsStack(size_t size)
    {
      base = new Object*[size];
      top = base;
      high = base + size;
    }

  ~ObjectsStack() { delete [] base; }
  
  void push(Object* ho) { assert(top < high - 1); *top = ho; top++; }
#ifdef QP_DEBUG
  bool atEnd() { return top == (high-1); }
#endif
  
  Object* pop() { assert(top > base); top--; return *top; }
  
  Object** getTop() const { return top; }
  
  void setTop(Object** newtop) { top = newtop; }
  
  void reset() { top = base; }
};


//#endif // HEAP_H

#endif // OBJECTS_H_INLINE


