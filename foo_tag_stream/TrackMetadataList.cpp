#include "stdafx.h"
#include "TrackMetadataList.h"
#include <SDK/file_info_filter_impl.h>

TrackMetadataList::TrackMetadataList(metadb_handle_list_cref tracks)
{
    for (size_t i = 0; i < tracks.get_count(); i++) {
        m_list.add_item(TrackMetadata(tracks[i]));
    }
}

TrackMetadataList::TrackMetadataList()
{
}

void TrackMetadataList::Add(const TrackMetadata& metadata) {
    m_list.add_item(metadata);
}

void TrackMetadataList::RemoveAt(size_t index) {
    m_list.remove_by_idx(index);
}

const TrackMetadata& TrackMetadataList::GetAt(size_t index) const {
    return m_list[index];
}

size_t TrackMetadataList::GetCount() const {
    return m_list.get_count();
}

void TrackMetadataList::ApplyToTracks(const metadb_handle_list& tracks) {
    if (tracks.get_count() != m_list.get_count()) {
        // �G���[����: �g���b�N�̐��ƃ��^�f�[�^�̐�����v���Ȃ��ꍇ
        return;
    }

    static_api_ptr_t<metadb_io_v2> api;

    pfc::list_t<const file_info*> newInfos;

    for (size_t i = 0; i < m_list.get_count(); ++i) {
        TrackMetadata& metadata = m_list[i];
        metadb_handle_ptr track = tracks[i];

        file_info_impl* newInfo = new file_info_impl();
        if (track->get_info_async(*newInfo)) {
            newInfo->meta_set("TITLE", metadata.GetTitle().get_ptr());
            newInfo->meta_set("ARTIST", metadata.GetArtist().get_ptr());
            newInfo->meta_set("ALBUM", metadata.GetAlbum().get_ptr());

            newInfos.add_item(newInfo);
        }
    }

    api->update_info_async(tracks, new service_impl_t<file_info_filter_impl>(tracks, newInfos), nullptr, metadb_io_v2::op_flag_delay_ui, nullptr);
}

pfc::string8 TrackMetadataList::ConvertToCsv() const
{
    pfc::string8 csv;

    // �w�b�_�[�s��ǉ�
    csv << "Number,Title,Artist,Album\n";

    // �e�g���b�N�̃��^�f�[�^��CSV�`���ɕϊ����Ēǉ�
    for (size_t i = 0; i < m_list.get_count(); ++i) {
        const TrackMetadata& metadata = m_list[i];
        csv << metadata.ConvertToCSV();
    }

    return csv;
}