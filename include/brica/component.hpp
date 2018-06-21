#ifndef __BRICA_KERNEL_COMPONENT_HPP__
#define __BRICA_KERNEL_COMPONENT_HPP__

#include "brica/assocvec.hpp"
#include "brica/buffer.hpp"
#include "brica/functor.hpp"

#include <string>
#include <utility>

namespace brica {

class Component {
  class Channel {
   public:
    virtual void send(Buffer& value) { buffer = value; }
    virtual const Buffer& recv() const { return buffer; }

   private:
    Buffer buffer;
  };

  using Channels = AssocVec<std::string, std::shared_ptr<Channel>>;

 public:
  void make_in_channel(std::string name) {
    inputs.emplace(name);
    in_channels.emplace(name);
  }

  void collect() {
    for (std::size_t i = 0; i < inputs.size(); ++i) {
      inputs[i] = in_channels[i]->recv();
    }
  }

  void execute() { functor(inputs, outputs); }

  void expose() {
    for (std::size_t i = 0; i < outputs.size(); ++i) {
      out_channels[i]->send(outputs[i]);
    }
  }

 private:
  Functor functor;
  Dict inputs;
  Dict outputs;
  Channels in_channels;
  Channels out_channels;
};

}  // namespace brica

#endif  // __BRICA_KERNEL_COMPONENT_HPP__
