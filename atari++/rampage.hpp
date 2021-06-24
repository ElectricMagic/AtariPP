/***********************************************************************************
 **
 ** Atari++ emulator (c) 2002 THOR-Software, Thomas Richter
 **
 ** $Id: rampage.hpp,v 1.8 2015/05/21 18:52:42 thor Exp $
 **
 ** In this module: Definition of a page of memory
 **********************************************************************************/

#ifndef RAMPAGE_HPP
#define RAMPAGE_HPP

/// Includes
#include "types.hpp"
#include "page.hpp"
#include "new.hpp"
///

/// Class RamPage
// Defines a single page of real memory
class RamPage : public Page {  
public:
  //
  // The constructor also constructs the memory here.
  RamPage(void)
    : Page(new UBYTE[256])
  { }
  //
  ~RamPage(void)
  {
    // This is not our field, but we delete it since we constructed it.
    delete[] memory;
  }
  //
  //
  // We overload the memory access functions such that we have faster
  // access if the compiler is smart enough. Maybe it isn't.
  // Read a byte. Returns the byte read.
  UBYTE ReadByte(ADR mem)
  {
    return memory[mem & PAGE_MASK];
  }
  //
  // Write a byte to a page.
  void WriteByte(ADR mem,UBYTE val)
  {
    memory[mem & PAGE_MASK] = val;
  }
  //
  // The following "complex" functions should never be called since the page
  // should fall back to direct reads/writes in first place. We present them
  // here for orthogonality
  // Read a byte. Returns the byte read.
  UBYTE ComplexRead(ADR mem)
  {
    return memory[mem & PAGE_MASK];
  }
  //
  // Write a byte to a page.
  void ComplexWrite(ADR mem,UBYTE val)
  {
    memory[mem & PAGE_MASK] = val;
  }  
  //
  // Patch a byte into a RAM. 
  virtual void PatchByte(ADR mem,UBYTE val)
  {
    memory[mem & PAGE_MASK] = val;
  }  
  //
  // Blank a rampage to all zeros: This initializes a page
  // for a coldstart.
  void Blank(void)
  {
    memset(memory,0,256);
  }  
};
///

///
#endif
