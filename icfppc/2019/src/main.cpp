#include "base/eval/evaluator.h"
#include "solvers/lscm.h"
#include "solvers/single.h"
#include "solvers/worker/simple.h"
#include "common/solvers/merger.h"
#include <string>

int main() {
  std::string path_to_root = "../icfppc/2019";
  base::eval::Evaluator evaluator;
  solvers::worker::Simple worker_simple;
  solvers::Merger merger(path_to_root + "/solutions", "all");
  solvers::LSCM solver_lscm;
  solvers::Single solver_single_simple(worker_simple);
  merger.Add(solver_lscm);
  merger.Add(solver_single_simple);
  for (unsigned i = 1; i <= 300; ++i) {
    std::string short_name = "prob-" + std::to_string(i + 1000).substr(1);
    std::string problem_dir = path_to_root + "/problems/main";
    std::string problem_filename = short_name + ".desc";
    std::string problem = merger.Read(problem_dir, problem_filename);
    std::string solution_filename = short_name + ".sol";
    merger.Solve(problem, solution_filename, evaluator);
  }
  return 0;
}
