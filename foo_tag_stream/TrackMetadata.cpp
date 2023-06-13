#include "stdafx.h"
#include "TrackMetadata.h"

TrackMetadata::TrackMetadata(const pfc::string8& title, const pfc::string8& artist, const pfc::string8& album)
    : m_title(title), m_artist(artist), m_album(album) {}

const pfc::string8& TrackMetadata::GetTitle() const {
    return m_title;
}

const pfc::string8& TrackMetadata::GetArtist() const {
    return m_artist;
}

const pfc::string8& TrackMetadata::GetAlbum() const {
    return m_album;
}
