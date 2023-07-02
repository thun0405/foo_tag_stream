#pragma once
#include <pfc/pfc.h>

class TrackMetadata {
public:
    TrackMetadata(
        pfc::string8 title,
        pfc::string8 artist,
        pfc::string8 album
    );
    TrackMetadata(metadb_handle_ptr track);
    TrackMetadata();

    pfc::string8 GetTitle() const;
    pfc::string8 GetArtist() const;
    pfc::string8 GetAlbum() const;
    pfc::string8 ConvertToCSV() const;

private:
    pfc::string8 m_title;
    pfc::string8 m_artist;
    pfc::string8 m_album;
};