#pragma once
#include "stdafx.h"

class TrackMetadata {
public:
    TrackMetadata(const pfc::string8& title, const pfc::string8& artist, const pfc::string8& album);
    const pfc::string8& GetTitle() const;
    const pfc::string8& GetArtist() const;
    const pfc::string8& GetAlbum() const;

private:
    pfc::string8 m_title;
    pfc::string8 m_artist;
    pfc::string8 m_album;
};
