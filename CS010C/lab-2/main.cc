#include <iostream>
#include <string>

#include "Playlist.h"

int main(int argc, char const* argv[]) {
  std::string playlistTitle = "";
  std::cout << "Enter playlist's title:\n";

  // get a string from the user
  std::getline(std::cin, playlistTitle);

  // construct playlist & show the menu
  Playlist pl;

  pl.PrintMenu(playlistTitle);

  return 0;
}
