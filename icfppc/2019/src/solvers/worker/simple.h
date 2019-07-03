#pragma once

#include "base/action.h"
#include "base/ext/world.h"
#include "solvers/worker/base.h"

namespace solvers {
namespace worker {
class Simple : public Base {
 public:
  std::string Name() const override;
  base::ActionsList Solve(base::ext::World& world) override;
};
}  // namespace worker
}  // namespace solvers
