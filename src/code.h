// code.h - Storage for holding compiled programs and functions for the
//	    manipulation.
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
// $Id: code.h,v 1.9 2006/01/31 23:17:49 qp Exp $ 

#ifndef	CODE_H
#define	CODE_H

#include <iostream>

#include "config.h"

#include "area_offsets.h"
#include "defs.h"
#include "heap_qp.h"
#include "instructions.h"
#include "magic.h"
#include "objects.h"
#include "string_map.h"

//
// Forward declaration.
//
class	PredTab;

//typedef word8 	*CodeLoc;
typedef word32   CodeOffset;

  
//
// Fetch 'n' bytes from the code area.
//
inline word8 get1Byte(CodeLoc& loc)
  {
    // No endian issues for a single byte quantity
    return(*loc++);
  }

inline word16	get2Bytes(CodeLoc& loc)
{
  word16 data;

  data = *loc++;
  data = (data << 8) | *loc++;

  return(data);
}

inline word32	get4Bytes(CodeLoc& loc)
{
  word32 data;

  data = *loc++;
  data = (data << 8) | *loc++;
  data = (data << 8) | *loc++;
  data = (data << 8) | *loc++;

  return(data);
}

inline wordptr	getPtrBytes(CodeLoc& loc)
{
#if BITS_PER_WORD == 64
  wordptr data = static_cast<wordptr>(get4Bytes(loc));
  return (data << 32) | static_cast<wordptr>(get4Bytes(loc));
#else
  return get4Bytes(loc);
#endif
}
inline qint64  getLongBytes(CodeLoc& loc)
{
#if BITS_PER_WORD == 64
  qint64 data = static_cast<qint64>(get4Bytes(loc));
  return (data << 32) | static_cast<qint64>(get4Bytes(loc));
#else
  return get4Bytes(loc);
#endif
}


//
// Update the specified location with new data.
//
inline void	update1Byte(CodeLoc loc, word8 data)
{
  *loc = data;
}
inline void	update2Bytes(CodeLoc loc, word16 data)
{
  *loc++ = (data & 0xff00) >> 8;
  *loc   =  data & 0x00ff;
}
inline void	update4Bytes(CodeLoc loc, word32 data)
{
  *loc++ = static_cast<word8>((data & 0xff000000) >> 24);
  *loc++ = static_cast<word8>((data & 0x00ff0000) >> 16);
  *loc++ = static_cast<word8>((data & 0x0000ff00) >> 8);
  *loc   =  static_cast<word8>(data & 0x000000ff);
}
inline void	updatePtrBytes(CodeLoc loc, wordptr data)
{
#if BITS_PER_WORD == 64
  update4Bytes(loc, static_cast<word32>(data >> 32));
  update4Bytes(loc + 4, static_cast<word32>(data & 0xffffffff));
#else
  update4Bytes(loc, static_cast<word32>(data));
#endif
}
inline void     updateLongBytes(CodeLoc loc, qint64 data)
{
#if BITS_PER_WORD == 64
  update4Bytes(loc, static_cast<word32>(data >> 32));
  update4Bytes(loc + 4, static_cast<word32>(data & 0xffffffff));
#else
  update4Bytes(loc, static_cast<word32>(data));
#endif
}

//
// Fetch different kinds of data from the code area.  The pointer to
// the area (the parameter) is incremented past the data after reading.
//
//
inline word8 getInstruction(CodeLoc& loc) { return(get1Byte(loc)); }
inline Object* getConstant(CodeLoc& loc) 
{
  return(reinterpret_cast<Object*>(getPtrBytes(loc)));
}
inline word8 getRegister(CodeLoc& loc) { return(get1Byte(loc)); }
inline word8 getNumber(CodeLoc& loc)  { return(get1Byte(loc)); }
inline wordptr getAddress(CodeLoc& loc)  { return(getPtrBytes(loc)); }
inline qint64 getInteger(CodeLoc& loc)  { return(getLongBytes(loc)); }
inline double getDouble(CodeLoc& loc)
{
  double d;
  memcpy(&d, loc, sizeof(double));
  loc += sizeof(double);
  return d;
}
inline CodeLoc getCodeLoc(CodeLoc& loc)  
{ return(reinterpret_cast<CodeLoc>(getPtrBytes(loc))); }
inline word16 getOffset(CodeLoc& loc)  { return(get2Bytes(loc)); }
inline Atom* getPredAtom(CodeLoc& loc)  
{ 
  Object* a = reinterpret_cast<Object*>(getPtrBytes(loc));
  assert(a->isAtom());
  return(reinterpret_cast<Atom*>(a));
}
inline word16 getTableSize(CodeLoc& loc)  { return(get2Bytes(loc)); }

//
// Update the code area with the new data.
//
inline void	updateInstruction(const CodeLoc loc, const word8 data)
{ update1Byte(loc, data); }
inline void	updateConstant(const CodeLoc loc, Object* data)
{ updatePtrBytes(loc, reinterpret_cast<wordptr>(data)); }
inline void	updateInteger(const CodeLoc loc, qint64 data)
{ updateLongBytes(loc, data); }
inline void     updateDouble(const CodeLoc loc, double data)
{
  memcpy(loc, &data, sizeof(double));
}
inline void	updateRegister(const CodeLoc loc, const word8 data)
{ update1Byte(loc, data); }
inline void	updateNumber(const CodeLoc loc, const word8 data)
{ update1Byte(loc, data); }
inline void	updateAddress(const CodeLoc loc, const wordptr data)
{ updatePtrBytes(loc, data); }
inline void	updateCodeLoc(const CodeLoc loc, const CodeLoc data)
{ updatePtrBytes(loc, reinterpret_cast<wordptr>(data)); }
inline void	updateOffset(const CodeLoc loc, const word16 data)
{ update2Bytes(loc, data); }
inline void	updatePredAtom(const CodeLoc loc, const Atom* data)
{ updatePtrBytes(loc, reinterpret_cast<wordptr>(data)); }
inline void	updateTableSize(const CodeLoc loc, const word16 data)
{ update2Bytes(loc, data); }
//
//  Area for storing static code
//
class   StaticCodeArea
{

private:
  word32	allocated_size;
  CodeLoc       base;
  CodeLoc       top;
  CodeLoc       last;

protected:
  virtual       const char      *getAreaName(void) const = 0;

public:
  explicit StaticCodeArea(word32 size);
  virtual ~StaticCodeArea(void);

  CodeLoc getTopOfStack(void) const       { return(top); }
  CodeLoc getBaseOfStack(void) const       { return(base); }
  word32  allocatedSize(void) const       { return(allocated_size); }

  CodeLoc allocateElements(const word32 n)
  {
    CodeLoc currtop = top;
    if (top + n >= last)
    {
      OutOfPage(__FUNCTION__,
                getAreaName(),
		allocated_size / K);
    }
    else
    {
      top += n;
      return(currtop);
    }
  }
  void saveArea(ostream& ostrm, const wordlong magic) const;

  void readData(istream& istrm, const word32 readSize);

  void loadArea(istream& istrm);

  void loadFileSegment(istream& istrm, const word32 size)
    {
      readData(istrm, size);
    }
  
};

class	Code : public StaticCodeArea
{

private:
  Timestamp stamp;
  //
  // Return the name of the table.
  //
  virtual const char *getAreaName(void) const { return("code area"); }
  
  //
  // Push 'n' bytes into the code area.
  //
  void push1Byte(word8 data) { update1Byte(allocateElements(1), data); }
  void push2Bytes(word16 data) { update2Bytes(allocateElements(2), data); }
  void push4Bytes(word32 data) { update4Bytes(allocateElements(4), data); }
  void pushPtrBytes(wordptr data)
    {
      updatePtrBytes(allocateElements(sizeof(wordptr)), data);
    }
  
  //
  // Resolve the CALL_PREDICATE and EXECUTE_PREDICATE instructions.
  //
  void resolveCallInstruction(const CodeLoc loc,
			      const PredLoc pred,
			      const word8 EscInst,
			      const word8 AddrInst,
			      PredTab& predicates,
			      Code* code);

  //
  // Turn atom and number pointers into tagged offsets and turn code pointers
  // into code offsets.
  //
  void pointersToOffsets(CodeLoc pc, const CodeLoc end, AtomTable& atoms);

  //
  // Turn tagged offsets into atoms and numbers and turn code offsets
  // into code pointers.
  //
  void offsetsToPointers(CodeLoc pc, const CodeLoc end, AtomTable& atoms);

public:
  
  //
  // Size of different kinds of data in the code area.
  //
  static const	size_t	SIZE_OF_INSTRUCTION	= sizeof(word8);
  typedef word8 InstructionSizedType;

  static const	size_t	SIZE_OF_CONSTANT	= sizeof(wordptr);
  typedef wordptr ConstantSizedType;

  static const	size_t	SIZE_OF_INTEGER	        = sizeof(qint64);
  typedef qint64 IntegerSizedType;

  static const	size_t	SIZE_OF_DOUBLE	        = sizeof(double);
  typedef double DoubleSizedType;

  static const	size_t	SIZE_OF_REGISTER	= 1;
  typedef word8 RegisterSizedType;

  static const	size_t	SIZE_OF_NUMBER		= 1;
  typedef word8 NumberSizedType;

  static const size_t	SIZE_OF_ADDRESS		= sizeof(wordptr);
  typedef wordptr AddressSizedType;

  static const	size_t	SIZE_OF_OFFSET		= 2;
  typedef word16 OffsetSizedType;

  static const	size_t	SIZE_OF_PRED		= sizeof(wordptr);
  typedef wordptr PredSizedType;

  static const	size_t	SIZE_OF_TABLE_SIZE	= 2;
  typedef word16 TableSizeSizedType;
  
  static const word32	SIZE_OF_HEADER		=
    SIZE_OF_CONSTANT + SIZE_OF_NUMBER + SIZE_OF_OFFSET;

  //
  // The Fail label for hash tables in code area.
  //
  // XXX This is very probably broken.
  static const	word32	FAIL			= 65535;
  
  explicit Code(word32 CodeSize)
    : StaticCodeArea (CodeSize)
    {}
  
  //
  // Push different kinds of data into the code area.
  //
  // If AtomLoc or word32 changes representation, then a bug may occur
  // if putPredAtom is not changed.
  //
  void	pushInstruction(const word8 data) { push1Byte(data); }
  void	pushConstant(const Object* data) 
    { 
      pushPtrBytes(reinterpret_cast<wordptr>(data)); 
    }
  void	pushRegister(const word8 data) { push1Byte(data); }
  void	pushNumber(const word8 data) { push1Byte(data); }
  void	pushAddress(const word32 data) { push4Bytes(data); }
  void	pushCodeLoc(const CodeLoc data) { pushPtrBytes(reinterpret_cast<wordptr>(data)); }
  void	pushOffset(const word16 data) { push2Bytes(data); }
  void	pushPredAtom(const Atom* data) 
    { 
      pushPtrBytes(reinterpret_cast<wordptr>(data)); 
    }
  void	pushTableSize(const word16 data) { push2Bytes(data); }
  
  //
  // The following manipulation requires a bit of finesse.
  // The CALL_ADDRESS and CALL_ESCAPE instructions are smaller than the 
  // EXECUTE_PREDICATE instruction, so we have to move stuff around a bit.
  // The EXECUTE_ADDRESS and EXECUTE_ESCAPE instructions are likewise smaller.
  // 
  void	updateCallInstruction(const CodeLoc loc,
			      const word8 inst,
			      const CodeLoc addr);
  
  //
  // Retrieve the number of Y registers available from a CALL
  // instruction.
  //
  word32	getNumYRegs(const CodeLoc loc) const
  {
    CodeLoc	calln;
    
    calln = loc - SIZE_OF_NUMBER;
    return(getNumber(calln));
  }
  
  //
  // Return the top of the area.
  //
  CodeLoc getTop(void) const { return(getTopOfStack()); }
  CodeLoc getBase(void) const { return(getBaseOfStack()); }
  
  //
  // Procedures for linking.
  //
  
  //
  // Read the predicate together with its preamble and store them in the
  // code area.
  // Return whether it is successful or not.
  //
  bool	addPredicate(istream& istrm, const char *file, const StringMap& map,
		     const StringMapLoc base,
		     AtomTable* atoms, PredTab& predicates, Code* code);
  
  //
  // Resolve all the references to atoms, predicates, and create hash
  // table for "switch" instructions.
  //
  void resolveCode(CodeLoc pc, 
		   const CodeLoc end, 
		   const StringMap& string_map, 
		   const StringMapLoc string_base,
		   PredTab& predicates,
		   AtomTable* atoms,
		   Code* code);

  //
  // Returns the size of the argument type indicated by char.
  //
  size_t argSize(const char) const;

  //
  // Total size of the code area.
  //
  word32 size(void) const { return(allocatedSize()); }
  
  //
  // Save the code area.
  //
  void	save(ostream& ostrm, AtomTable& atoms); 
  
  //
  // Restore the code area.
  //
  void	load(istream& istrm, AtomTable& atoms);
  
  const word32 GetStamp(void) { return stamp.GetStamp(); }
  void Stamp(void) { stamp.Stamp(); }

};

#endif	// CODE_H


