#include "gtk_menu.h"

/*
gboolean show_popup(GtkWidget *widget, GdkEvent *event)
{
            g_print ("show_popup 1.\n");
    const guint RIGHT_CLICK = 3;

    if (event->type == GDK_BUTTON_PRESS) {

        GdkEventButton *bevent = (GdkEventButton *) event;

        if (bevent->button == RIGHT_CLICK) {

            g_print ("show_popup - RIGHT_CLICK.\n");

            gtk_menu_popup(GTK_MENU(widget), NULL, NULL, NULL, NULL,
                bevent->button, bevent->time);
        }

        return TRUE;
    }

    return FALSE;
}
*/

GtkWidget *create_menubar (kwinst *app, GtkAccelGroup *mainaccel)
{
    GtkWidget *menubar;         /* menu container   */
    GtkWidget *fileMenu;        /* file menu        */
    GtkWidget *fileMi;
    GtkWidget *sep;
    GtkWidget *newMi;
    GtkWidget *openMi;
    GtkWidget *recentMi;
    GtkWidget *recentMenu;
    GtkWidget *reloadMi;
    GtkWidget *saveMi;
    GtkWidget *saveasMi;
    GtkWidget *pagesuMi;
    GtkWidget *printMi;
    GtkWidget *pprevMi;
    GtkWidget *closeMi;
    GtkWidget *quitMi;

    GtkWidget *editMenu;        /* edit menu        */
    GtkWidget *editMi;
    GtkWidget *undoMi;
    GtkWidget *redoMi;
    GtkWidget *copyMi;
    GtkWidget *cutMi;
    GtkWidget *pasteMi;
    GtkWidget *deleteMi;
    GtkWidget *selallMi;
    GtkWidget *deselectMi;
    GtkWidget *findMi;
    GtkWidget *replaceMi;
    GtkWidget *gotoMi;
    GtkWidget *prefsMi;

    GtkWidget *viewMenu;        /* view menu      */
    GtkWidget *viewMi;
    GtkWidget *fontMi;
    // GtkWidget *showmbMi;
    GtkWidget *showtbMi;
        GSList *tbgroup = NULL;
        GtkWidget *tbvisMenu;
        GtkWidget *tbappearMi;
        GtkWidget *tbtextMi;
        GtkWidget *tbiconsMi;
        GtkWidget *tbbothMi;
#ifdef HAVESOURCEVIEW
    GtkWidget *linenoMi;
    GtkWidget *linehlMi;
    GtkWidget *marginMi;
    GtkWidget *syntaxMi;
    GtkWidget *highlightMi;
    GtkWidget *highlightMenu;
    GtkWidget *synschemeMi;
    GtkWidget *synschemeMenu = NULL;
#endif
    GtkWidget *wordwrapMi;

    GtkWidget *statusMenu;      /* status menu      */
    GtkWidget *statusMi;
    GtkWidget *clearMi;
    GtkWidget *propsMi;
    GtkWidget *brbMi;   /* (Big Red Button) */

    GtkWidget *toolsMenu;       /* tools menu      */
    GtkWidget *toolsMi;
    GtkWidget *eoltitleMi;
        GSList    *eolgroup = NULL;
        GtkWidget *eolMenu;
//         GtkWidget *eolLFMi;
//         GtkWidget *eolCRLFMi;
//         GtkWidget *eolCRMi;
    GtkWidget *indentMi;
    GtkWidget *unindentMi;
    GtkWidget *indfixedMi;
    GtkWidget *undfixedMi;
    GtkWidget *insdtmMi;
    GtkWidget *insfileMi;
    GtkWidget *commentMi;
    GtkWidget *uncommentMi;
    GtkWidget *toupperMi;
    GtkWidget *tolowerMi;
    GtkWidget *totitleMi;
    GtkWidget *joinMi;

    GtkWidget *helpMenu;        /* help menu        */
    GtkWidget *helpMi;
    GtkWidget *aboutMi;

    /* create menubar, menus and submenus */
    menubar             = gtk_menu_bar_new ();
        fileMenu        = gtk_menu_new ();
            recentMenu  = gtk_recent_chooser_menu_new();
        editMenu        = gtk_menu_new ();
        viewMenu        = gtk_menu_new ();
            tbvisMenu   = gtk_menu_new ();
        statusMenu      = gtk_menu_new ();
        toolsMenu       = gtk_menu_new ();
            eolMenu     = gtk_menu_new ();
        helpMenu        = gtk_menu_new ();

#ifdef HAVESOURCEVIEW
    highlightMenu = highlight_build_menu (app);
    synschemeMenu = sourceview_syntax_styles_menu (synschemeMenu, app);
#endif

    /* define filter for recentMenu for text files */
    GtkRecentFilter *filter = gtk_recent_filter_new ();
#ifndef HAVEMSWIN
    gtk_recent_filter_set_name (filter, "Text");
    gtk_recent_filter_add_mime_type (filter, "text/plain");
#else
    /* Add a filter that will display all of the files in the dialog. */
    gtk_recent_filter_set_name (filter, "All Files");
    gtk_recent_filter_add_pattern (filter, "*");
#endif
    /* set to choose most recently used files and full-path tips */
    gtk_recent_chooser_set_sort_type (GTK_RECENT_CHOOSER(recentMenu),
                                    GTK_RECENT_SORT_MRU);
    gtk_recent_chooser_set_filter (GTK_RECENT_CHOOSER(recentMenu), filter);
    gtk_recent_chooser_set_show_tips (GTK_RECENT_CHOOSER(recentMenu), TRUE);
    gtk_recent_chooser_set_local_only (GTK_RECENT_CHOOSER (recentMenu), TRUE);

    /* define file menu */
    fileMi = gtk_menu_item_new_with_mnemonic ("_File");
    sep = gtk_separator_menu_item_new ();
    newMi    = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW,
                                                   NULL);
    openMi   = gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN,
                                                   NULL);
    recentMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_DND_MULTIPLE,
                                                   NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (recentMi), "Open _Recent File");
    saveMi   = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE,
                                                   NULL);
    saveasMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE_AS,
                                                   NULL);
    reloadMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_REFRESH,
                                                   NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (reloadMi), "R_eload Saved File");
    pagesuMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_PAGE_SETUP,
                                                   NULL);
    pprevMi  = gtk_image_menu_item_new_from_stock (GTK_STOCK_PRINT_PREVIEW,
                                                   NULL);
    printMi  = gtk_image_menu_item_new_from_stock (GTK_STOCK_PRINT,
                                                   NULL);
    closeMi  = gtk_image_menu_item_new_from_stock (GTK_STOCK_CLOSE,
                                                   NULL);
    quitMi   = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT,
                                                   NULL);

    /* create entries under 'File' then add to menubar */
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (fileMi), fileMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), sep);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), newMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), openMi);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM (recentMi), recentMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), recentMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), saveMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), saveasMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), reloadMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), pagesuMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), pprevMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), printMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), closeMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), quitMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (menubar), fileMi);

    gtk_widget_add_accelerator (newMi, "activate", mainaccel,
                                GDK_KEY_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (openMi, "activate", mainaccel,
                                GDK_KEY_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
//     gtk_widget_add_accelerator (recentMi, "activate", mainaccel,
//                                 GDK_KEY_o, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
//                                 GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (reloadMi, "activate", mainaccel,
                                GDK_KEY_F5, 0, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (saveMi, "activate", mainaccel,
                                GDK_KEY_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (saveasMi, "activate", mainaccel,
                                GDK_KEY_s, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (pagesuMi, "activate", mainaccel,
                                GDK_KEY_p, GDK_MOD1_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (pprevMi, "activate", mainaccel,
                                GDK_KEY_p, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (printMi, "activate", mainaccel,
                                GDK_KEY_p, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (closeMi, "activate", mainaccel,
                                GDK_KEY_w, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (quitMi, "activate", mainaccel,
                                GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

    /* define edit menu */
    editMi = gtk_menu_item_new_with_mnemonic ("_Edit");
    sep = gtk_separator_menu_item_new ();
    undoMi     = gtk_image_menu_item_new_from_stock (GTK_STOCK_UNDO,
                                                    NULL);
    redoMi     = gtk_image_menu_item_new_from_stock (GTK_STOCK_REDO,
                                                    NULL);
    copyMi     = gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY,
                                                    NULL);
    cutMi      = gtk_image_menu_item_new_from_stock (GTK_STOCK_CUT,
                                                    NULL);
    pasteMi    = gtk_image_menu_item_new_from_stock (GTK_STOCK_PASTE,
                                                    NULL);
    deleteMi   = gtk_image_menu_item_new_from_stock (GTK_STOCK_DELETE,
                                                    NULL);
    selallMi   = gtk_image_menu_item_new_from_stock (GTK_STOCK_ZOOM_FIT,
                                                    NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (selallMi), "_Select _All");

    deselectMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_CLEAR,
                                                    NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (deselectMi), "_Deselect All");

    findMi     = gtk_image_menu_item_new_from_stock (GTK_STOCK_FIND,
                                                    NULL);
    replaceMi  = gtk_image_menu_item_new_from_stock (GTK_STOCK_FIND_AND_REPLACE,
                                                    NULL);
    gotoMi     = gtk_image_menu_item_new_from_stock (GTK_STOCK_INDEX,
                                                    NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (gotoMi), "_Go to Line");

    prefsMi    = gtk_image_menu_item_new_from_stock (GTK_STOCK_PREFERENCES,
                                                    NULL);

    /* create entries under 'Edit' then add to menubar */
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (editMi), editMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), sep);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), undoMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), redoMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), copyMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), cutMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), pasteMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), deleteMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), selallMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), deselectMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), findMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), replaceMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), gotoMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (editMenu), prefsMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (menubar), editMi);

    gtk_widget_add_accelerator (undoMi, "activate", mainaccel,
                                GDK_KEY_z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (redoMi, "activate", mainaccel,
                                GDK_KEY_z, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (copyMi, "activate", mainaccel,
                                GDK_KEY_c, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (cutMi, "activate", mainaccel,
                                GDK_KEY_x, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (pasteMi, "activate", mainaccel,
                                GDK_KEY_v, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (selallMi, "activate", mainaccel,
                                GDK_KEY_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (deselectMi, "activate", mainaccel,
                                GDK_KEY_a, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (findMi, "activate", mainaccel,
                                GDK_KEY_f, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (replaceMi, "activate", mainaccel,
                                GDK_KEY_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (gotoMi, "activate", mainaccel,
                                GDK_KEY_g, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (prefsMi, "activate", mainaccel,
                                GDK_KEY_p, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);

    /* define view menu */
    viewMi = gtk_menu_item_new_with_mnemonic ("_View");
    sep = gtk_separator_menu_item_new ();
    fontMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_SELECT_FONT,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (fontMi), "_Font Selection");
//     showmbMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_PROPERTIES,
//                                                    NULL);
//     gtk_menu_item_set_label (GTK_MENU_ITEM (showmbMi), "Show/Hide _Menubar");
    showtbMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_CONVERT,
                                                   NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (showtbMi), "_Show/Hide Toolbar");
        /* toolbar appearance submenu */
        tbappearMi = gtk_menu_item_new_with_mnemonic ("Toolbar _Appearance");
        app->tbappearMi = tbappearMi;
        tbtextMi = gtk_radio_menu_item_new_with_mnemonic (tbgroup, "_Text Only");
        tbgroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (tbtextMi));
        tbiconsMi = gtk_radio_menu_item_new_with_mnemonic (tbgroup, "_Icons Only");
        tbgroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (tbiconsMi));
        gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (tbiconsMi), TRUE);
        tbbothMi = gtk_radio_menu_item_new_with_mnemonic (tbgroup, "_Both Text & Icons");
        tbgroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (tbbothMi));
//         tbtextMi = gtk_menu_item_new_with_mnemonic ("_Text Only");
//         tbiconsMi = gtk_menu_item_new_with_mnemonic ("_Icons Only");
//         tbbothMi = gtk_menu_item_new_with_mnemonic ("_Both Text & Icons");
#ifdef HAVESOURCEVIEW
    marginMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_GOTO_LAST,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (marginMi), "Show/Hide Right _Margin");
    linehlMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_INDEX,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (linehlMi), "_Current Line Highlight");
    syntaxMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_SELECT_COLOR,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (syntaxMi), "Syntax _Highlight  (on/off)");

    highlightMi = gtk_menu_item_new_with_mnemonic ("_Syntax Language");

    synschemeMi = gtk_menu_item_new_with_mnemonic ("S_yntax Styles");
    linenoMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_EDIT,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (linenoMi), "Line _Numbers");
#endif
    wordwrapMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_JUSTIFY_FILL,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (wordwrapMi), "_Word Wrap (on/off)");

    /* create entries under 'View' then add to menubar */
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (viewMi), viewMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), sep);
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), fontMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu),
                           gtk_separator_menu_item_new());
//     gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), showmbMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), showtbMi);

        /* toolbar appearance submenu */
        gtk_menu_item_set_submenu (GTK_MENU_ITEM (tbappearMi), tbvisMenu);
        gtk_menu_shell_append (GTK_MENU_SHELL (tbvisMenu), tbtextMi);
        gtk_menu_shell_append (GTK_MENU_SHELL (tbvisMenu), tbiconsMi);
        gtk_menu_shell_append (GTK_MENU_SHELL (tbvisMenu), tbbothMi);

    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), tbappearMi);
#ifdef HAVESOURCEVIEW
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), marginMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), linehlMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), syntaxMi);
    if (highlightMenu) {
        gtk_menu_item_set_submenu (GTK_MENU_ITEM (highlightMi), highlightMenu);
        gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), highlightMi);
    }
    if (synschemeMenu) {
        gtk_menu_item_set_submenu (GTK_MENU_ITEM (synschemeMi), synschemeMenu);
        gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), synschemeMi);
    }
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), linenoMi);
#endif
    gtk_menu_shell_append (GTK_MENU_SHELL (viewMenu), wordwrapMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (menubar), viewMi);

    gtk_widget_add_accelerator (viewMi, "activate", mainaccel,
                                GDK_KEY_v, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (fontMi, "activate", mainaccel,
                                GDK_KEY_t, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
//     gtk_widget_add_accelerator (showmbMi, "activate", mainaccel,
//                                 GDK_KEY_m, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (showtbMi, "activate", mainaccel,
                                GDK_KEY_t, GDK_CONTROL_MASK,
                                GTK_ACCEL_VISIBLE);
#ifdef HAVESOURCEVIEW
    gtk_widget_add_accelerator (marginMi, "activate", mainaccel,
                                GDK_KEY_m, GDK_CONTROL_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (linehlMi, "activate", mainaccel,
                                GDK_KEY_h, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (syntaxMi, "activate", mainaccel,
                                GDK_KEY_h, GDK_MOD1_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (linenoMi, "activate", mainaccel,
                                GDK_KEY_F11, 0, GTK_ACCEL_VISIBLE);
#endif
    gtk_widget_add_accelerator (wordwrapMi, "activate", mainaccel,
                                GDK_KEY_F12, 0, GTK_ACCEL_VISIBLE);

    /* define status menu */
    statusMi = gtk_menu_item_new_with_mnemonic ("_Status");
    sep = gtk_separator_menu_item_new ();

    clearMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_CLEAR,
                                                  NULL);
    brbMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_MEDIA_RECORD,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (brbMi), "_Big Red Button...");

    /* create entries under 'Status' then add to menubar */
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (statusMi), statusMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (statusMenu), sep);
    /* disabled clear for now */
    // gtk_menu_shell_append (GTK_MENU_SHELL (statusMenu), clearMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (statusMenu),
                           gtk_separator_menu_item_new());
    // gtk_menu_shell_append (GTK_MENU_SHELL (statusMenu), brbMi);
    /*
     * Hide Status Menu until it is populated with line count,
     * char count, etc.
     */
    // gtk_menu_shell_append (GTK_MENU_SHELL (menubar), statusMi);

    gtk_widget_add_accelerator (clearMi, "activate", mainaccel,
                                GDK_KEY_c, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);

    /* define tools menu */
    toolsMi = gtk_menu_item_new_with_mnemonic ("_Tools");
    sep = gtk_separator_menu_item_new ();

        /* eol appearance submenu */
        eoltitleMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_GO_FORWARD,
                                                        NULL);
        gtk_menu_item_set_label (GTK_MENU_ITEM (eoltitleMi), "End of Line _Selection");
        // eoltitleMi = gtk_menu_item_new_with_mnemonic ("End Of Line _Selection");
        app->eolLFMi = gtk_radio_menu_item_new_with_mnemonic (eolgroup, "_Linux / Unix / OSX");
        eolgroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (app->eolLFMi));
        app->eolCRLFMi = gtk_radio_menu_item_new_with_mnemonic (eolgroup, "DOS / _Windows");
        eolgroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (app->eolCRLFMi));
        app->eolCRMi = gtk_radio_menu_item_new_with_mnemonic (eolgroup, "_Macintosh (pre-OSX)");
        eolgroup = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (app->eolCRMi));
        if (app->eol == LF)
            gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (app->eolLFMi), TRUE);
        else if (app->eol == CRLF)
            gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (app->eolCRLFMi), TRUE);
        else
            gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (app->eolCRMi), TRUE);
    indentMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_INDENT,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (indentMi), "Incr_ease Indent");
    unindentMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_UNINDENT,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (unindentMi), "_Decrease Indent");
    indfixedMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_INDENT,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (indfixedMi), "Indent _Fixed Width");
    undfixedMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_UNINDENT,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (undfixedMi), "Unindent Fixed _Width");
    insdtmMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_EDIT,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (insdtmMi), "Insert Date/Ti_me at Cursor...");
    insfileMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (insfileMi), "_Insert File at Cursor...");
    commentMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_STRIKETHROUGH,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (commentMi), "_Comment");
    uncommentMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_UNDERLINE,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (uncommentMi), "U_ncomment");
    toupperMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_GO_UP,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (toupperMi), "_Uppercase");
    tolowerMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_GO_DOWN,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (tolowerMi), "_Lowercase");
    totitleMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_GO_FORWARD,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (totitleMi), "_Titlecase");
    joinMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_ADD,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (joinMi), "_Join Lines");
    propsMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_PROPERTIES,
                                                  NULL);
    gtk_menu_item_set_label (GTK_MENU_ITEM (propsMi), "_Word/Char Statistics");

    /* create entries under 'Tools' then add to menubar */
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (toolsMi), toolsMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), sep);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM (eoltitleMi), eolMenu);
        gtk_menu_shell_append (GTK_MENU_SHELL (eolMenu), app->eolLFMi);
        gtk_menu_shell_append (GTK_MENU_SHELL (eolMenu), app->eolCRLFMi);
        gtk_menu_shell_append (GTK_MENU_SHELL (eolMenu), app->eolCRMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), eoltitleMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), indentMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), unindentMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), indfixedMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), undfixedMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), insfileMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), insdtmMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), commentMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), uncommentMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), toupperMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), tolowerMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), totitleMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), joinMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (menubar), toolsMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu),
                           gtk_separator_menu_item_new());
    gtk_menu_shell_append (GTK_MENU_SHELL (toolsMenu), propsMi);

    gtk_widget_add_accelerator (indentMi, "activate", mainaccel,
                                GDK_KEY_i, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (unindentMi, "activate", mainaccel,
                                GDK_KEY_i, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
#ifndef HAVEMSWIN
/** TODO FIXME - GDK_SUPER_MASK 'i' as 'ctrl+i'.
 *  gurads added to prevent assignment of
 *  GDK_SUPER_MASK causing 'i' to be interpreted
 *  as 'ctrl+i' on mswin
 */
    gtk_widget_add_accelerator (indfixedMi, "activate", mainaccel,
                                GDK_KEY_i, GDK_SUPER_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (undfixedMi, "activate", mainaccel,
                                GDK_KEY_i, GDK_SUPER_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
#endif
    gtk_widget_add_accelerator (insdtmMi, "activate", mainaccel,
                                GDK_KEY_t, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (commentMi, "activate", mainaccel,
                                GDK_KEY_d, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (uncommentMi, "activate", mainaccel,
                                GDK_KEY_d, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (toupperMi, "activate", mainaccel,
                                GDK_KEY_u, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (tolowerMi, "activate", mainaccel,
                                GDK_KEY_l, GDK_CONTROL_MASK,
                                GTK_ACCEL_VISIBLE);
    /* tolowerMi accel changed to allow key-code insertion of Unicode chars
     *                             GDK_KEY_u, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
     */
    gtk_widget_add_accelerator (totitleMi, "activate", mainaccel,
                                GDK_KEY_u, GDK_MOD1_MASK | GDK_SHIFT_MASK,
                                GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (joinMi, "activate", mainaccel,
                                GDK_KEY_j, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator (propsMi, "activate", mainaccel,
                                GDK_KEY_r, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);

    /*define help menu */
    helpMi = gtk_menu_item_new_with_mnemonic ("_Help");
    gtk_menu_item_set_right_justified ((GtkMenuItem *)helpMi, TRUE);
    sep = gtk_separator_menu_item_new ();
    aboutMi = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT,
                                                  NULL);

    /* create entries under 'Help' then add to menubar */
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (helpMi), helpMenu);
    gtk_menu_shell_append (GTK_MENU_SHELL (helpMenu), sep);
    gtk_menu_shell_append (GTK_MENU_SHELL (helpMenu), aboutMi);
    gtk_menu_shell_append (GTK_MENU_SHELL (menubar), helpMi);

    gtk_widget_add_accelerator (aboutMi, "activate", mainaccel,
                                GDK_KEY_a, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);

    /* File Menu */
    g_signal_connect (G_OBJECT (newMi), "activate",         /* file New     */
                      G_CALLBACK (menu_file_new_activate), app);

    g_signal_connect (G_OBJECT (openMi), "activate",        /* file Open    */
                      G_CALLBACK (menu_file_open_activate), app);

    g_signal_connect (G_OBJECT (recentMenu), "item-activated", /* file Open    */
                      G_CALLBACK (menu_file_open_recent_activate), app);

    g_signal_connect (G_OBJECT (reloadMi), "activate",         /* file Run     */
                      G_CALLBACK (menu_file_reload_activate), app);

    g_signal_connect (G_OBJECT (saveMi), "activate",        /* file Save    */
                      G_CALLBACK (menu_file_save_activate), app);

    g_signal_connect (G_OBJECT (saveasMi), "activate",      /* file SaveAs  */
                      G_CALLBACK (menu_file_saveas_activate), app);

    g_signal_connect (G_OBJECT (pagesuMi), "activate",        /* file Quit    */
                      G_CALLBACK (menu_file_pagesu_activate), app);

    g_signal_connect (G_OBJECT (pprevMi), "activate",        /* file Quit    */
                      G_CALLBACK (menu_file_pprev_activate), app);

    g_signal_connect (G_OBJECT (printMi), "activate",        /* file Quit    */
                      G_CALLBACK (menu_file_print_activate), app);

    g_signal_connect (G_OBJECT (closeMi), "activate",        /* file Quit    */
                      G_CALLBACK (menu_file_close_activate), app);

    g_signal_connect (G_OBJECT (quitMi), "activate",        /* file Quit    */
                      G_CALLBACK (menu_file_quit_activate), app);
    /* Edit Menu */
    g_signal_connect (G_OBJECT (undoMi), "activate",         /* edit Copy   */
                      G_CALLBACK (menu_edit_undo_activate), app);

    g_signal_connect (G_OBJECT (redoMi), "activate",         /* edit Cut     */
                      G_CALLBACK (menu_edit_redo_activate), app);

    g_signal_connect (G_OBJECT (copyMi), "activate",         /* edit Copy   */
                      G_CALLBACK (menu_edit_copy_activate), app);

    g_signal_connect (G_OBJECT (cutMi), "activate",         /* edit Cut     */
                      G_CALLBACK (menu_edit_cut_activate), app);

    g_signal_connect (G_OBJECT (pasteMi), "activate",       /* edit Paste   */
                      G_CALLBACK (menu_edit_paste_activate), app);

    g_signal_connect (G_OBJECT (deleteMi), "activate",      /* edit Delete  */
                      G_CALLBACK (menu_edit_delete_activate), app);

    g_signal_connect (G_OBJECT (selallMi), "activate",      /* edit sel all */
                      G_CALLBACK (menu_edit_selectall_activate), app);

    g_signal_connect (G_OBJECT (deselectMi), "activate",      /* edit sel all */
                      G_CALLBACK (menu_edit_deselectall_activate), app);

    g_signal_connect (G_OBJECT (findMi), "activate",        /* edit Find    */
                      G_CALLBACK (menu_edit_find_activate), app);

    g_signal_connect (G_OBJECT (replaceMi), "activate",     /* edit Replace */
                      G_CALLBACK (menu_edit_replace_activate), app);

    g_signal_connect (G_OBJECT (gotoMi), "activate",        /* edit Goto */
                      G_CALLBACK (menu_edit_goto_activate), app);

    g_signal_connect (G_OBJECT (prefsMi), "activate",       /* stat Prefs   */
                      G_CALLBACK (menu_edit_preferences_activate), app);
    /* View Menu */
    g_signal_connect (G_OBJECT (fontMi), "activate",        /* font select  */
                      G_CALLBACK (menu_font_select_activate), app);

//     g_signal_connect (G_OBJECT (showmbMi), "activate",      /* show toolbar */
//                       G_CALLBACK (menu_showmb_activate), app);

    g_signal_connect (G_OBJECT (showtbMi), "activate",      /* show toolbar */
                      G_CALLBACK (menu_showtb_activate), app);

    g_signal_connect (G_OBJECT (tbtextMi), "activate",      /* tb submenu   */
                      G_CALLBACK (menu_tbshow_text_activate), app);

    g_signal_connect (G_OBJECT (tbiconsMi), "activate",     /* tb submenu   */
                      G_CALLBACK (menu_tbshow_icons_activate), app);

    g_signal_connect (G_OBJECT (tbbothMi), "activate",      /* tb submenu   */
                      G_CALLBACK (menu_tbshow_both_activate), app);
#ifdef HAVESOURCEVIEW
    g_signal_connect (G_OBJECT (linehlMi), "activate",      /* line hglight */
                      G_CALLBACK (menu_view_linehl_activate), app);

    g_signal_connect (G_OBJECT (marginMi), "activate",      /* show margin  */
                      G_CALLBACK (menu_view_margin_activate), app);

    g_signal_connect (G_OBJECT (linenoMi), "activate",      /* line numbers */
                      G_CALLBACK (menu_view_lineno_activate), app);
#endif
    g_signal_connect (G_OBJECT (wordwrapMi), "activate",    /* word wrap    */
                      G_CALLBACK (menu_view_wordwrap_activate), app);

    /* Status Menu */
    g_signal_connect (G_OBJECT (clearMi), "activate",       /* stat Clear   */
                      G_CALLBACK (menu_status_clear_activate), app);

    g_signal_connect (G_OBJECT (propsMi), "activate",       /* stat Props   */
                      G_CALLBACK (menu_status_properties_activate), app);

    g_signal_connect (G_OBJECT (brbMi), "activate",         /* stat Props   */
                      G_CALLBACK (menu_status_bigredbtn_activate), app);

    /* Tools Menu */
    g_signal_connect (G_OBJECT (app->eolLFMi), "activate",       /* EOL types    */
                      G_CALLBACK (menu_tools_eol_lf), app);

    g_signal_connect (G_OBJECT (app->eolCRLFMi), "activate",     /* EOL types    */
                      G_CALLBACK (menu_tools_eol_crlf), app);

    g_signal_connect (G_OBJECT (app->eolCRMi), "activate",       /* EOL types    */
                      G_CALLBACK (menu_tools_eol_cr), app);

    g_signal_connect (G_OBJECT (indentMi), "activate",      /* tools indent */
                      G_CALLBACK (menu_tools_indent_activate), app);

    g_signal_connect (G_OBJECT (unindentMi), "activate",    /* unindent     */
                      G_CALLBACK (menu_tools_unindent_activate), app);

    g_signal_connect (G_OBJECT (indfixedMi), "activate",      /* tools indent */
                      G_CALLBACK (menu_tools_indent_fixed_activate), app);

    g_signal_connect (G_OBJECT (undfixedMi), "activate",      /* tools indent */
                      G_CALLBACK (menu_tools_unindent_fixed_activate), app);

#ifdef HAVESOURCEVIEW
    g_signal_connect (G_OBJECT (syntaxMi), "activate",      /* unindent     */
                      G_CALLBACK (menu_tools_syntax_activate), app);
#endif

    g_signal_connect (G_OBJECT (insdtmMi), "activate",     /* insert date  */
                      G_CALLBACK (menu_tools_insdtm_activate), app);

    g_signal_connect (G_OBJECT (insfileMi), "activate",     /* insert file  */
                      G_CALLBACK (menu_tools_insfile_activate), app);

    g_signal_connect (G_OBJECT (commentMi), "activate",     /* comment code */
                      G_CALLBACK (menu_tools_comment_activate), app);

    g_signal_connect (G_OBJECT (uncommentMi), "activate",   /* uncomment    */
                      G_CALLBACK (menu_tools_uncomment_activate), app);

    g_signal_connect (G_OBJECT (toupperMi), "activate",     /* to uppercase */
                      G_CALLBACK (menu_tools_toupper_activate), app);

    g_signal_connect (G_OBJECT (tolowerMi), "activate",     /* to lowercase */
                      G_CALLBACK (menu_tools_tolower_activate), app);

    g_signal_connect (G_OBJECT (totitleMi), "activate",     /* to titlecase */
                      G_CALLBACK (menu_tools_totitle_activate), app);

    g_signal_connect (G_OBJECT (joinMi), "activate",        /* to titlecase */
                      G_CALLBACK (menu_tools_join_activate), app);

    /* Help Menu */
    g_signal_connect (G_OBJECT (aboutMi), "activate",       /* help About   */
                      G_CALLBACK (menu_help_about_activate), app);

    /* modified menu in container - popup works, but menu doesn't */
//     app->menubar = menubar;
//     gtk_widget_show_all(evbox);
//     return evbox;
    /* original */
    return (app->menubar = menubar);
}


/*
 * menu callback functions
 *
 *  _File menu
 */
void menu_file_new_activate (GtkMenuItem *menuitem, kwinst *app)
{
    /* spawn new instance of editor
     * TODO: omit parsing keyfile on new instance of editor if possible
     */
    if (!create_new_editor_inst (app, NULL)) {
        /* clear current file, use current window if spawn fails */
        buffer_clear (app);         /* check for save and clear  */
        status_set_default (app);   /* statusbard default values */

        /* dialog advising of failure and consequences */
        gchar *msg = g_strdup_printf ("Error: failed to spawn separate\n"
                                    "instance of %s\n", app->exename);
        dlg_info_win (app, msg, "Error - Unable to Create 2nd Instance");
        g_free (msg);
    }

    if (menuitem) {}
}

void menu_file_open_activate (GtkMenuItem *menuitem, kwinst *app)
{
    /* get new filename */
    gchar *newfile = get_open_filename (app);

    /* open newfile in current or new editor instance */
    file_open (app, newfile);

    if (menuitem) {}
}

void menu_file_open_recent_activate (GtkRecentChooser *chooser, kwinst *app)
{
    /* get uri from selected chooser item */
    gchar *uri = gtk_recent_chooser_get_current_uri (chooser);
    gchar *p, *filename;

    /* get filename from uri and allocate/copy filename */
    // p = uri_to_filename (uri);
    p = g_filename_from_uri (uri, NULL, NULL);
    filename = g_strdup (p);

    /* open newfile in current or new editor instance */
    file_open (app, filename);
}

void menu_file_reload_activate (GtkMenuItem *menuitem, kwinst *app)
{
    if (!app->filename) {
        /* TODO: error dialog */
        return;
    }

    /* TODO: create  buffer_reload_file() and move code there */

    /* clear exising buffer, insert saved file, set modified to FALSE
     * set title.
     */
    gtk_text_buffer_set_text (GTK_TEXT_BUFFER(app->buffer), "", -1);

    /* insert saved file into buffer */
    buffer_insert_file (app, NULL);
    gtk_text_buffer_set_modified (GTK_TEXT_BUFFER(app->buffer), FALSE);
    gtkwrite_window_set_title (NULL, app);

    /* don't move status operations */
    status_menuitem_label (menuitem, app);

    gtk_widget_grab_focus (app->view);
}

void menu_file_save_activate (GtkMenuItem *menuitem, kwinst *app)
{
    buffer_save_file (app, NULL);
    gtk_widget_grab_focus (app->view);

    if (menuitem) {}
}

void menu_file_saveas_activate (GtkMenuItem *menuitem, kwinst *app)
{
    gchar *filename = NULL;

    filename = get_save_filename (app);
    if (filename)
        buffer_save_file (app, filename);
    else
        show_info_bar_ok ("Warning: Save of File Canceled!",
                            GTK_MESSAGE_INFO, app);
        // dlg_info ("Warning: Save of File Canceled!", "SAVE CANCELED!");

    gtk_widget_grab_focus (app->view);

    if (menuitem) {}
}

void menu_file_pagesu_activate (GtkMenuItem *menuitem, kwinst *app)
{
    do_page_setup (app);

    if (menuitem) {}
    if (app) {}
}

void menu_file_pprev_activate (GtkMenuItem *menuitem, kwinst *app)
{
    dlg_info ("NOTICE:\n\nPrint-preview Capabilities\nare currently provided by your\n"
                "native 'Print' dialog and may\nvary from system to system.",
                "Under Construction");
    if (menuitem) {}
    if (app) {}
}

void menu_file_print_activate (GtkMenuItem *menuitem, kwinst *app)
{
    // dlg_info ("NOTICE: Print Capabilities\n\nUnder Construction.",
    //             "Under Construction");

    do_print(app);

    if (menuitem) {}
    if (app) {}
}

void menu_file_close_activate (GtkMenuItem *menuitem, kwinst *app)
{
    buffer_clear (app);     /* check for save and clear */

    if (menuitem) {}
}

void menu_file_quit_activate (GtkMenuItem *menuitem, kwinst *app)
{
    if (!app->winszsaved) { /* user chose save current size in settings */
        /* get window size */
        gtk_window_get_size (GTK_WINDOW (app->window), &(app->winwidth),
                            &(app->winheight));
    }

    /* check changed, prompt yes/no, apply buffer cleanups */
    ibar_handle_quit (app);
    // buffer_handle_quit (app);
    // gtk_main_quit ();

    if (menuitem) {}
}

/*
 *  _Edit menu
 */
void menu_edit_undo_activate (GtkMenuItem *menuitem, kwinst *app)
{
#ifdef HAVESOURCEVIEW
    if (gtk_source_buffer_can_undo (app->buffer))
        gtk_source_buffer_undo (app->buffer);
    else
        show_info_bar_markup_ok ("Unable to undo previous operation.",
                                GTK_MESSAGE_INFO, app);
        // err_dialog ("Error:\n\nUnable to undo previous operation.");
#else
    if (app) {}
#endif
    gtkwrite_window_set_title (NULL, app);

    if (menuitem) {}
}

void menu_edit_redo_activate (GtkMenuItem *menuitem, kwinst *app)
{
#ifdef HAVESOURCEVIEW
    if (gtk_source_buffer_can_redo (app->buffer))
        gtk_source_buffer_redo (app->buffer);
    else
        show_info_bar_markup_ok ("Unable to redo previous operation.",
                                GTK_MESSAGE_INFO, app);
        // err_dialog ("Error:\n\nUnable to redo previous operation.");
#else
    if (app) {}
#endif

    if (menuitem) {}
}

void menu_edit_copy_activate (GtkMenuItem *menuitem, kwinst *app)
{
    GtkTextBuffer *buffer;
    GtkClipboard *clipboard;

    clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app->view));
    gtk_text_buffer_copy_clipboard (buffer, clipboard);

    if (menuitem) {}
}

void menu_edit_cut_activate (GtkMenuItem *menuitem, kwinst *app)
{
    GtkTextBuffer *buffer;
    GtkClipboard *clipboard;

    clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app->view));
    gtk_text_buffer_cut_clipboard (buffer, clipboard, TRUE);

    if (menuitem) {}
}

void menu_edit_paste_activate (GtkMenuItem *menuitem, kwinst *app)
{
    GtkTextBuffer *buffer;
    GtkClipboard *clipboard;

    clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app->view));
    gtk_text_buffer_paste_clipboard (buffer, clipboard, NULL, TRUE);

    if (menuitem) {}
}

void menu_edit_delete_activate (GtkMenuItem *menuitem, kwinst *app)
{
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app->view));
    gtk_text_buffer_delete_selection (buffer, FALSE, TRUE);

    if (menuitem) {}
}

void menu_edit_selectall_activate (GtkMenuItem *menuitem, kwinst *app)
{
    buffer_select_all (app);
    if (menuitem) {}
    if (app) {}
}

void menu_edit_deselectall_activate (GtkMenuItem *menuitem, kwinst *app)
{
    buffer_deselect_all (app);
    if (menuitem) {}
    if (app) {}
}

void menu_edit_find_activate (GtkMenuItem *menuitem, kwinst *app)
{
    create_find_dlg (app);
    if (menuitem) {}
    if (app) {}
}

void menu_edit_replace_activate (GtkMenuItem *menuitem, kwinst *app)
{
    create_replace_dlg (app);
    if (menuitem) {}
    if (app) {}
}

void menu_edit_goto_activate (GtkMenuItem *menuitem, kwinst *app)
{
    create_goto_dlg (app);
    // g_print ("menu_edit_goto_activate callback\n");
    if (menuitem) {}
    // if (app) {}
}

void menu_edit_preferences_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_update_str (app, "Edit : Preferences");
    create_settings_dlg (app);
    if (menuitem) {}
    if (app) {}
}

/*
 *  _View menu
 */
void menu_font_select_activate (GtkMenuItem *menuitem, kwinst *app)
{
    font_select_dialog (GTK_WIDGET (menuitem), app);

    if (menuitem) {}
    if (app) {}
}

// void menu_showmb_activate (GtkMenuItem *menuitem, kwinst *app)
// {
//         gtk_widget_set_visible (app->menubar,
//                                 gtk_widget_get_visible (app->menubar) ?
//                                 FALSE : TRUE);
//     if (menuitem) {}
// }

void menu_showtb_activate (GtkMenuItem *menuitem, kwinst *app)
{
    app->showtoolbar = gtk_widget_get_visible (app->toolbar) ? FALSE : TRUE;
    gtk_widget_set_visible (app->toolbar, app->showtoolbar);
    gtk_widget_set_sensitive (app->tbappearMi, app->showtoolbar);
//     gtk_widget_set_visible (app->toolbar,
//                             gtk_widget_get_visible (app->toolbar) ?
//                             FALSE : TRUE);
    if (menuitem) {}
}

void menu_tbshow_text_activate (GtkMenuItem *menuitem, kwinst *app)
{
    gtk_toolbar_set_style(GTK_TOOLBAR(app->toolbar), GTK_TOOLBAR_TEXT);
    if (menuitem) {}
}

void menu_tbshow_icons_activate (GtkMenuItem *menuitem, kwinst *app)
{
    gtk_toolbar_set_style(GTK_TOOLBAR(app->toolbar), GTK_TOOLBAR_ICONS);
    if (menuitem) {}
}

void menu_tbshow_both_activate (GtkMenuItem *menuitem, kwinst *app)
{
    gtk_toolbar_set_style(GTK_TOOLBAR(app->toolbar), GTK_TOOLBAR_BOTH);
    if (menuitem) {}
}
#ifdef HAVESOURCEVIEW
void menu_view_linehl_activate (GtkMenuItem *menuitem, kwinst *app)
{
    app->linehghlt = app->linehghlt ? FALSE : TRUE;

    gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW(app->view),
                                                app->linehghlt);

    if (menuitem) {}
}

void menu_view_margin_activate (GtkMenuItem *menuitem, kwinst *app)
{
    app->showmargin = app->showmargin ? FALSE : TRUE;

    gtk_source_view_set_show_right_margin (GTK_SOURCE_VIEW (app->view),
                                            app->showmargin);

    if (menuitem) {}
}

void menu_view_lineno_activate (GtkMenuItem *menuitem, kwinst *app)
{
 #ifdef DEBUG
    g_print ("line numbers are: %s\n", app->lineno ? "ON" : "OFF");
 #endif

    app->lineno = app->lineno ? FALSE : TRUE;   /* toggle value */
    gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW(app->view),
                                            app->lineno);

 #ifdef DEBUG
    g_print ("line numbers now: %s\n", app->lineno ? "ON" : "OFF");
 #endif
    if (menuitem) {}
}
#endif

void menu_view_wordwrap_activate (GtkMenuItem *menuitem, kwinst *app)
{
    app->dynwrap = app->dynwrap ? FALSE : TRUE;
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (app->view),
            app->dynwrap ? GTK_WRAP_WORD : GTK_WRAP_NONE);

    if (menuitem) {}
}

/*
 *  _Status menu
 */
void menu_status_clear_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
}

/* moved to end of tools menu until status menu filled out */
void menu_status_properties_activate (GtkMenuItem *menuitem, kwinst *app)
{
    // propcb (GTK_WIDGET (menuitem), app);
    // dlg_info ("Currently unused test callback.", "Unused Test Callback");
//     buffer_content_stats (GTK_TEXT_BUFFER(app->buffer));
    buffer_content_stats (app);
    if (menuitem) {}
    if (app) {}
}

void menu_status_bigredbtn_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
    // selection_dump (GTK_TEXT_BUFFER(app->buffer), dump2lower);
    /* default if nothing being tested */
    err_dialog ("Note:  Noting currently hooked to Big Red Button...");
}


/*
 *  _Tools menu
 */

/** helper function for each end-of-line convert callback */
void tools_eol_handle_convert (GtkMenuItem *menuitem, kwinst *app)
{
#ifdef DEBUGEOL
    g_print ("%s -- Activated\n", gtk_menu_item_get_label (menuitem));
#else
    if (menuitem) {}
#endif
    if (app->eol != app->oeol) {

        /* if eolchg set after file load or
         * new file and buffer modified
         */
        if (app->eolchg || app->modified) {

#ifdef DEBUGEOL
            g_print ("  %s != %s && (eolchg || modified) -- converting\n",
                    app->eolnm[app->eol], app->eolnm[app->oeol]);
#endif
            /* convert eol from app->oeol => app->eol */
            buffer_convert_eol (app);
        }
        else {
#ifdef DEBUGEOL
            g_print ("  Neither (app->eolchg || app->modified) -- skipping\n");
#endif
        }

        /* set app->oeol = app->eol; here! */
        app->oeol = app->eol;
    }
#ifdef DEBUGEOL
    else {
        g_print ("  %s == %s || !eolchg -- skipping\n",
                app->eolnm[app->eol], app->eolnm[app->oeol]);
    }
#endif
}

/** set end-of-line to LF and convert all line-ends to LF */
void menu_tools_eol_lf (GtkMenuItem *menuitem, kwinst *app)
{
#ifdef DEBUGEOL
    g_print ("%s - called.\n", gtk_menu_item_get_label (menuitem));
#endif

    /* if menuitem is being Activated - set eol, handle convert */
    if (gtk_check_menu_item_get_active (GTK_CHECK_MENU_ITEM(menuitem))) {
        app->eol = LF;
        tools_eol_handle_convert (menuitem, app);
    }

#ifdef DEBUGEOL
    else {
        g_print ("%s -- Deactived, skipping\n", gtk_menu_item_get_label (menuitem));
    }
#endif

    status_set_default (app);
}

/** set end-of-line to CRLF and convert all line-ends to CRLF */
void menu_tools_eol_crlf (GtkMenuItem *menuitem, kwinst *app)
{
#ifdef DEBUGEOL
    g_print ("%s - called.\n", gtk_menu_item_get_label (menuitem));
#endif

    /* if menuitem is being Activated - set eol, handle convert */
    if (gtk_check_menu_item_get_active (GTK_CHECK_MENU_ITEM(menuitem))) {
        app->eol = CRLF;
        tools_eol_handle_convert (menuitem, app);
    }

#ifdef DEBUGEOL
    else {
        g_print ("%s -- Deactived, skipping\n", gtk_menu_item_get_label (menuitem));
    }
#endif

    status_set_default (app);
}

/** set end-of-line to CR and convert all line-ends to CR */
void menu_tools_eol_cr (GtkMenuItem *menuitem, kwinst *app)
{
#ifdef DEBUGEOL
    g_print ("%s - called.\n", gtk_menu_item_get_label (menuitem));
#endif

    /* if menuitem is being Activated - set eol, handle convert */
    if (gtk_check_menu_item_get_active (GTK_CHECK_MENU_ITEM(menuitem))) {
        app->eol = CR;
        tools_eol_handle_convert (menuitem, app);
    }

#ifdef DEBUGEOL
    else {
        g_print ("%s -- Deactived, skipping\n", gtk_menu_item_get_label (menuitem));
    }
#endif

    status_set_default (app);
}

void menu_tools_indent_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
    GtkTextIter start, end;
    gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(app->buffer), &start, &end);
    buffer_indent_lines (app, &start, &end);

}

void menu_tools_unindent_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
    GtkTextIter start, end;
    gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(app->buffer), &start, &end);
    buffer_unindent_lines (app, &start, &end);
    if (menuitem) {}
    if (app) {}
}

void menu_tools_indent_fixed_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
    GtkTextIter start, end;
    gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(app->buffer), &start, &end);
    buffer_indent_lines_fixed (app, &start, &end);

}

void menu_tools_unindent_fixed_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
    GtkTextIter start, end;
    gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(app->buffer), &start, &end);
    buffer_unindent_lines_fixed (app, &start, &end);

}

#ifdef HAVESOURCEVIEW
void menu_tools_syntax_activate (GtkMenuItem *menuitem, kwinst *app)
{
    if (app->language) {    /* if set, toggle show/hide */

        if (app->highlight)
            app->highlight = FALSE;
        else
            app->highlight = TRUE;

        gtk_source_buffer_set_highlight_syntax (app->buffer, app->highlight);
    }
    else {
        // app->highlight = TRUE;
        // sourceview_guess_language (app);
        dlg_info ("Note:\n\nNo filename set.\nSyntax highlight guess currently "
                "depends on filename.\n\nSave file to activate highlighting.",
                "Syntax Highlighting Requires Filename");
    }

    status_pop (GTK_WIDGET (menuitem), app);
}
#endif

void menu_tools_insdtm_activate (GtkMenuItem *menuitem, gpointer data)
{
    kwinst *app = (kwinst*)data;
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(app->buffer);
    gchar *dtm = get_local_datetime();

    gtk_text_buffer_insert_at_cursor (buffer, dtm, -1);

    g_free (dtm);

    if (menuitem) {}
}

void menu_tools_insfile_activate (GtkMenuItem *menuitem, kwinst *app)
{
    gchar *filename = NULL;
    status_pop (GTK_WIDGET (menuitem), app);
    buffer_file_insert_dlg (app, filename);
}

void menu_tools_comment_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
    GtkTextIter start, end;
    gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(app->buffer), &start, &end);
    buffer_comment_lines (app, &start, &end);
    if (menuitem) {}
}

void menu_tools_uncomment_activate (GtkMenuItem *menuitem, kwinst *app)
{
    status_pop (GTK_WIDGET (menuitem), app);
    GtkTextIter start, end;
    gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(app->buffer), &start, &end);
    buffer_uncomment_lines (app, &start, &end);
    if (menuitem) {}
}

void menu_tools_toupper_activate (GtkMenuItem *menuitem, kwinst *app)
{
    selection_for_each_char (GTK_TEXT_BUFFER(app->buffer), str2upper);
    if (menuitem) {}
}

void menu_tools_tolower_activate (GtkMenuItem *menuitem, kwinst *app)
{
    selection_for_each_char (GTK_TEXT_BUFFER(app->buffer), str2lower);
    if (menuitem) {}
}

void menu_tools_totitle_activate (GtkMenuItem *menuitem, kwinst *app)
{
    selection_for_each_char (GTK_TEXT_BUFFER(app->buffer), str2title);
    if (menuitem) {}
}

void menu_tools_join_activate (GtkMenuItem *menuitem, kwinst *app)
{
    selection_for_each_char (GTK_TEXT_BUFFER(app->buffer), joinlines);
    if (menuitem) {}
}

/*
 *  _Help menu
 */
void menu_help_about_activate (GtkMenuItem *menuitem, kwinst *app)
{
    help_about (app);
    if (menuitem) {}
}

/*
 * general window functions
 */

void help_about (kwinst *app)
{
    gchar *buf, *logofn, *license;
    gsize fsize;
    GdkPixbuf *logo = NULL;

    static const gchar *const authors[] = {
            "David C. Rankin, J.D,P.E. <drankinatty@gmail.com>",
            NULL
    };

    static const gchar copyright[] = \
            "Copyright \xc2\xa9 2019 David C. Rankin";

    static const gchar comments[] = APPSTR;

    /* create pixbuf from logofn to pass to show_about_dialog */
//     if ((logofn = get_logo_filename (app))) {
    if ((logofn = g_strdup_printf ("%s/%s", app->imgdir, LOGO))) {
        // g_print ("logofn : '%s'\n", logofn);
        logo = create_pixbuf_from_file (logofn);
        g_free (logofn);
    }

#ifndef HAVEMSWIN
    /* Archlinux */
    license = g_strdup_printf ("%s/%s/%s", "/usr/share/licenses", CFGDIR, LICENSE);
    if (g_file_test (license, G_FILE_TEST_EXISTS))
        goto gotnixlic;

    /* openSuSE */
    g_free (license);
    license = NULL;
    license = g_strdup_printf ("%s/%s/%s", "/usr/share/doc/packages", CFGDIR, LICENSE);
    if (g_file_test (license, G_FILE_TEST_EXISTS))
        goto gotnixlic;

    /* generic */
    g_free (license);
    license = NULL;
    license = g_strdup_printf ("%s/%s", app->sysdatadir, LICENSE);

    gotnixlic:;
#else
    /* win32/win64 */
    license = g_strdup_printf ("%s\\%s", app->sysdatadir, LICENSE);
#endif

    /* check if license read into buf */
    if (g_file_get_contents (license, &buf, &fsize, NULL)) {

        if (logo)   /* show logo */
            gtk_show_about_dialog (GTK_WINDOW (app->window),
                                "authors", authors,
                                "comments", comments,
                                "copyright", copyright,
                                "version", VER,
                                "website", SITE,
                                "program-name", APPSTR,
                                "logo", logo,
                                "license", buf,
                                NULL);
        else    /* show stock GTK_STOCK_EDIT */
            gtk_show_about_dialog (GTK_WINDOW (app->window),
                                "authors", authors,
                                "comments", comments,
                                "copyright", copyright,
                                "version", VER,
                                "website", SITE,
                                "program-name", APPSTR,
                                "logo-icon-name", GTK_STOCK_EDIT,
                                "license", buf,
                                NULL);
        g_free (buf);
    }
    else {
#ifdef DEBUG
        g_print ("error: load of file %s failed.\n", LICENSE);
#endif
        if (logo)   /* show logo */
            gtk_show_about_dialog (GTK_WINDOW (app->window),
                                "authors", authors,
                                "comments", comments,
                                "copyright", copyright,
                                "version", VER,
                                "website", SITE,
                                "program-name", APPSTR,
                                "logo", logo,
                                NULL);
        else    /* show stock GTK_STOCK_EDIT */
            gtk_show_about_dialog (GTK_WINDOW (app->window),
                                "authors", authors,
                                "comments", comments,
                                "copyright", copyright,
                                "version", VER,
                                "website", SITE,
                                "program-name", APPSTR,
                                "logo-icon-name", GTK_STOCK_EDIT,
                                NULL);
    }

    if (logo)
        g_object_unref (logo);
    if (license)
        g_free (license);
}
