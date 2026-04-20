#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>

class PlaylistNode {
 public:
  // constructors & destructors
  PlaylistNode();
  PlaylistNode(std::string id, std::string name, std::string artist,
               int length);

  // functions
  void InsertAfter(
      PlaylistNode* node);  // node->= this; this->next = node->next
  void SetNext(PlaylistNode* node);
  std::string GetID() const;
  std::string GetSongName() const;
  std::string GetArtistName() const;
  int GetSongLength() const;
  PlaylistNode* GetNext() const;
  void PrintPlaylistNode();

 private:
  std::string uniqueID;
  std::string songName;
  std::string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
};

class Playlist {
 public:
  // constructors & destructors
  Playlist();
  ~Playlist();

  // functions
  void PrintMenu(std::string name);
  void AddSong(std::string id, std::string name, std::string artist,
               int length);
  void RemoveSong(std::string id);
  void ChangePosition(int currentPos, int newPos);
  void OutputSongsByArtist(std::string artist) const;
  int TotalTime() const;
  void PrintPlaylist() const;

 private:
  PlaylistNode* head;
  PlaylistNode* tail;
};

#endif