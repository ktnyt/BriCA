#ifndef __BRICA_KERNEL_FUNCTOR_HPP__
#define __BRICA_KERNEL_FUNCTOR_HPP__

#include <functional>

#include "brica/assocvec.hpp"
#include "brica/buffer.hpp"

namespace brica {

using Dict = AssocVec<std::string, Buffer>;
using Functor = std::function<void(Dict, Dict)>;

}  // namespace brica

#endif  // __BRICA_KERNEL_FUNCTOR_HPP__
