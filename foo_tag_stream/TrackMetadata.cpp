#include "stdafx.h"
#include "TrackMetadata.h"
#include <future>

TrackMetadata::TrackMetadata(
    pfc::string8 title,
    pfc::string8 artist,
    pfc::string8 album
) : 
    m_title(title), 
    m_artist(artist), 
    m_album(album) 
{}

TrackMetadata::TrackMetadata(metadb_handle_ptr track)
{
    // metadb_handle_ptrが有効なポインタであることを確認
    if (track.is_valid()) {
        file_info_impl info;
        if (track->get_info_async(info)) {
            // メタデータを取得
            m_title = info.meta_get("TITLE", 0);
            m_artist = info.meta_get("ARTIST", 0);
            m_album = info.meta_get("ALBUM", 0);
        }
    }
}

TrackMetadata::TrackMetadata()
{
}

pfc::string8 TrackMetadata::ConvertToCSV() const
{
    auto appendField = [](pfc::string8& csv, const pfc::string8& field) {
        csv << (field.is_empty() ? pfc::string8("") : field) << ",";
    };

    pfc::string8 csv;
    appendField(csv, m_title);
    appendField(csv, m_artist);
    appendField(csv, m_album);

    return csv;
}

pfc::string8 TrackMetadata::GetTitle() const
{
    return m_title;
}

pfc::string8 TrackMetadata::GetArtist() const
{
    return m_artist;
}

pfc::string8 TrackMetadata::GetAlbum() const
{
    return m_album;
}

void TrackMetadata::SetTitle(pfc::string8 title)
{
    m_title = title;
}

void TrackMetadata::SetArtist(pfc::string8 artist)
{
    m_artist = artist;
}

void TrackMetadata::SetAlbum(pfc::string8 album)
{
    m_album = album;
}
