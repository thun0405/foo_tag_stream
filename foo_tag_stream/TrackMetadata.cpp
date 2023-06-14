#include "stdafx.h"
#include "TrackMetadata.h"

TrackMetadata::TrackMetadata(
    int number,
    pfc::string8 title,
    pfc::string8 artist,
    pfc::string8 album
) : 
    m_number(number), 
    m_title(title), 
    m_artist(artist), 
    m_album(album) 
{}

int TrackMetadata::GetNumber() const {
    return m_number;
}

pfc::string8 TrackMetadata::GetTitle() const {
    return m_title;
}

pfc::string8 TrackMetadata::GetArtist() const {
    return m_artist;
}

pfc::string8 TrackMetadata::GetAlbum() const {
    return m_album;
}
