#include "stdafx.h"
#include "HelloWorld.h"

void HelloWorld::display(metadb_handle_list_cref p_data) {
    for (size_t i = 0; i < p_data.get_count(); ++i) {
        metadb_handle_ptr handle = p_data[i];
        file_info_impl info;
        if (handle->get_info(info)) {
            console::printf("Title: %s", info.meta_get("TITLE", 0));
            console::printf("Artist: %s", info.meta_get("ARTIST", 0));
            console::printf("Album: %s", info.meta_get("ALBUM", 0));
            // 他のメタデータも同様に取得できます
        }
    }
    popup_message::g_show("Hello World", "Context Menu Command");
}