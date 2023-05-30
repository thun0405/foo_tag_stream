#include "stdafx.h"

#include "HelloWorld.h"
#include "ui_dialog.h"


// Identifier of our context menu group. Substitute with your own when reusing code.
static const GUID guid_mygroup = { 0x143c290c, 0xf390, 0x4a7f, { 0xb6, 0x64, 0x5, 0xa, 0x35, 0x74, 0x67, 0xa } };


// Switch to contextmenu_group_factory to embed your commands in the root menu but separated from other commands.

//static contextmenu_group_factory g_mygroup(guid_mygroup, contextmenu_groups::root, 0);
static contextmenu_group_popup_factory g_mygroup(guid_mygroup, contextmenu_groups::root, "Tag Stream", 0);

class MyContextMenu : public contextmenu_item_simple {
protected:
    enum {
        cmd_first,
        cmd_second,
        cmd_count
    };

    GUID get_parent() {
        return guid_mygroup;
    }

    unsigned get_num_items() override {
        return cmd_count;
    }

    void get_item_name(unsigned index, pfc::string_base& out) override {
        switch (index) {
        case cmd_first:
            out = "First command";
            break;
        case cmd_second:
            out = "Second command";
            break;
        }
    }

    void context_command(unsigned index, metadb_handle_list_cref p_data, const GUID& p_caller) override {
        switch (index) {
        case cmd_first:
            // Do something for the first command
            HelloWorld helloWorld;
            helloWorld.display(p_data);
            break;
        case cmd_second:
            // Do something for the second command
            ShowMyDialog();
            break;
        }
    }

    GUID get_item_guid(unsigned index) override {
        // Return a unique GUID for each command
        // These GUIDs are just examples and should be replaced with your own GUIDs
        static const GUID guid_first = { 0x1dffe8fa, 0xe579, 0x4c0f, { 0x83, 0xfe, 0xce, 0xa2, 0x4b, 0xe4, 0xb6, 0x21 } };
        static const GUID guid_second = { 0x730f4408, 0x27d, 0x40e6, { 0xa0, 0xea, 0x8b, 0xf0, 0x19, 0x50, 0x1d, 0xb5 } };

        switch (index) {
        case cmd_first:
            return guid_first;
        case cmd_second:
            return guid_second;
        default:
            return pfc::guid_null;
        }
    }

    bool get_item_description(unsigned index, pfc::string_base& out) override {
        switch (index) {
        case cmd_first:
            out = "This is the first command.";
            return true;
        case cmd_second:
            out = "This is the second command.";
            return true;
        default:
            return false;
        }
    }
};

static service_factory_single_t<MyContextMenu> g_helloWorldContextMenu;
