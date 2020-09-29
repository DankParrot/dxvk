#pragma once

#include "d3d8_include.h"

#include <unordered_map>

namespace dxvk {

  template <typename D3D9, typename D3D8>
  class D3D8WrappedObject : public ComObjectClamp<D3D8> {

    // Address lookup table for things we don't just cache
    static inline std::unordered_map<D3D9*, D3D8*> LookupTable;

  public:

    D3D8WrappedObject(Com<D3D9>&& object)
      : m_d3d9(std::move(object)) {
      LookupTable[m_d3d9.ptr()] = this;
    }

    ~D3D8WrappedObject() {
      LookupTable.erase(m_d3d9.ptr());
    }

    D3D9* GetD3D9() {
      return m_d3d9.ptr();
    }

    static inline D3D8* LookupAddress(D3D9* pAddress9) {
      return LookupTable[pAddress9];
    }

  private:

    Com<D3D9> m_d3d9;

  };

}