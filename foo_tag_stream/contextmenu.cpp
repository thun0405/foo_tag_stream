#include "stdafx.h"
#include "Guids.h"
#include "PreviewDialog.h"
#include "MainDialog.h"
#include "MainWindow.h"

// Identifier of our context menu group. Substitute with your own when reusing code.
static contextmenu_group_popup_factory g_mygroup(guid_mygroup, contextmenu_groups::root, "Tag Stream", 0);

struct CommandInfo {
    const char* name;
    const char* description;
    GUID guid;
};

static const CommandInfo commands[] = {
    {
        "Main Dialog", 
        "This is the first command.", 
        guid_first 
    },
    { 
        "Preview Dialog",
        "This is the second command.", 
        guid_second 
    }
};

typedef void (*CommandFunc)(metadb_handle_list_cref p_data);

void FirstCommand(metadb_handle_list_cref p_data) {
    ShowMainDialog(p_data);
}

void SecondCommand(metadb_handle_list_cref p_data) {
    ShowPreviewDialog(p_data, "");
}

static CommandFunc commandFuncs[] = {
    FirstCommand,
    SecondCommand
};

class MyContextMenu : public contextmenu_item_simple {
protected:
    GUID get_parent() {
        return guid_mygroup;
    }

    unsigned get_num_items() override {
        return sizeof(commands) / sizeof(CommandInfo);
    }

    void get_item_name(unsigned index, pfc::string_base& out) override {
        out = commands[index].name;
    }

    void context_command(unsigned index, metadb_handle_list_cref p_data, const GUID& p_caller) override {
        commandFuncs[index](p_data);
    }

    GUID get_item_guid(unsigned index) override {
        return commands[index].guid;
    }

    bool get_item_description(unsigned index, pfc::string_base& out) override {
        out = commands[index].description;
        return true;
    }
};

static service_factory_single_t<MyContextMenu> g_helloWorldContextMenu;
