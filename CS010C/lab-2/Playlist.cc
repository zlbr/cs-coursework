#include "Playlist.h"

#include <iostream>
#include <string>

// default constructor: use null ptrs
Playlist::Playlist() : head(nullptr), tail(nullptr) {}

// default destructor: delete everything
Playlist::~Playlist() {
  PlaylistNode* node = head;
  PlaylistNode* temp = nullptr;

  while (node) {
    temp = node->GetNext();
    delete node;
    node = temp;
  }
}

void Playlist::PrintMenu(std::string playlistName) {
  char ch;
  while (true) {
    std::cout << std::endl << playlistName << " PLAYLIST MENU" << std::endl;

    std::cout << "a - Add song" << std::endl;
    std::cout << "d - Remove song" << std::endl;
    std::cout << "c - Change position of song" << std::endl;
    std::cout << "s - Output songs by specific artist" << std::endl;
    std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
    std::cout << "o - Output full playlist" << std::endl;
    std::cout << "q - Quit" << std::endl;

    std::cin >> ch;

    // the extra newline in cin gets into the next read operation
    // https://stackoverflow.com/a/33402868
    std::cin.ignore();

    std::cout << std::endl;

    // exit
    if (ch == 'q') {
      exit(0);
    }

    // output full playlist
    if (ch == 'o') {
      if (!head)
        std::cout << "Playlist is empty" << std::endl;
      else
        this->PrintPlaylist();
    }

    // add song
    if (ch == 'a') {
      std::string id, name, artist;
      int length;

      std::cout << "ADD SONG" << std::endl;

      std::cout << "Enter song's unique ID: ";
      std::getline(std::cin, id);

      std::cout << std::endl << "Enter song's name: ";
      std::getline(std::cin, name);

      std::cout << std::endl << "Enter artist's name: ";
      std::getline(std::cin, artist);

      std::cout << std::endl << "Enter song's length (in seconds): ";
      std::cin >> length;

      std::cout << std::endl;

      this->AddSong(id, name, artist, length);
    }

    // remove song
    if (ch == 'r') {
      std::string id;

      std::cout << "REMOVE SONG" << std::endl;
      std::cout << "Enter song's unique ID: ";
      std::cin >> id;

      std::cout << std::endl;

      this->RemoveSong(id);
    }

    if (ch == 'd') {
      std::string removeId;
      std::cout << "REMOVE SONG" << std::endl;

      std::cout << "Enter song's unique ID: ";
      std::getline(std::cin, removeId);
      std::cout << std::endl;

      this->RemoveSong(removeId);
    }

    if (ch == 'c') {
      int currentPos, newPos;

      std::cout << "CHANGE POSITION OF SONG" << std::endl;
      std::cout << "Enter song's current position: ";
      std::cin >> currentPos;

      std::cout << std::endl << "Enter new position for song: ";
      std::cin >> newPos;

      std::cout << std::endl;

      // subtract 1, since these indices are 1-indexed
      this->ChangePosition(currentPos - 1, newPos - 1);
    }

    if (ch == 's') {
      std::string artist;
      std::cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << std::endl;

      std::cout << "Enter artist's name: ";
      std::getline(std::cin, artist);

      std::cout << std::endl;

      this->OutputSongsByArtist(artist);
    }

    if (ch == 't') {
      std::cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << std::endl;
      std::cout << "Total time: " << this->TotalTime() << " seconds"
                << std::endl;
    }
  }
}

// AddSong inserts song with specified params to the back of the list
void Playlist::AddSong(std::string id, std::string name, std::string artist,
                       int length) {
  PlaylistNode* node = new PlaylistNode(id, name, artist, length);

  if (!head) {
    head = node;
    tail = node;
  } else {
    tail->InsertAfter(node);
    tail = node;
  }
}

// RemoveSong finds and removes song with specified id
void Playlist::RemoveSong(std::string id) {
  PlaylistNode* last = nullptr;
  PlaylistNode* node = head;

  while (node) {
    if (node->GetID() == id) {
      if (last) last->InsertAfter(node->GetNext());
      if (head == node) head = node->GetNext();
      if (tail == node) tail = last;

      std::cout << "\"" << node->GetSongName() << "\" removed" << std::endl;

      break;
    }

    last = node;
    node = node->GetNext();
  }
};

// ChangePosition moves the song at currentPos to newPos
void Playlist::ChangePosition(int currentPos, int newPos) {
  PlaylistNode* node = head;
  int count = 0;

  // count nodes
  while (node) {
    count++;
    node = node->GetNext();
  }

  PlaylistNode** arr = new PlaylistNode*[count];

  // fill array with nodes
  node = head;
  for (int j = 0; j < count; j++) {
    arr[j] = node;
    node = node->GetNext();
  }

  // save the node being moved
  PlaylistNode* currPosNode = arr[currentPos];

  // shift elements in array to simulate the move
  if (currentPos < newPos) {
    // moving down the list
    for (int j = currentPos; j < newPos; j++) {
      arr[j] = arr[j + 1];
    }
  } else {
    // moving up the list
    for (int j = currentPos; j > newPos; j--) {
      arr[j] = arr[j - 1];
    }
  }

  // place moved node at new position
  arr[newPos] = currPosNode;

  // rebuild linked list from array
  for (int j = 0; j < count; j++) {
    if (j < count - 1) {
      arr[j]->SetNext(arr[j + 1]);
    } else {
      arr[j]->SetNext(nullptr);
    }
  }

  // update head and tail
  head = arr[0];
  tail = arr[count - 1];

  std::cout << "\"" << currPosNode->GetSongName() << "\" moved to position "
            << (newPos + 1) << std::endl;

  // deallocate temp array
  delete[] arr;
};

// TotalTime returns the sum of all node song lengths
int Playlist::TotalTime() const {
  PlaylistNode* node = head;
  int time = 0;

  while (node) {
    time += node->GetSongLength();
    node = node->GetNext();
  }

  return time;
}

// PrintPlaylist prints the full playlist with indices
void Playlist::PrintPlaylist() const {
  PlaylistNode* node = head;
  int i = 1;

  while (node) {
    std::cout << std::endl << i << "." << std::endl;
    node->PrintPlaylistNode();

    node = node->GetNext();
    i++;
  }
}

// OutputSongsByArtist prints all songs by the specified artist
void Playlist::OutputSongsByArtist(std::string artist) const {
  PlaylistNode* node = head;
  int i = 1;

  while (node) {
    if (node->GetArtistName() == artist) {
      std::cout << std::endl << i << "." << std::endl;
      node->PrintPlaylistNode();
    }

    node = node->GetNext();
    i++;
  }
}

// ============================================================================================

// default null constructor
PlaylistNode::PlaylistNode()
    : uniqueID("none"),
      songName("none"),
      artistName("none"),
      songLength(0),
      nextNodePtr(nullptr) {}

// parameterized construstor
PlaylistNode::PlaylistNode(std::string id, std::string name, std::string artist,
                           int length)
    : uniqueID(id),
      songName(name),
      artistName(artist),
      songLength(length),
      nextNodePtr(nullptr) {};

// InsertAfter inserts the specified node after this one, then sets its next
// value to the current (old) one
void PlaylistNode::InsertAfter(PlaylistNode* node) {
  node->nextNodePtr = nextNodePtr;
  nextNodePtr = node;
};

// SetNext sets the next pointer
void PlaylistNode::SetNext(PlaylistNode* node) { nextNodePtr = node; };

// accessors. self-explanatory and succinct
std::string PlaylistNode::GetID() const { return uniqueID; };
std::string PlaylistNode::GetSongName() const { return songName; };
std::string PlaylistNode::GetArtistName() const { return artistName; };
int PlaylistNode::GetSongLength() const { return songLength; };
PlaylistNode* PlaylistNode::GetNext() const { return nextNodePtr; };

void PlaylistNode::PrintPlaylistNode() {
  std::cout << "Unique ID: " << uniqueID << std::endl;
  std::cout << "Song Name: " << songName << std::endl;
  std::cout << "Artist Name: " << artistName << std::endl;
  std::cout << "Song Length (in seconds): " << songLength << std::endl;
};
