#include "gtk_common_dlg.h"

/** general use err_dialog, just pass errmsg. */
void err_dialog (const gchar *errmsg)
{
    GtkWidget *dialog;

    g_warning (errmsg); /* log to terminal window */

    /* create an error dialog and display modally to the user */
    dialog = gtk_message_dialog_new (NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    errmsg);

    gtk_window_set_title (GTK_WINDOW (dialog), "Error!");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

/** general use err_dialog, just pass errmsg. */
void err_dialog_win (gpointer *data, const gchar *errmsg)
{
    kwinst *app = (kwinst *)data;
    GtkWidget *dialog;

    g_warning (errmsg); /* log to terminal window */

    /* create an error dialog and display modally to the user */
    dialog = gtk_message_dialog_new (GTK_WINDOW (app->window),
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    errmsg);

    gtk_window_set_title (GTK_WINDOW (dialog), "Error!");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

/** font_select_dialog used to set textview font.
 *  create a new pango font description and calls
 *  gtk_widget_modify_font to set textview font.
 */
void font_select_dialog (GtkWidget *widget, kwinst *app)
{
    GtkResponseType result;

    GtkWidget *dialog = gtk_font_selection_dialog_new ("Select Font");

    /* set initial font name if (!wanted) use default */
    if (!gtk_font_selection_dialog_set_font_name (
            GTK_FONT_SELECTION_DIALOG (dialog), app->fontname))
        gtk_font_selection_dialog_set_font_name (
            GTK_FONT_SELECTION_DIALOG (dialog), "Monospace 8");

    result = gtk_dialog_run (GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY) {

        if (app->fontname) g_free (app->fontname);

        PangoFontDescription *font_desc;
        app->fontname = gtk_font_selection_dialog_get_font_name (
                                GTK_FONT_SELECTION_DIALOG (dialog));

        if (!app->fontname) {
            err_dialog ("error: invalid font returned.");
            return;
        }

        font_desc = pango_font_description_from_string (app->fontname);

        gtk_widget_modify_font (app->view, font_desc);
        pango_font_description_free (font_desc);
    }
    gtk_widget_destroy (dialog);

    if (widget) {}  /* stub */
}

void buffer_file_insert_dlg (kwinst *app, gchar *filename)
{
    GtkWidget *dialog;

    /* Create a new file chooser widget */
    dialog = gtk_file_chooser_dialog_new ("Select a file for editing",
					  // parent_window,
					  GTK_WINDOW (app->window),
					  GTK_FILE_CHOOSER_ACTION_OPEN,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					  NULL);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        buffer_insert_file (app, filename);
    }

    gtk_widget_destroy (dialog);
}

void buffer_file_open_dlg (kwinst *app, gchar *filename)
{
    GtkWidget *dialog;

    /* Create a new file chooser widget */
    dialog = gtk_file_chooser_dialog_new ("Select a file for editing",
					  // parent_window,
					  GTK_WINDOW (app->window),
					  GTK_FILE_CHOOSER_ACTION_OPEN,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					  NULL);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        app->filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        split_fname (app);
        buffer_insert_file (app, NULL);
    }

    gtk_widget_destroy (dialog);
    if (filename) {}
}

/* Removed until upstream bug fixed
 * see: https://bugzilla.gnome.org/show_bug.cgi?id=779605
 */
void file_open_recent_dlg (kwinst *app)
{
    GtkWidget *dialog;
    GtkRecentManager *manager;
    GtkRecentFilter *filter;

    manager = gtk_recent_manager_get_default ();
    dialog = gtk_recent_chooser_dialog_new_for_manager ("Recent Documents",
                                            GTK_WINDOW (app->window),
                                            manager,
                                            GTK_STOCK_CANCEL,
                                            GTK_RESPONSE_CANCEL,
                                            GTK_STOCK_OPEN,
                                            GTK_RESPONSE_ACCEPT,
                                            NULL);

    /* Add a filter that will only display plain text files.
     * note: the first filter defined is displayed by default.
     */
#ifndef HAVEMSWIN
    filter = gtk_recent_filter_new ();
    gtk_recent_filter_set_name (filter, "Plain Text");
    gtk_recent_filter_add_mime_type (filter, "text/plain");
    gtk_recent_chooser_add_filter (GTK_RECENT_CHOOSER (dialog), filter);
#endif
    /* Add a filter that will display all of the files in the dialog. */
    filter = gtk_recent_filter_new ();
    gtk_recent_filter_set_name (filter, "All Files");
    gtk_recent_filter_add_pattern (filter, "*");
    gtk_recent_chooser_add_filter (GTK_RECENT_CHOOSER (dialog), filter);

    /* set to choose most recently used files */
    gtk_recent_chooser_set_show_not_found (GTK_RECENT_CHOOSER (dialog),
                                           FALSE);
    gtk_recent_chooser_set_sort_type (GTK_RECENT_CHOOSER (dialog),
                                      GTK_RECENT_SORT_MRU);
    gtk_recent_chooser_set_limit (GTK_RECENT_CHOOSER (dialog), 30);
    gtk_recent_chooser_set_show_tips (GTK_RECENT_CHOOSER(dialog), TRUE);
    gtk_recent_chooser_set_local_only (GTK_RECENT_CHOOSER (dialog), TRUE);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        GtkRecentInfo *info;
        const gchar *uri;
        gchar *filename;

        info = gtk_recent_chooser_get_current_item (GTK_RECENT_CHOOSER (dialog));
        /* compare with gtk_recent_chooser_get_current_uri
         * (you can use uri_to_filename here, but g_filename_from_uri is fine )
         */
        uri = gtk_recent_info_get_uri (info);
        // filename = uri_to_filename (gtk_recent_info_get_uri (info));
        if (uri) {
            filename = g_filename_from_uri (uri, NULL, NULL);
            file_open (app, filename);
            g_free (filename);
        }
        else
            err_dialog_win ((gpointer *)(app), "uri_to_filename () returned NULL");
        gtk_recent_info_unref (info);
    }
    gtk_widget_destroy (dialog);
}

void dlg_info (const gchar *msg, const gchar *title)
{
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new (NULL,
                                    GTK_DIALOG_MODAL |
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_CLOSE,
                                    msg);

    gtk_window_set_title (GTK_WINDOW (dialog), title);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void dlg_info_win (gpointer data, const gchar *msg, const gchar *title)
{
    kwinst *app = (kwinst *)data;
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new (GTK_WINDOW (app->window),
                                    GTK_DIALOG_MODAL |
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_CLOSE,
                                    msg);

    gtk_window_set_title (GTK_WINDOW (dialog), title);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

gboolean dlg_yes_no_msg (gpointer data, const gchar *msg, const gchar *title,
                            gboolean default_return)
{
    GtkWidget *window = data ? ((kwinst *)data)->window : NULL;
    gboolean ret = default_return ? TRUE : FALSE;
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new (GTK_WINDOW (window),
                                    GTK_DIALOG_MODAL |
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_YES_NO,
                                    msg);

    gtk_window_set_title (GTK_WINDOW (dialog), title);
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_NO)
    {
        ret = FALSE;    /* don't save */
    }
    else ret = TRUE;    /* save */

    gtk_widget_destroy (dialog);

    return ret;
}

gboolean buffer_prompt_on_mod (kwinst *app)
{
    gboolean ret = FALSE;
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app->view));

    if (gtk_text_buffer_get_modified (buffer) == TRUE)
    {
        GtkWidget *dialog;

        const gchar *msg  = "Do you want to save the changes you have made?";

        dialog = gtk_message_dialog_new (NULL,
                                         GTK_DIALOG_MODAL |
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_QUESTION,
                                         GTK_BUTTONS_YES_NO,
                                         msg);

        gtk_window_set_title (GTK_WINDOW (dialog), "Save?");
        if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_NO)
        {
            ret = FALSE;    /* don't save */
        }
        else ret = TRUE;    /* save */

        gtk_widget_destroy (dialog);
    }

    return ret;
}

gchar *get_open_filename (kwinst *app)
{
    GtkWidget *chooser;
    gchar *filename=NULL;

    chooser = gtk_file_chooser_dialog_new ("Open File...",
                                            GTK_WINDOW (app->window),
                                            GTK_FILE_CHOOSER_ACTION_OPEN,
                                            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                            GTK_STOCK_OPEN, GTK_RESPONSE_OK,
                                            NULL);

    if (app->filename) {
#ifdef DEBUG
        g_print ("get_open_filename() app->fpath: %s\napp->filename: %s\n",
                app->fpath, app->filename);
#endif
        /* set current file path beginning choice */
        gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(chooser),
                                            app->fpath);
        /* set current filename beginning choice */
        gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(chooser),
                                        app->filename);
    }

    if (gtk_dialog_run (GTK_DIALOG (chooser)) == GTK_RESPONSE_OK)
    {
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
    }
    gtk_widget_destroy (chooser);

    return filename;
}

gchar *get_save_filename (kwinst *app)
{
    GtkWidget *chooser;
    gchar *filename = NULL;

    chooser = gtk_file_chooser_dialog_new ("Save File...",
                                            GTK_WINDOW (app->window),
                                            GTK_FILE_CHOOSER_ACTION_SAVE,
                                            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                            GTK_STOCK_SAVE, GTK_RESPONSE_OK,
                                            NULL);

    gtk_file_chooser_set_create_folders (GTK_FILE_CHOOSER(chooser), TRUE);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(chooser),
                                                    TRUE);
    if (app->filename) {
        /* set current file path beginning choice */
        gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(chooser),
                                            app->fpath);
        /* set current filename beginning choice */
        gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(chooser),
                                        app->filename);
    }

    if (gtk_dialog_run (GTK_DIALOG (chooser)) == GTK_RESPONSE_OK)
    {
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
    }
    gtk_widget_destroy (chooser);

    return filename;
}
