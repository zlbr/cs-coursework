#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <queue>
#include <string>
#include <vector>

void CreateInitialRuns(const std::string& infilename, const int num_ways,
                       const int run_size) {
  std::ifstream ifs(infilename);
  int runs = 0;
  do {
    std::vector<int> vec;

    // TODO Q1.1: Step 1 - Fill a local vector with @run_size items from the
    // input file
    int item;
    for (unsigned int i = 0; i < run_size; ++i) {
      ifs >> item;
      vec.push_back(item);
    }

    // TODO Q1.2: Step 2 - Sort the local vector
    // Hint: Use std::sort
    std::sort(vec.begin(), vec.end());

    // TODO Q1.3: Step 3 - Write the sorted vector to a temporary output file
    // The temporary file should be named: infilename + "." + run_number
    // Hint: Use std::ofstream and std::copy with std::ostream_iterator
    std::string fname = infilename + "." + std::to_string(runs);
    std::ofstream outfile(fname);

    if (!outfile.good()) throw std::logic_error("failed to open outfile");

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(outfile, "\n"));
    outfile.close();
  } while (++runs != num_ways);
  ifs.close();
}

// Operate a k-way merge on the @num_ways different sorted files and write the
// final result to an output file
void KWayMerge(const std::string& infilename, const int num_ways) {
  // TODO Q2.1: Open all the @num_ways temporary files created in
  // CreateInitialRuns Also open the output file which will contain the final
  // sorted numbers The output file should be named: infilename + ".sorted"
  std::vector<std::ifstream> infiles;
  std::ofstream outfile(infilename + ".sorted");

  if (!outfile.good()) throw std::logic_error("failed to open outfile");

  for (unsigned int run = 0; run < num_ways; ++run) {
    std::string fname = infilename + "." + std::to_string(run);

    infiles.emplace_back(fname);

    // std::ifstream infile(fname);

    // infiles.push_back(infile);
  }

  // TODO Q2.2: Create a min-heap using std::priority_queue
  // The heap should contain pairs: <value, file_index>
  // Hint: Use std::pair<int, int> and std::greater<> for min-heap behavior
  // Then, push the first item from each temporary file into the heap
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      minHeap;

  int item;
  for (unsigned int run = 0; run < num_ways; ++run) {
    if (infiles.at(run) >> item) {
      minHeap.push({item, run});
    }
  }

  // TODO Q2.3: Complete the K-way merge algorithm
  // While the heap is not empty:
  while (!minHeap.empty()) {
    //   1. Pop the minimum item from the heap
    auto min = minHeap.top();
    minHeap.pop();

    int minValue = min.first;
    int minFileIndex = min.second;

    //   2. Write it to the output file
    outfile << minValue << " ";

    //   3. Read the next item from the same temporary file (if any)
    int nextVal;

    //   4. If there's a next item, push it to the heap
    if (infiles.at(minFileIndex) >> nextVal) {
      minHeap.push({nextVal, minFileIndex});
    }

    //   5. If the file is exhausted, close it
    if (infiles.at(minFileIndex).eof()) infiles.at(minFileIndex).close();
  }
}

#ifndef NO_MAIN
int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "usage: ./external_sort <input_file> "
              << "<num_ways> <run_size>" << std::endl;
    return 1;
  }

  // Open input file
  std::string infilename{argv[1]};

  // Get following arguments
  int num_ways = atoi(argv[2]);
  int run_size = atoi(argv[3]);

  // Sort each ways on its own
  CreateInitialRuns(infilename, num_ways, run_size);

  // Merge all the ways together
  KWayMerge(infilename, num_ways);

  return 0;
}
#endif
