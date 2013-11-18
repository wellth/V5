#include <config.h>
#include <gtk/gtk.h>

#include <glib/gi18n.h>
#include <string.h>
#include "window_defs_n_config.h"
#include "main_test_backend.h"

static int init_test3_window = 0, init_test3_b_window = 0;
GtkWidget *t3_normal_smsg1, *t3_normal_smsg2;
GtkWidget *t3_result_smsg1, *t3_result_smsg2;
GtkBuilder *Test3Builder, *Test3bBuilder;
static GtkWidget *button1, *button2, *button3, *button4, *button5, *home_button; 
GtkWidget * CoLevelLabel, *test3_msg;
unsigned char COTestEn = 0;
_WT_IN_FILE InText;

#if 0
gboolean _label_update(gpointer data)
{
    GtkLabel *label = (GtkLabel*)data;
    	char buf[256];
	if(sec_expired == 0){
		memset(&buf, 0x0, 256);
		snprintf(buf, 255, "%d", sec_expired);
		gtk_label_set_label(label, buf);
	}
	if(start_timer) { 
		memset(&buf, 0x0, 256);
		snprintf(buf, 255, "%d", ++sec_expired);
		gtk_label_set_label(label, buf);
		if(sec_expired > 2500){
			sec_expired = 0;
			start_timer = 0;
			hide_measure_btn_show_repeate_btn();
		}
	} else {
		sec_expired = 0;
	}
	
	return continue_timer;
}

void _start_timer (GtkWidget *button, gpointer data)
{
    (void)button;/*Avoid compiler warnings*/
    GtkWidget *label = data;
   //if(!start_timer)
    {
        //g_timeout_add_seconds(1, _label_update, label);
		g_timeout_add(1, _label_update, label);
        start_timer = TRUE;
        continue_timer = TRUE;
    }
}
#endif

void test3_button_set_state(int bool_val){
	gtk_widget_set_sensitive(button1, bool_val);
	gtk_widget_set_sensitive(button2, bool_val);
	gtk_widget_set_sensitive(button3, bool_val);
	if(bool_val == FALSE)
		disable_test3_repeate();
	gtk_widget_set_sensitive(button5, bool_val);

	GtkWidget *feed_back;
	if(bool_val == TRUE){
		feed_back = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "label9"));
		gtk_label_set_label (feed_back, "Please wait upto sensor is ready");
	}
}

void enable_test3_repeate(){
	GtkWidget *feed_back;
	gtk_widget_set_sensitive(button4, TRUE);
	feed_back = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "label9"));
	gtk_label_set_label (feed_back, "Click to measure");
}
void disable_test3_repeate(){
	GtkWidget *feed_back;
	gtk_widget_set_sensitive(button4, FALSE);
	//feed_back = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "label9"));
	//gtk_label_set_label (feed_back, "Click to measure");
}

void reset_test3_results() {
	gtk_label_set_label (CoLevelLabel, "**");
	gtk_widget_show (t3_normal_smsg1);
	gtk_widget_hide (t3_result_smsg1);
	gtk_widget_show (t3_normal_smsg2);
	gtk_widget_hide (t3_result_smsg2);
	//gtk_label_set_label (test3_msg, "System message");
	
}

void test3_b_next_btnclicked(GtkWidget *widget, gpointer user_data)
{
	//reset_test3_results();
	hide_window_test3_b();
	show_window_test4();
	start_timer = 0;
	COTestEn = 0;
	set_cur_test = CUR_TEST4;
	show_measure_btn_hide_repeate_btn();
}

void test3_next_btnclicked(GtkWidget *widget, gpointer user_data)
{
	reset_test3_results();
	hide_window_test3();
	show_window_test3_b();
	if(isQuickWellthCheck)
		test3_hide_next_button_n_image();
	start_timer = 0;
	COTestEn = 0;
	//set_cur_test = CUR_TEST4;
	//show_measure_btn_hide_repeate_btn();
}
void test3_click_to_measure_btnclicked(GtkWidget *widget, gpointer user_data)
{
	gchar *buf;
	GtkWidget *feed_back;
	

	FILE *fp;
	start_timer = 1;
	//if height is not selected show dialog window
	reset_test3_results();
	feed_back = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "label9"));
	gtk_label_set_label (feed_back, "Please wait..! Getting your CO level");
	
	printf("ready for CO measurement\n");
	fp = fopen (IN_TEXT_FILE, "w");
	if(fp<0){
		printf(" System is not able to create file \n");
	}
	else{
		printf("ip is ready \n");
		ClearOutPutFile();
		//WriteEntryFile();
		strcpy(InText.InBuf,"CoTest");
		fwrite(InText.InBuf,sizeof(InText.InBuf),1,fp);
		printf(" File has been Updated \n");
		COTestEn = 1;
		fclose(fp);			
	}
	test3_button_set_state(FALSE);
	Minutes = 0;
	Seconds = 0;
	StartTimer = 1;
	
	test_timeout = SMOKE_TIMEOUT;
	TimerInit();
}
//test4_repeate_btnclicked
void test3_set_btnclicked(GtkWidget *widget, gpointer user_data)
{
}
void test3_hide_next_button_n_image(){
	GtkWidget *button;GtkImage *nextImage;
	button = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "next"));
	nextImage = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "next_icon"));
	gtk_widget_hide(button);
	gtk_widget_hide(nextImage);
}

static GtkWidget*
create_test3_window (void)
{
	GtkWidget *window;
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG;

	GError** error = NULL;
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (Test3Builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (Test3Builder, TEST3_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TEST3_WINDOW,
				TEST3_UI_FILE);
        }

	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3Builder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3Builder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);

	//GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3Builder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	GdkPixbufAnimation * pixbufTestanm = gdk_pixbuf_animation_new_from_file(TEST3, error);
	imageTest = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3Builder, "image2"));
	gtk_image_set_from_animation(GTK_IMAGE(imageTest), pixbufTestanm);

#ifdef DISPLAY_ADD
	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ADDS2, error);
	GtkImage *adds = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3Builder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(adds), pixbufaddanm);
#endif

	//GdkPixbufAnimation * pixbuf1 = gdk_pixbuf_animation_new_from_file(GRAPH, error);
	//GtkImage * grf = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3Builder, "graph"));
	//gtk_image_set_from_animation(GTK_IMAGE(grf), pixbuf1);
	
	
	button1 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "exit"));
 	 g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (test_exit_btnclicked),
                    NULL);
	profileBtnClickedFrom = test3_pro_btn;
	
	button2 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "profile"));
 	 g_signal_connect (G_OBJECT (button2), "clicked",
                    G_CALLBACK (test_profile_btnclicked),
                    profileBtnClickedFrom);

	button4 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "repeate"));
	g_signal_connect (G_OBJECT (button4), "clicked",
                    G_CALLBACK (test3_click_to_measure_btnclicked),
                    NULL);
	
	button3 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "click_to_measure"));
	GtkWidget *timer_label = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "timer_label"));
 	 g_signal_connect (G_OBJECT (button3), "clicked",
                    G_CALLBACK (test3_click_to_measure_btnclicked),
                    NULL);
	continue_timer = TRUE;
    start_timer = TRUE;
	//g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(_start_timer), timer_label);
	//g_signal_connect(G_OBJECT(button31), "clicked", G_CALLBACK(_start_timer), timer_label);

	CoLevelLabel = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "label5"));
	//test3_msg = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "label7"));

	t3_normal_smsg1 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "t3_normal_smsg1"));
	t3_normal_smsg2 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "t3_normal_smsg2"));
	t3_result_smsg1 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "t3_result_smsg1"));
	t3_result_smsg2 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "t3_result_smsg2"));
	
	/*button4 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "skip"));
 	 g_signal_connect (G_OBJECT (button4), "clicked",
                    G_CALLBACK (test3_set_btnclicked),
                    NULL);
	*/
	button5 = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "next"));
 	 g_signal_connect (G_OBJECT (button5), "clicked",
                    G_CALLBACK (test3_next_btnclicked),
                    NULL);
	
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_test3()
{
	GtkWidget *window, *label;
	char lbl_buf[64];
	if(!init_test3_window) {
		   GError *error=NULL;
		Test3Builder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (Test3Builder, TEST3_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_test3_window();
		init_test3_window = 1;
	}
	label = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "user_name"));
	strcpy(lbl_buf, "Hi ");
	reset_test3_results();
	strcat(lbl_buf, GlobalUserName);
	gtk_label_set_label (label, lbl_buf);
	
	window = GTK_WIDGET (gtk_builder_get_object (Test3Builder, TEST3_WINDOW));
	gtk_widget_show_all(window);
	cur_active_screen = test3_scrn;
}

void hide_window_test3()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (Test3Builder, TEST3_WINDOW));
	gtk_widget_hide(window);
}

void GetCoOutput(void){
	GtkWidget *window;
	FILE *fp;
	char Buf[2];
	char CO_buf[64], co_read_buf[32];
	char BMI_msg_buf[128];
	float CO_value;
   
	if(COTestEn==1){
		fp = fopen (OT_TEXT_FILE, "r+");
		if(fp<0){
			printf(" System is not able to create file \n");
		}
		else{
			fread(&Buf,1,1,fp);
			fclose(fp);	
			if(Buf[0] == '1'){
				printf(" String info %d \n",Buf[0]);
				printf("System Got Data Updated \n");
				fp = fopen (OT_ENTERY_FILE, "r");
				if(fp < 0){
					g_print("Data.csv not able to open");
				}
				GetLine(fp, co_read_buf);
				//fread(co_read_buf,sizeof(co_read_buf),1,fp);
				fclose(fp);
				sscanf(co_read_buf, "%f", &CO_value);
				sprintf(CO_buf, "%s", co_read_buf);
				
				printf("CO Value is %f\n", CO_value);			
				
					//gtk_entry_set_text(entry2,&Bmi.Weight);
				//gtk_entry_set_text(entry3,&Bmi.BmiValue);	
				if(CO_value < 1.1) {
					gtk_widget_hide (t3_normal_smsg1);
					gtk_widget_show (t3_result_smsg1);
					gtk_widget_show (t3_normal_smsg2);
					gtk_widget_hide (t3_result_smsg2);
				} else { 
					gtk_widget_show (t3_normal_smsg1);
					gtk_widget_hide (t3_result_smsg1);
					gtk_widget_hide (t3_normal_smsg2);
					gtk_widget_show (t3_result_smsg2);
				}
				gtk_label_set_label (CoLevelLabel, CO_buf);
				//gtk_label_set_label (test3_msg, bmi_buf);
				COTestEn=0;
				Minutes = 0;
				Seconds = 0;
				ClearOutPutFile();
				test3_button_set_state(TRUE);
				smoke_test_wait_start();

				window = GTK_WIDGET (gtk_builder_get_object (Test3Builder, TEST3_WINDOW));
				gtk_widget_show_all(window);
				if(isQuickWellthCheck)
					test3_hide_next_button_n_image();
			}			
		}
	}
}

static GtkWidget*
create_test3_b_window (void)
{
	GtkWidget *window; 
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG, *add;
	GtkWidget *timer_label;

	GtkWidget *vbox1;
	GError** error = NULL;
	int i=0;
	char buf[8];
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (Test3bBuilder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, TEST3_b_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TEST3_b_WINDOW,
				TEST1B_UI_FILE);
        }
/*
	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test1Builder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test1Builder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);
*/
	//GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);
/*
	GdkPixbufAnimation * pixbufTestanm = gdk_pixbuf_animation_new_from_file(TEST1, error);
	imageTest = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "image2"));
	gtk_image_set_from_animation(GTK_IMAGE(imageTest), pixbufTestanm);
*/
	
	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ADDS2, error);
	add = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(add), pixbufaddanm);
	
//#endif
	
	//GdkPixbufAnimation * pixbuf1 = gdk_pixbuf_animation_new_from_file(GRAPH, error);
	//GtkImage * grf = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test1Builder, "graph"));
	//gtk_image_set_from_animation(GTK_IMAGE(grf), pixbuf1);
	
/*	GdkPixbufAnimation * pixbuf2 = gdk_pixbuf_animation_new_from_file(T1_NEXT_ICON, error);
	GtkImage * nxt_icon = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "next_icon"));
	gtk_image_set_from_animation(GTK_IMAGE(nxt_icon), pixbuf2);
*/
	GdkPixbufAnimation * pixbuf2 = gdk_pixbuf_animation_new_from_file(T3_NEXT_ICON, error);
	GtkImage * nxt_icon = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "next_icon"));
	gtk_image_set_from_animation(GTK_IMAGE(nxt_icon), pixbuf2);
	
	button1 = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "exit"));
 	 g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (test_exit_btnclicked),
                    NULL);

	home_button = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "home"));
 	 g_signal_connect (G_OBJECT (home_button), "clicked",
                    G_CALLBACK (test_home_btnclicked),
                    NULL);
	
	button5 = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "next"));
 	 g_signal_connect (G_OBJECT (button5), "clicked",
                    G_CALLBACK (test3_b_next_btnclicked),
                    NULL);

	
	
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_test3_b()
{
	GtkWidget *window, *label;
	char lbl_buf[64];
	if(!init_test3_b_window) {
		   GError *error=NULL;
		Test3bBuilder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (Test3bBuilder, TEST3B_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_test3_b_window();
		init_test3_b_window = 1;
	}
	label = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, "user_name"));
	strcpy(lbl_buf, "Hi ");
	strcat(lbl_buf, GlobalUserName);
	gtk_label_set_label (label, lbl_buf);
	
	window = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, TEST3_b_WINDOW));
	gtk_widget_show_all(window);
	cur_active_screen = test3_b_scrn;
	if(isQuickWellthCheck)
		gtk_widget_hide(button1);
	else
		gtk_widget_hide(home_button);
}

void hide_window_test3_b()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (Test3bBuilder, TEST3_b_WINDOW));
	gtk_widget_hide(window);
}

