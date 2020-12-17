#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	GtkTextBuffer *text_buffer_view;
	GtkTextView *text_write;
	//GtkTextBuffer *text_buffer2;
	GtkTextView *txtvw_show;

	GtkWidget *scrol_list_friend;
	//GtkLayout *layout;
	GtkWidget *grid;
    GtkWidget *button[100];

    Object *object_chat ;
    int sock_chat_private;
}app_widgets;
int row;
//test

int recv_chat;

app_widgets        *widgets;
GtkWidget       *window_friend_chat;


void set_obj_chat_private(char *from_username, int sockfd){
    widgets = g_slice_new(app_widgets);
    widgets->object_chat = new_chat_private_object();
    strcpy(widgets->object_chat->chat_private.from_username,from_username);
    widgets->sock_chat_private = sockfd;
    //object->chat_private->to_username
}

void recv_to_friend(void *app){
    //test
    char message_recv[250];
    app_widgets *widg = (app_widgets*)app;
    while(1){
 
            recv_chat = recv(widg->sock_chat_private,message_recv,sizeof(message_recv),0);
            if(recv_chat < 0 ) break;
            message_recv[recv_chat] = '\0';
            puts(message_recv);
        
            if(gtk_text_buffer_get_char_count(gtk_text_view_get_buffer(widg->txtvw_show)) != 0){
                gtk_text_buffer_insert_at_cursor(widg->text_buffer_view,"\n",-1);
            }
            gtk_text_buffer_insert_at_cursor(widg->text_buffer_view,message_recv,-1);   
  

    }
    
}

//
void on_row(GtkButton *b);
int chat_private(int argc, char **argv)
{
    GtkBuilder      *builder_chat; 
    GtkWidget       *window_chat;

  

    gtk_init(&argc, &argv);

    builder_chat = gtk_builder_new();
    gtk_builder_add_from_file (builder_chat, "Glade/chat.glade", NULL);

    window_chat = GTK_WIDGET(gtk_builder_get_object(builder_chat, "window_chat"));
    widgets->text_write  = GTK_TEXT_VIEW(gtk_builder_get_object(builder_chat, "txtvw_write"));
    widgets->text_buffer_view  = GTK_TEXT_BUFFER(gtk_builder_get_object(builder_chat, "textbuffer_view"));
    widgets->txtvw_show  = GTK_TEXT_VIEW(gtk_builder_get_object(builder_chat, "txtvw_show"));
    //widgets->text_buffer2  = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer2"));
    widgets->scrol_list_friend = GTK_WIDGET(gtk_builder_get_object(builder_chat,"scrol_list_friend"));
    widgets->grid = GTK_WIDGET(gtk_builder_get_object(builder_chat,"grid_list_friend"));
    //widgets->layout = GTK_LAYOUT(gtk_builder_get_object(builder,"layout"));
    /////////////
    row =0;
    //test
    pthread_t id;
    if(pthread_create(&id,NULL, (void *)recv_to_friend,(void *)widgets) != 0){
        perror("Create pthread error!\n");
        exit(EXIT_FAILURE);
    } 
    
    // 
    //////////
    gtk_builder_connect_signals(builder_chat, widgets);
   
    g_object_unref(builder_chat);
    
    // start 1 second timer
    

    gtk_widget_show(window_chat);    

    //gtk_widget_set_visible(widgets->scrol_list_friend,FALSE);   
           
    gtk_main();
    pthread_cancel(id);
    g_slice_free(app_widgets, widgets);

    return 0;
}

// called when window is closed
void on_window_chat_destroy()
{
    gtk_main_quit();
    gtk_widget_set_visible(window_friend_chat,TRUE);
}

void on_chat_send_clicked(GtkButton *button, app_widgets *widg){
    GtkTextIter start, end;

    gtk_text_buffer_get_start_iter(gtk_text_view_get_buffer(widg->text_write),&start);
    gtk_text_buffer_get_end_iter(gtk_text_view_get_buffer(widg->text_write),&end);
    
    if(gtk_text_buffer_get_char_count(gtk_text_view_get_buffer(widg->txtvw_show)) != 0){
        gtk_text_buffer_insert_at_cursor(widg->text_buffer_view,"\n",-1);
    }
    //test
 
    strcpy(widg->object_chat->chat_private.message,gtk_text_buffer_get_text(
        gtk_text_view_get_buffer(widg->text_write),&start,&end,FALSE));
    if(send(widg->sock_chat_private,widg->object_chat,sizeof(Object),0) < 0){
        perror("send - chat private");
        return;
    }
    //
    //gtk_text_view_set_buffer(widg->text_view2,gtk_text_view_get_buffer(widg->text_view1));
    gtk_text_buffer_insert_at_cursor(widg->text_buffer_view,"[YOU]:\n",-1);
    gtk_text_buffer_insert_at_cursor(widg->text_buffer_view,gtk_text_buffer_get_text(
        gtk_text_view_get_buffer(widg->text_write),&start,&end,FALSE),-1);
    gtk_text_view_set_buffer(widg->text_write,gtk_text_buffer_new(NULL));
    //test client - server
}

void on_togbtn_list_friend_toggled(GtkToggleButton *togglebutton, app_widgets * widg){
	//GtkWidget *button_ = gtk_button_new_with_label("button_name");
    
	if(gtk_widget_is_visible(widg->scrol_list_friend)){
		gtk_widget_set_visible(widg->scrol_list_friend,FALSE);
	}else{
		gtk_widget_set_visible(widg->scrol_list_friend,TRUE);
        gtk_widget_show_all(widg->scrol_list_friend);
	}
	
}

void on_add_friend_clicked(GtkButton *button, app_widgets *widg){
    int stt = row + 1;
    char str_stt[10];
    sprintf(str_stt,"%d",stt);
    char label[] = "friend ";
    strcat(label,str_stt);
    widg->button[row] = gtk_button_new_with_label(label);
    g_signal_connect(widg->button[row],"clicked",G_CALLBACK(on_row),NULL);
    gtk_grid_insert_row(GTK_GRID(widg->grid),row);
    gtk_grid_attach(GTK_GRID(widg->grid),widg->button[row],1,row,1,1);
    if(gtk_widget_is_visible(widg->scrol_list_friend)){
        gtk_widget_show_all(widg->scrol_list_friend);
    }
    row++;

}

void on_row(GtkButton *b){
    g_print("You clicked button: %s\n",gtk_button_get_label(b));
}

