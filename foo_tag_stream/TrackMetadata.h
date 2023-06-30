#pragma once
#include <pfc/pfc.h>

class TrackMetadata {
public:
    TrackMetadata(
        int number,
        pfc::string8 title,
        pfc::string8 artist,
        pfc::string8 album,
        pfc::string8 albumArtist
    );
    TrackMetadata(metadb_handle_ptr track);
    TrackMetadata();

    int GetNumber() const;
    pfc::string8 GetTitle() const;
    pfc::string8 GetArtist() const;
    pfc::string8 GetAlbum() const;
    pfc::string8 GetAlbumArtist() const;
    pfc::string8 ConvertToCSV() const;

private:
    int m_number;
    pfc::string8 m_title;
    pfc::string8 m_artist;
    pfc::string8 m_album;
    pfc::string8 m_albumArtist;
};
