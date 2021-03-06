#include <config.h>
#include <gtk/gtk.h>

#include <glib/gi18n.h>
#include "window_defs_n_config.h"


static int init_system_admin_window = 0;
static int init_sys_admin_diag_window = 0;
static int init_sys_admin_theme_window = 0;
static int init_client_admin_window = 0;
GtkBuilder *SystemAdminBuilder, *AdminDiagnosticsBuilder, *AdminThemesBuilder, *ClientAdminBuilder;

void admin_exit_btnclicked(GtkWidget *widget, gpointer user_data){
	hide_window_system_admin ();
	show_window_login ();
}
void admin_station_diagnostics_btnclicked(GtkWidget *widget, gpointer user_data){
	hide_window_system_admin ();
	show_window_system_admin_diagnostics ();
}
void admin_edit_threshold_btnclicked(GtkWidget *widget, gpointer user_data){
	
}
void admin_edit_system_themes_btnclicked(GtkWidget *widget, gpointer user_data){
	hide_window_system_admin ();
	show_window_system_admin_themes ();
}
void admin_access_transaction_files_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_connect_pc_btnclicked(GtkWidget *widget, gpointer user_data){

}

void admin_diag_body_fat_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_diag_ethernet_connectivity_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_diag_smoking_status_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_diag_exit_btnclicked(GtkWidget *widget, gpointer user_data){
	hide_window_system_admin_diagnostics ();
	show_window_system_admin ();
}
void admin_diag_weight_bmi_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_diag_blood_pressure_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_diag_gprs_connectivity_btnclicked(GtkWidget *widget, gpointer user_data){

}

void admin_theme_exit_btnclicked(GtkWidget *widget, gpointer user_data){
	hide_window_system_admin_themes ();
	show_window_system_admin ();
}
void admin_theme_edit_clnt_logo_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_theme_login_mode_btnclicked(GtkWidget *widget, gpointer user_data){

}
void admin_theme_user_feedback_btnclicked(GtkWidget *widget, gpointer user_data){

}


void clnt_admin_setup_new_user_btnclicked(GtkWidget *widget, gpointer user_data){

}
void clnt_admin_reports_trends_btnclicked(GtkWidget *widget, gpointer user_data){

}
void clnt_admin_send_grp_msg_btnclicked(GtkWidget *widget, gpointer user_data){

}
void clnt_admin_exit_btnclicked(GtkWidget *widget, gpointer user_data){
	hide_window_client_admin ();
	show_window_login ();
}
static GtkWidget*
create_system_admin_window (void)
{
	GtkWidget *window, *button1, *button2, *button3, *button4, *button5, *button6; 
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG;

	GError** error = NULL;
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (SystemAdminBuilder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, SYSTEM_ADMIN_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				SYSTEM_ADMIN_WINDOW,
				SYSTEM_ADMIN_UI_FILE);
        }

	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);

	//GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);


	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ADDS2, error);
	GtkImage *adds = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(adds), pixbufaddanm);
	

	
	button1 = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "exit"));
 	 g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (admin_exit_btnclicked),
                    NULL);

	//profileBtnClickedFrom = test2_pro_btn;
	button2 = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "station_diagnostics"));
 	 g_signal_connect (G_OBJECT (button2), "clicked",
                    G_CALLBACK (admin_station_diagnostics_btnclicked),
                    NULL);
	
	button3 = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "edit_thresholds"));
 	 g_signal_connect (G_OBJECT (button3), "clicked",
                    G_CALLBACK (admin_edit_threshold_btnclicked),
                    NULL);

	button4 = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "edit_system_themes"));
 	 g_signal_connect (G_OBJECT (button4), "clicked",
                    G_CALLBACK (admin_edit_system_themes_btnclicked),
                    NULL);

	button5 = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "access_transaction_files"));
 	 g_signal_connect (G_OBJECT (button5), "clicked",
                    G_CALLBACK (admin_access_transaction_files_btnclicked),
                    NULL);

	button6 = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, "connect_pc"));
 	 g_signal_connect (G_OBJECT (button6), "clicked",
                    G_CALLBACK (admin_connect_pc_btnclicked),
                    NULL);
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_system_admin()
{
	GtkWidget *window;
	if(!init_system_admin_window) {
		   GError *error=NULL;
		SystemAdminBuilder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (SystemAdminBuilder, SYSTEM_ADMIN_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_system_admin_window ();
		init_system_admin_window = 1;
	}
	window = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, SYSTEM_ADMIN_WINDOW));
	gtk_widget_show(window);
	cur_active_screen = system_admin_scrn;
}

void hide_window_system_admin()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (SystemAdminBuilder, SYSTEM_ADMIN_WINDOW));
	gtk_widget_hide(window);
}


static GtkWidget*
create_system_admin_diagnostics_window (void)
{
	GtkWidget *window, *button1, *button2, *button3, *button4, *button5, *button6, *button7; 
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG;

	GError** error = NULL;
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (AdminDiagnosticsBuilder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, SYS_ADMIN_DIAG_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				SYS_ADMIN_DIAG_WINDOW,
				SYS_ADMIN_DIAG_UI_FILE);
        }

	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);

	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	GdkPixbufAnimation * pixbuft1anm = gdk_pixbuf_animation_new_from_file(HM_NEXT_ICON , error);
	GtkImage *image1 = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "image2"));
	gtk_image_set_from_animation(GTK_IMAGE(image1), pixbuft1anm);
	GdkPixbufAnimation * pixbuft2anm = gdk_pixbuf_animation_new_from_file(T1_NEXT_ICON , error);
	GtkImage *image2 = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "image3"));
	gtk_image_set_from_animation(GTK_IMAGE(image2), pixbuft2anm);
	GdkPixbufAnimation * pixbuft3anm = gdk_pixbuf_animation_new_from_file(T2_NEXT_ICON , error);
	GtkImage *image3 = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "image5"));
	gtk_image_set_from_animation(GTK_IMAGE(image3), pixbuft3anm);
	GdkPixbufAnimation * pixbuft4anm = gdk_pixbuf_animation_new_from_file(T3_NEXT_ICON , error);
	GtkImage *image4 = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "image4"));
	gtk_image_set_from_animation(GTK_IMAGE(image4), pixbuft4anm);
	
	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ADDS2, error);
	GtkImage *adds = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(adds), pixbufaddanm);
	

	
	button1 = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "exit"));
 	 g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (admin_diag_exit_btnclicked),
                    NULL);

	//profileBtnClickedFrom = test2_pro_btn;
	button2 = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "weight_n_bmi"));
 	 g_signal_connect (G_OBJECT (button2), "clicked",
                    G_CALLBACK (admin_diag_weight_bmi_btnclicked),
                    NULL);
	
	button3 = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "blood_pressure"));
 	 g_signal_connect (G_OBJECT (button3), "clicked",
                    G_CALLBACK (admin_diag_blood_pressure_btnclicked),
                    NULL);

	button4 = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "gprs_connectivity"));
 	 g_signal_connect (G_OBJECT (button4), "clicked",
                    G_CALLBACK (admin_diag_gprs_connectivity_btnclicked),
                    NULL);

	button5 = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "body_fat"));
 	 g_signal_connect (G_OBJECT (button5), "clicked",
                    G_CALLBACK (admin_diag_body_fat_btnclicked),
                    NULL);

	button6 = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "ethernet_connectivity"));
 	 g_signal_connect (G_OBJECT (button6), "clicked",
                    G_CALLBACK (admin_diag_ethernet_connectivity_btnclicked),
                    NULL);

	button7 = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, "smoking_status"));
 	 g_signal_connect (G_OBJECT (button6), "clicked",
                    G_CALLBACK (admin_diag_smoking_status_btnclicked),
                    NULL);
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_system_admin_diagnostics()
{
	GtkWidget *window;
	if(!init_sys_admin_diag_window) {
		   GError *error=NULL;
		AdminDiagnosticsBuilder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (AdminDiagnosticsBuilder, SYS_ADMIN_DIAG_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_system_admin_diagnostics_window ();
		init_sys_admin_diag_window = 1;
	}
	window = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, SYS_ADMIN_DIAG_WINDOW));
	gtk_widget_show(window);
	cur_active_screen = system_admin_diagnostic_scrn;
}

void hide_window_system_admin_diagnostics()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (AdminDiagnosticsBuilder, SYS_ADMIN_DIAG_WINDOW));
	gtk_widget_hide(window);
}



static GtkWidget*
create_system_admin_themes_window (void)
{
	GtkWidget *window, *button1, *button2, *button3, *button4, *button5, *button6; 
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG;

	GError** error = NULL;
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (AdminThemesBuilder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, SYS_ADMIN_THEMES_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				SYS_ADMIN_THEMES_WINDOW,
				SYS_ADMIN_THEME_UI_FILE);
        }

	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);

	//GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);


	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ADDS2, error);
	GtkImage *adds = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(adds), pixbufaddanm);
	

	
	button1 = GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "exit"));
 	 g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (admin_theme_exit_btnclicked),
                    NULL);

	//profileBtnClickedFrom = test2_pro_btn;
	button2 = GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "edit_clnt_logo"));
 	 g_signal_connect (G_OBJECT (button2), "clicked",
                    G_CALLBACK (admin_theme_edit_clnt_logo_btnclicked),
                    NULL);
	
	button3 = GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "login_mode"));
 	 g_signal_connect (G_OBJECT (button3), "clicked",
                    G_CALLBACK (admin_theme_login_mode_btnclicked),
                    NULL);

	button4 = GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, "user_feedback"));
 	 g_signal_connect (G_OBJECT (button4), "clicked",
                    G_CALLBACK (admin_theme_user_feedback_btnclicked),
                    NULL);
	
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_system_admin_themes()
{
	GtkWidget *window;
	if(!init_sys_admin_theme_window) {
		   GError *error=NULL;
		AdminThemesBuilder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (AdminThemesBuilder, SYS_ADMIN_THEME_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_system_admin_themes_window ();
		init_sys_admin_theme_window = 1;
	}
	window = GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, SYS_ADMIN_THEMES_WINDOW));
	gtk_widget_show(window);
	cur_active_screen = system_admin_theme_scrn;
}

void hide_window_system_admin_themes()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (AdminThemesBuilder, SYS_ADMIN_THEMES_WINDOW));
	gtk_widget_hide(window);
}


static GtkWidget*
create_client_admin_window (void)
{
	GtkWidget *window, *button1, *button2, *button3, *button4, *button5, *button6; 
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG;

	GError** error = NULL;
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (ClientAdminBuilder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, CLIENT_ADMIN_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				CLIENT_ADMIN_WINDOW,
				CLIENT_ADMIN_UI_FILE);
        }

	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);

	//GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);


	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ADDS2, error);
	GtkImage *adds = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(adds), pixbufaddanm);
	

	
	button1 = GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "exit"));
 	 g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (clnt_admin_exit_btnclicked),
                    NULL);

	//profileBtnClickedFrom = test2_pro_btn;
	button2 = GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "send_group_msg"));
 	 g_signal_connect (G_OBJECT (button2), "clicked",
                    G_CALLBACK (clnt_admin_send_grp_msg_btnclicked),
                    NULL);
	
	button3 = GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "reports_n_trends"));
 	 g_signal_connect (G_OBJECT (button3), "clicked",
                    G_CALLBACK (clnt_admin_reports_trends_btnclicked),
                    NULL);

//	button4 = GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, "setup_new_user"));
 //	 g_signal_connect (G_OBJECT (button4), "clicked",
   //                 G_CALLBACK (clnt_admin_setup_new_user_btnclicked),
     //               NULL);
	
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_client_admin()
{
	GtkWidget *window;
	if(!init_sys_admin_theme_window) {
		   GError *error=NULL;
		ClientAdminBuilder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (ClientAdminBuilder, CLIENT_ADMIN_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_client_admin_window ();
		init_client_admin_window = 1;
	}
	window = GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, CLIENT_ADMIN_WINDOW));
	gtk_widget_show(window);
	cur_active_screen = client_admin_scrn;
}

void hide_window_client_admin()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (ClientAdminBuilder, CLIENT_ADMIN_WINDOW));
	gtk_widget_hide(window);
}
