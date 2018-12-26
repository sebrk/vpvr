#pragma once

#include "stdafx.h"
#include "typeDefs3D.h"

#ifdef ENABLE_SDL
class VertexBuffer
{
public:
   enum LockFlags
   {
      WRITEONLY,
      NOOVERWRITE,
      DISCARDCONTENTS = D3DLOCK_DISCARD
   };
   GLuint Buffer;
   GLuint Array;
   GLuint count;
   GLuint sizePerVertex;
   DWORD fvf;
   GLuint offset;//unused ATM, but if we want to group multiple IndexBuffers later in one buffer we might need it
   DWORD usage;

   void lock(const unsigned int offsetToLock, const unsigned int sizeToLock, void **dataBuffer, const DWORD flags);
   void unlock(void);
   void release(void);

   static void CreateVertexBuffer(const unsigned int vertexCount, const DWORD usage, const DWORD fvf, VertexBuffer **vBuffer);

private:
   unsigned int _offsetToLock;
   unsigned int _sizeToLock;
   void *_dataBuffer;
};




#else

class VertexBuffer : public IDirect3DVertexBuffer9
{
public:
   enum LockFlags
   {
      WRITEONLY = 0,                        // in DX9, this is specified during VB creation
      NOOVERWRITE = D3DLOCK_NOOVERWRITE,    // meaning: no recently drawn vertices are overwritten. only works with dynamic VBs.
                                            // it's only needed for VBs which are locked several times per frame
                                            DISCARDCONTENTS = D3DLOCK_DISCARD     // discard previous contents; only works with dynamic VBs
   };

   void lock(const unsigned int offsetToLock, const unsigned int sizeToLock, void **dataBuffer, const DWORD flags);
   void unlock(void);
   void release(void);

   static void CreateVertexBuffer(const unsigned int vertexCount, const DWORD usage, const DWORD fvf, VertexBuffer **vBuffer);
   static void setD3DDevice(IDirect3DDevice9* pD3DDevice);
private:
   VertexBuffer();     // disable default constructor
   static IDirect3DDevice9* m_pD3DDevice;
};


#endif