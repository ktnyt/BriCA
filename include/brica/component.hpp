/******************************************************************************
 *
 * brica/component.hpp
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *****************************************************************************/

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

  Channel& get_in_channel(std::string name) { return *in_channels[name]; }

  void make_out_channel(std::string name) {
    outputs.emplace(name);
    out_channels.emplace(name);
  }

  Channel& get_out_channel(std::string name) { return *out_channels[name]; }

  void connect(Component& target, std::string from, std::string to) {
    in_channels[to] = target.out_channels[from];
  }

  void collect() {
    for (std::size_t i = 0; i < inputs.size(); ++i) {
      inputs.index(i) = in_channels.index(i)->recv();
    }
  }

  void execute() { functor(inputs, outputs); }

  void expose() {
    for (std::size_t i = 0; i < outputs.size(); ++i) {
      out_channels.index(i)->send(outputs.index(i));
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
