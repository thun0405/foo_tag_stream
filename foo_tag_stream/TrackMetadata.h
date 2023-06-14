#pragma once
#include <pfc/pfc.h>

class TrackMetadata {
public:
    TrackMetadata(
        int number,
        pfc::string8 title,
        pfc::string8 artist,
        pfc::string8 album
    );

    int GetNumber() const;
    pfc::string8 GetTitle() const;
    pfc::string8 GetArtist() const;
    pfc::string8 GetAlbum() const;

private:
    int m_number;
    pfc::string8 m_title;
    pfc::string8 m_artist;
    pfc::string8 m_album;
};
