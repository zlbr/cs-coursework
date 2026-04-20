#include <algorithm>
#include <chrono>  // NOLINT (build/c++11)
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// classes
#ifndef SIGNATURE_H
#define SIGNATURE_H

class Sighting {
 private:
  int signature;

 public:
  // Single-argument constructor accepts an already existing signature
  Sighting(int sig) : signature(sig) {}

  // Two-argument constructor accepts a speed and brightness, and stores the
  // calculated signature
  Sighting(double speed, double brightness) {
    // signature = (S x B) / 10
    signature = std::ceil(speed * brightness / 10.0);
  }

  // < operator to directly compare Signatures
  bool operator<(const Sighting& rhs) const {
    return signature < rhs.signature;
  };

  int GetSignature() { return signature; }

  // operator<< to pretty-print
  friend std::ostream& operator<<(std::ostream& out, const Sighting& rhs) {
    return out << "Signature: " << rhs.signature;
  }
};

#endif

#ifndef CHRONO_H
#define CHRONO_H

class ChronoTime {
  std::chrono::high_resolution_clock::time_point start;

 public:
  ChronoTime() { this->Reset(); }

  // Reset sets the start time to the current time.
  void Reset() { start = std::chrono::high_resolution_clock::now(); }

  // ElapsedTimeMicro returns the elapsed time in microseconds
  double ElapsedTimeMicro() {
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_us =
        std::chrono::duration<double, std::micro>(end - start).count();

    return elapsed_us;
  }
};

#endif

// pre-declare funcs for intellisense :)
int LinearSearch(std::vector<Sighting>&, std::vector<int>&);
int BinarySearch(std::vector<Sighting>&, std::vector<int>&);

int main(int argc, char* argv[]) {
  // check args
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0]
              << " <sighting_file.dat> <signature_file.dat> <result_file.dat>"
              << std::endl;
    return 1;
  }

  // declare vectors
  std::vector<Sighting> sightings;
  std::vector<int> signatures;

  // open the sightings file
  std::ifstream sightingsFile(argv[1]);
  if (sightingsFile.fail()) {
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    return 1;
  }

  // read all sightings until EOF
  int speed, brightness;
  while (sightingsFile >> speed >> brightness) {
    sightings.push_back(Sighting(speed, brightness));
  }

  sightingsFile.close();

  // open the signatures file
  std::ifstream signaturesFile(argv[2]);
  if (signaturesFile.fail()) {
    std::cerr << "Error: cannot open file " << argv[2] << std::endl;
    return 1;
  }

  // read the signatures until EOF
  int signature;
  while (signaturesFile >> signature) {
    // dupe prevention
    // bool exists = false;
    // for (int s : signatures) {
    //   if (s == signature) {
    //     exists = true;
    //     break;
    //   }
    // }

    // if (!exists)
    signatures.push_back(signature);
  }

  signaturesFile.close();

  // User prompt for search method
  std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;
  char search_type;
  bool validSelection = false;

  // Input validation loop
  while (!validSelection) {
    std::cin >> search_type;
    if (search_type != 'l' && search_type != 'b') {
      std::cerr << "Incorrect choice" << std::endl;
    } else {
      validSelection = true;
    }
  }

  // initialize timer and matches variable
  ChronoTime ct;
  int matches = 0;

  // Implement search logic based on user choice
  switch (search_type) {
    case 'l':
      ct.Reset();
      matches = LinearSearch(sightings, signatures);
      break;
    case 'b':
      // sort signatures and computedSignatures
      std::sort(signatures.begin(), signatures.end());
      std::sort(sightings.begin(), sightings.end());

      ct.Reset();

      matches = BinarySearch(sightings, signatures);
      break;
  }

  double elapsed_us = ct.ElapsedTimeMicro();

  std::cout << "CPU time: " << elapsed_us << " microseconds" << std::endl;

  std::ofstream outfile(argv[3]);
  if (outfile.fail()) {
    std::cerr << "Error: cannot open file " << argv[3] << std::endl;
    return 1;
  }

  // write to file and close
  outfile << matches << std::endl;
  outfile.close();

  return 0;
}

// LinearSearch does a linear search for matching signatures and returns the
// number of matches found
int LinearSearch(std::vector<Sighting>& sightings,
                 std::vector<int>& signatures) {
  int matches = 0;

  for (int sig : signatures) {
    for (Sighting sight : sightings) {
      if (sight.GetSignature() == sig) {
        matches++;
        break;
      }
    }
  }

  return matches;
}

// BinarySearch does a binary search for matching signatures and returns the
// number of matches found
int BinarySearch(std::vector<Sighting>& sightings,
                 std::vector<int>& signatures) {
  int matches = 0;

  for (int sig : signatures) {
    if (std::binary_search(sightings.begin(), sightings.end(), Sighting(sig))) {
      matches++;
    }
  }

  return matches;
}
