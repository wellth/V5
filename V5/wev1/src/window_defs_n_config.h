#include "DemonRetuns.h"
#include "ProcessCSV.h"

#ifndef ALL_WINDOW_DEFS_N_CONFIG_H
#define ALL_WINDOW_DEFS_N_CONFIG_H

//#define DISPLAY_ADD

/*********************************************************************/
			//Windows images 
/*********************************************************************/

#define CLIENT_LOGO 	"Images/logo.png"
#define WELLTH_LOGO 	"Images/WeLogoFin.png"
//#define BG1 			"/home/kiran/Downloads/800x600.jpg"
//#define BG1 			"/home/kiran/Downloads/222bg.jpg"
//#define BG1 			"Images/w8.jpg"
#define BG1 			"Images/soft_YB_BG.jpg"
#define BG2 			"Images/soft_YB_BG.jpg"
//#define BG 			"Images/yelloBG.png"
#define BG 				"Images/soft_YB_BG.jpg"
#define TEST1			"Images/final_test_1.png"
#define TEST2			"Images/final_test_2.PNG"
//#define TEST2			"Images/final_test_2_icon.PNG"
#define TEST3			"Images/final_test_3.PNG"
//#define TEST3			"Images/final_test_3_icon.PNG"
#define HEALTH_STAT     "Images/stat1.png"
#define TEST4			"Images/final_test_4.PNG"
//#define TEST4			"Images/final_test_4_icon.PNG"
#define SYMPTOMS		"Images/final_check_symptoms.PNG"
#define ADDS1			"Images/add1.gif"
#define ADDS2			"Images/add12.gif"
#define ADDS3			"Images/add3.gif"
#define HM_NEXT_ICON 	"Images/final_test_1_icon.PNG"
#define T1_NEXT_ICON 	"Images/final_test_2_icon.PNG"
#define T2_NEXT_ICON 	"Images/final_test_3_icon.PNG"
#define T3_NEXT_ICON 	"Images/final_test_4_icon.PNG"
#define GRAPH			"Images/graph.png"
#define KEYPAD_BG		"Images/key_pad_bg.png"
#define QNA_ICON		"Images/qna_icon.png"

#define SMART_CARD		"Images/swipe_card.png"

#define Q1O1_IMG		"Images/QnA_png/Q4No.7.png"
#define Q1O2_IMG		"Images/QnA_png/Q410_mins.png"
#define Q1O3_IMG		"Images/QnA_png/Q415_mins.png"
#define Q2O1_IMG		"Images/QnA_png/Q7_male.png"
#define Q2O2_IMG		"Images/QnA_png/Q7_female.png"
#define Q2O3_IMG		"Images/QnA_png/Q7_Same_for_both.png"

#define TICKER_FILE 	"ticker.txt"

/*********************************************************************/
			//UI files
/*********************************************************************/
#define HOME_UI_FILE			"uiScreens/home.ui"
#define TEST1_UI_FILE			"uiScreens/Test1.ui"     //weight and bmi
#define TEST2_UI_FILE			"uiScreens/Test2.ui"     //body fat
#define TEST3_UI_FILE			"uiScreens/Test3.ui"     //smoking detector
#define TEST4_UI_FILE			"uiScreens/Test4.ui"     //blood pressure
#define TEST1B_UI_FILE			"uiScreens/Test1_b.ui"     //weight and bmi
#define TEST2B_UI_FILE			"uiScreens/Test2_b.ui"     //body fat
#define TEST3B_UI_FILE			"uiScreens/Test3_b.ui"     //smoking detector
#define TEST4B_UI_FILE			"uiScreens/Test4_b.ui"     //blood pressure
#define FST_TP_UI_FILE			"uiScreens/first_time_profile.ui"
#define PREV_WE_CHECK_UI_FILE	"uiScreens/prev_we_check_stats.ui"
#define CHECK_SYMPTOMS_UI_FILE	"uiScreens/check_symptoms.ui"
#define EMAIL_COLLEAGUE_UI_FILE	"uiScreens/email_colleague.ui"
#define QUICK_WE_CHECK_UI_FILE	"uiScreens/quick_we_check.ui"
#define DEPENDENT_GUEST_UI_FILE	"uiScreens/dependent_or_guest.ui"
#define PROFILE_UI_FILE			"uiScreens/profile.ui"
#define SYSTEM_ADMIN_UI_FILE	"uiScreens/system_admin.ui"
#define SYS_ADMIN_THEME_UI_FILE	"uiScreens/system_admin_theme.ui"
#define SYS_ADMIN_DIAG_UI_FILE	"uiScreens/system_admin_diagnostic.ui"
#define CLIENT_ADMIN_UI_FILE	"uiScreens/client_admin.ui"

#define USER_SUMMARY_UI_FILE	"uiScreens/user_summary.ui"
#define HEALTH_SUMMARY_UI_FILE	"uiScreens/health_summary.ui"
#define QN_AND_ANS_UI_FILE		"uiScreens/q_n_a.ui"
#define EXIT_UI_FILE			"uiScreens/exit.ui"
#define BACK_GND_FILE			"uiScreens/back_ground.ui"
#define APP_DATABASE_PATH		"src/app_db1.db"

#define KEY_PAD_UI_FILE	"uiScreens/key_pad.ui"

#define MAX_BYTE_DATA_IN_ENTRY_FILE		255

/*********************************************************************/
			//Window names in programm/code
/*********************************************************************/
#define HOME_WINDOW				"window_home"
#define TEST1_WINDOW			"window_test1"
#define TEST2_WINDOW			"window_test2"
#define TEST3_WINDOW			"window_test3"
#define TEST4_WINDOW			"window_test4"
#define TEST1_b_WINDOW			"window_test1b"
#define TEST2_b_WINDOW			"window_test2b"
#define TEST3_b_WINDOW			"window_test3b"
#define TEST4_b_WINDOW			"window_test4b"
#define FST_TIME_PROFILE_WINDOW	"window_1st_time_profile"
#define PREV_WE_CHECK_WINDOW	"window_prev_wellth_check"
#define CHECK_SYMPTOMS_WINDOW	"window_check_symptoms"
#define EMAIL_COLLEAGUE_WINDOW	"window_email_colleague"
#define QUICK_WE_CHECK_WINDOW	"window_quick_we_check"
#define DEPENDENT_GUEST_WINDOW	"window_dependent_or_guest"
#define PROFILE_WINDOW			"window_rpt_user_prof"
#define SYSTEM_ADMIN_WINDOW		"window_system_admin"
#define SYS_ADMIN_THEMES_WINDOW		"window_system_admin_theme"
#define SYS_ADMIN_DIAG_WINDOW		"window_system_admin_diag"
#define CLIENT_ADMIN_WINDOW			"window_client_admin"	
#define USER_SUMMARY_WINDOW			"window_user_summary"
#define HEALTH_SUMMARY_WINDOW			"window_health_summary"
#define BACK_GND_WINDOW				"window_bk_gnd"

#define QN_AND_ANS_WINDOW		"window_q_and_a"
#define EXIT_WINDOW				"window_exit"

#define KEY_PAD_FRAME				"key_pad"	

typedef struct _Private Private;
static struct _Private
{
	/* ANJUTA: Widgets declaration for WindowMain.ui - DO NOT REMOVE */
};

extern const char ticker_text[];
typedef enum pro_btn_clk_from{
	client_admin_pro_btn = 0,
	check_symptoms_pro_btn,
	email_colleague_pro_btn,
	home_pro_btn,
	last_wellth_check_pro_btn,
	quick_wellth_check_pro_btn,
	start_test_pro_btn,
	summary_display_pro_btn,
	test1_pro_btn,
	test2_pro_btn,
	test3_pro_btn,
	test4_pro_btn,
	user_summary_pro_btn
}PROFILE_BTN_CLK;

typedef enum test1{
	CUR_TEST1 = 0,
	CUR_TEST2,
	CUR_TEST3,
	CUR_TEST4
} cur_tests;

typedef enum Screen{
	client_admin_scrn = 0,
	check_symptoms_scrn,
	email_colleague_scrn,
	home_scrn,
	last_wellth_check_scrn,
	quick_wellth_check_scrn,
	system_admin_scrn,
	system_admin_diagnostic_scrn,
	system_admin_theme_scrn,
	depenednt_or_guest_scrn,
	first_time_profile_scrn,
	profile_scrn,
	summary_display_scrn,
	test1_scrn,
	test2_scrn,
	test3_scrn,
	test4_scrn,
	test1_b_scrn,
	test2_b_scrn,
	test3_b_scrn,
	test4_b_scrn,
	user_summary_scrn,
	initial_scrn,
	login_scrn,
	mand_msg_scrn,
	wev1_scrn,
	qn_and_ans_scrn,
	exit_scrn
}ACTIVE_SCREEN;

extern ACTIVE_SCREEN cur_active_screen;
extern DEMON_RETURN_STATUS demon_return_status;

extern int profileBtnClickedFrom;

extern GtkBuilder *DummyBuilder;
extern char GlobalUserName[];
extern int isQuickWellthCheck;
//from admin.c
GtkBuilder *SystemAdminBuilder, *AdminDiagnosticsBuilder, *AdminThemesBuilder, *ClientAdminBuilder;

extern GdkPixbufAnimation * pixbufBGanm;
//from profile.c
extern GtkBuilder *ProfileBuilder;
/******************** Global window builder pointers ********************/
cur_tests set_cur_test;

gboolean _label_update(gpointer data);
void _start_timer (GtkWidget *button, gpointer data);

static struct Private* priv = NULL;

/* Determines if the timer has started */
extern gboolean start_timer;
extern gboolean continue_timer;
/* Display seconds expired */
extern int sec_expired, smoke_wait_expire_sec;
int SessionExpired, Seconds, Minutes;
/********************************************************************************/
				//Global window builder pointers
/********************************************************************************/
extern GtkBuilder *HomeBuilder, *Test1Builder, *Test2Builder, *Test3Builder, *Test4Builder;
extern GtkBuilder *FirstTimeProfileBuilder, *PrevWellthCheckBuilder, *CheckSymptomsBuilder;
extern GtkBuilder *EmailColleagueBuilder, *QuickWeCheckBuilder, *DependentGuestBuilder;

//from main.c
extern GtkBuilder *MainBuilder, *InitialBuilder, *LoginBuilder, *SignupBuilder, 
*MandMsgBuilder, *KeyPadBuilder;
extern GtkBuilder *DummyBuilder;
extern GtkWidget *KeyPadFrameWidget;
extern GtkBuilder *UserSummaryBuilder, *HealthSummaryBuilder;

//from admin.c
GtkBuilder *SystemAdminBuilder, *AdminDiagnosticsBuilder, *AdminThemesBuilder, *ClientAdminBuilder;

//from profile.c
extern GtkBuilder *ProfileBuilder;
extern GtkBuilder *QnAndAnsBuilder;
extern GtkBuilder *ExitBuilder;
/******************** Global window builder pointers ********************/


void create_dummy_window();
/*********************************************************************/
			//Show window functions
/*********************************************************************/
void show_window_mand_msg ();
void show_window_login ();
void show_window_signup ();
void show_window_second();
void show_window_main();
void show_window_test1();
void show_window_test2();
void show_window_test3();
void show_window_test4();
void show_window_test1_b();
void show_window_test2_b();
void show_window_test3_b();
void show_window_test4_b();
void show_window_home();
void show_window_first_time_profile();
void show_window_prev_wellth_check();
void show_window_check_symptoms();
void show_window_email_colleague();
void show_window_quick_wellth_check();
void show_window_dependent_guest();
void show_window_profile();
void show_window_system_admin ();
void show_window_system_admin_diagnostics ();
void show_window_system_admin_themes ();

void show_window_health_summary();
void show_window_user_summary();
void show_window_qna();
void show_window_exit();

/************************* Show window functions **************************/



/*********************************************************************/
				//hide window functions
/*********************************************************************/
void hide_window_test1 ();
void hide_window_test2 ();
void hide_window_test3 ();
void hide_window_test4 ();
void hide_window_test1_b ();
void hide_window_test2_b ();
void hide_window_test3_b ();
void hide_window_test4_b ();
void hide_window_home ();
void hide_window_first_time_profile();
void hide_window_prev_wellth_check();
void hide_window_check_symptoms();
void hide_window_email_colleague();
void hide_window_quick_wellth_check();
void hide_window_dependent_guest ();
void hide_window_profile ();
void hide_window_system_admin ();
void hide_window_system_admin_diagnostics ();
void hide_window_system_admin_themes ();

void hide_window_health_summary();
void hide_window_user_summary();
void hide_window_qna();
void hide_window_exit();

void test1_hide_next_button_n_image();
void test2_hide_next_button_n_image();
void test3_hide_next_button_n_image();
void test4_hide_next_button_n_image();
void qna_next_btnclicked(GtkWidget *widget, gpointer user_data);

/*************************test enable or disable function******************/
void test1_button_set_state(int bool_val);
void test2_button_set_state(int bool_val);
void test3_button_set_state(int bool_val);
void test4_button_set_state(int bool_val);

/***************************hide window functions*****************************/

extern gboolean ScrollTickerText();
extern void test_exit_btnclicked(GtkWidget *widget, gpointer user_data);
void test_profile_btnclicked(GtkWidget *widget, gpointer user_data);
void _start_timer (GtkWidget *button, gpointer data);
char * ReadTickerFromFile();

gboolean playAudioFiles();

/*********************************************************************************
 //			Demon Function
***********************************************************************************/
int ReadDemonLoginStatus();
gboolean WriteDataFromUI(char * WriteDataBuf); 
gboolean isOutputFlagSet();

void BMI_system_msg(float bmi_value, char msg_buf[]);
void get_bmi_summary_graph_name(float bmi_value, int Age, char gender[], char graph_name[]); 
void get_blood_pressure_summary_graph_name(float sbp, float dbp, int Age, char gender[], char sbp_graph_name[], char dbp_graph_name[]);
void blood_pressure_system_msg(float sbp, float dbp, float pls_rate, char msg_buf[]);
void get_bf_summary_graph_name(float bmi_value, float bodyfat_val, int Age, char gender[], char graph_name[]); 

//***************************Demon Function***************************/

#endif			//ALL_WINDOW_DEFS_N_CONFIG_H
