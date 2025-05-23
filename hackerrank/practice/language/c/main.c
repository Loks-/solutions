#include <stdio.h>

int run_solution(const char* solution_name);

int ProxyRunWithInput(const char* solution_name, const char* input_file_name) {
  FILE* fp = 0;
  if (input_file_name) fp = freopen(input_file_name, "r", stdin);
  int solution_results = run_solution(solution_name);
  if (fp) fclose(fp);
  return solution_results;
}

int ProxyRunWithOutput(const char* solution_name, const char* input_file_name,
                       const char* output_file_name) {
  FILE* fp = 0;
  if (output_file_name) fp = freopen(output_file_name, "w", stdout);
  int solution_results = ProxyRunWithInput(solution_name, input_file_name);
  if (fp) fclose(fp);
  return solution_results;
}

// Returns 0 if files are equal and -1 otherwise.
int CompareFiles(const char* file1_name, const char* file2_name) {
  FILE* fp1 = fopen(file1_name, "r");
  FILE* fp2 = fopen(file2_name, "r");
  if (!fp1 || !fp2) return -4;
  char ch1 = 0, ch2 = 0;
  for (; ch1 != EOF && ch2 != EOF;) {
    ch1 = fgetc(fp1);
    ch2 = fgetc(fp2);
    if (ch1 != ch2) break;
  }
  if (ch1 == EOF && ch2 == EOF)
    return 0;
  else
    return -1;
}

int ProxyTest(const char* solution_name, const char* input_file_name,
              const char* test_file_name) {
  const char* temp_file_name = "temp.out";
  int solution_results =
      ProxyRunWithOutput(solution_name, input_file_name, temp_file_name);
  if (solution_results) return solution_results;
  return CompareFiles(temp_file_name, test_file_name);
}

int auto_run_or_test(const char* solution_name, const char* input_file_name,
                     const char* test_file_name) {
  return test_file_name
             ? ProxyTest(solution_name, input_file_name, test_file_name)
             : ProxyRunWithInput(solution_name, input_file_name);
}

int main(int nargs, char** pargs) {
  char buf[256];
  char* solution_name = 0;
  if (nargs >= 2) {
    solution_name = pargs[1];
  } else {
    printf("Input hackerrank c solution to run:\n");
    scanf("%255s", buf);
    solution_name = buf;
  }
  return auto_run_or_test(solution_name, (nargs > 2) ? pargs[2] : 0,
                          (nargs > 3) ? pargs[3] : 0);
}
