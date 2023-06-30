#include "stdafx.h"
#include "TrackMetadata.h"
#include <future>

TrackMetadata::TrackMetadata(
    int number,
    pfc::string8 title,
    pfc::string8 artist,
    pfc::string8 album,
    pfc::string8 albumArtist
) : 
    m_number(number), 
    m_title(title), 
    m_artist(artist), 
    m_album(album) 
{}

TrackMetadata::TrackMetadata(metadb_handle_ptr track)
{
    // metadb_handle_ptrが有効なポインタであることを確認
    if (track.is_valid()) {
        // 非同期タスクを作成
        std::future<file_info_impl> future = std::async(std::launch::async, [&]() {
            file_info_impl info;
            track->get_info_async(info);
            return info;
            });

        // 非同期タスクが完了するまで待機
        file_info_impl info = future.get();

        // メタデータを取得
        m_number = info.info_get_int("tracknumber");
        m_title = info.info_get("title");
        m_artist = info.info_get("artist");
        m_album = info.info_get("album");
        m_albumArtist = info.info_get("album artist");
    }
}

TrackMetadata::TrackMetadata()
{
}

int TrackMetadata::GetNumber() const
{
    return m_number;
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

pfc::string8 TrackMetadata::GetAlbumArtist() const
{
    return m_albumArtist;
}

pfc::string8 TrackMetadata::ConvertToCSV() const
{
    auto appendField = [](pfc::string8& csv, const pfc::string8& field) {
        csv << (field.is_empty() ? pfc::string8("") : field) << ",";
    };

    pfc::string8 csv;
    csv << m_number << ",";
    appendField(csv, m_title);
    appendField(csv, m_artist);
    appendField(csv, m_album);
    appendField(csv, m_albumArtist);
    csv << "\n";  // 末尾に改行を追加

    return csv;
}
