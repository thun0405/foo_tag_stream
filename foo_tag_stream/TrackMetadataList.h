#pragma once
#include "TrackMetadata.h"
#include <pfc/list.h>

class TrackMetadataList {
public:
    TrackMetadataList(metadb_handle_list_cref tracks);
    TrackMetadataList();

    void Add(const TrackMetadata& metadata);
    void RemoveAt(size_t index);
    const TrackMetadata& GetAt(size_t index) const;
    size_t GetCount() const;
    void ApplyToTracks(const metadb_handle_list& tracks);
    pfc::string8 ConvertToCsv() const;

private:
    pfc::list_t<TrackMetadata> m_list;
};
