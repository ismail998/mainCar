#include <gtk/gtk.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "contra.h"
GtkBuilder *builder;
//struct Voiture
//save voiture btn
void WindowGesClient (GtkWidget *widget,gpointer   data);
void btn_click(GtkButton *wboton, GtkEntry **wentrada);
void btn_ok(GtkWidget *widget,gpointer   data);
void btn_save_client(GtkButton *wboton, GtkEntry **wentrada);
void btn_search_client(GtkButton *wboton, GtkEntry **wentrada);
void btn_update_client(GtkButton *wboton, GtkEntry **wentrada);
void btn_search(GtkButton *wboton, GtkEntry *wentrada);
void btn_sup(GtkButton *wboton, GtkEntry *wentrada);
int ilestexitid(int id);
void showWindownotfound (GtkWidget *widget, gpointer   data);
void btn_sup_client(GtkButton *wboton, GtkEntry *wentrada);
void setlabelInTable(const char *str,GtkWidget *table,int n,int m ,int k,int l);
void WindowAjoutVoiture(GtkWidget *widget, gpointer   data);
void WindowAjoutClient (GtkWidget *widget, gpointer   data);
void WindowGesVoiture (GtkWidget *widget,gpointer   data);
void Windowmodvoiture (GtkWidget *widget,gpointer   data);
void WindowmodClient (GtkWidget *widget,gpointer   data);
void WindowSuprimerVoiture (GtkWidget *widget,gpointer   data);
void WindowSuprimerCleint (GtkWidget *widget,gpointer   data);
void close_app  (GtkButton *wboton, GtkEntry *wentrada);
void Windowlist (GtkWidget *widget,gpointer   data);
void Windowlistclient (GtkWidget *widget,gpointer   data);
void btn_updat (GtkButton *wboton, GtkEntry **wentrada);
int main (int   argc,
      char *argv[])
{
  GObject *window;
  GError *error = NULL;
  GObject *btnGvoiture,*btnclient,*btnlocation,*btnclose;
  gtk_init (&argc, &argv);
  FILE *fp,*ftp,*fcp,*fop;
  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "mainUi.glade", &error) == 0){
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    }
  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  btnGvoiture = gtk_builder_get_object(builder,"Gvoiture");
  btnclient = gtk_builder_get_object(builder,"GClient");
  btnlocation  =gtk_builder_get_object(builder,"locatio");
  btnclose=gtk_builder_get_object(builder,"quite");
   // open file
     if((fp=fopen("voiture.txt","rb+"))==NULL)
{
    if((fp=fopen("voiture.txt","wb+"))==NULL)
       {
           printf("can't open file");
       }}
    fclose(fp);
    /*************************************************/
       if((fop=fopen("contra.txt","rb+"))==NULL)
{
      if((fop=fopen("contra.txt","w"))==NULL)
       {
           printf("can't open file");
       }}
    fclose(fop);
    /*************************************************/
if((ftp=fopen("tmp.txt","rb+"))==NULL)
{
    if((ftp=fopen("tmp.txt","wb+"))==NULL)
       {
           printf("can't open file");
       }}
    fclose(ftp);
    /****************************************************/
     if((fp=fopen("client.txt","rb+"))==NULL)
{
    if((fp=fopen("client.txt","wb+"))==NULL)
       {
           printf("can't open file");
       }}
    fclose(fp);
    /***********************************************************/
  g_signal_connect (btnGvoiture, "clicked",G_CALLBACK (WindowGesVoiture), NULL);
  g_signal_connect (btnclient, "clicked",G_CALLBACK (WindowGesClient), NULL);
   g_signal_connect (btnlocation, "clicked",G_CALLBACK (Windowlocation), NULL);
 g_signal_connect (btnclose, "clicked",G_CALLBACK (close_app), NULL);

  gtk_widget_show(window);
  gtk_main ();
  return 0;
}
void close_app  (GtkButton *wboton, GtkEntry *wentrada){
GObject *window14;
window14 = gtk_builder_get_object (builder, "window");
closeWindow(window14);
}
void btn_click(GtkButton *wboton, GtkEntry **wentrada){
  FILE *fp;
  voiture v;
  GObject *window;
  window = gtk_builder_get_object (builder, "ajoutvoiture");
 const char  *nameVoiture,*mareque,*couleur,*nbplace,*prixJour,*Elocation,* idVOITURE;
 nameVoiture = gtk_entry_get_text (*(wentrada+0));
 mareque  = gtk_entry_get_text (*(wentrada+1));
 couleur   =  gtk_entry_get_text (*(wentrada+2));
 nbplace  = gtk_entry_get_text (*(wentrada+3));
 prixJour  = gtk_entry_get_text (*(wentrada+4));
 Elocation = gtk_entry_get_text (*(wentrada+5));
 idVOITURE  =gtk_entry_get_text (*(wentrada+6));
 int f=0;
     fp = fopen("voiture.txt","r");


     while(fscanf(fp,"%d %s %s %d %s %d %s \n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
     {
            if(v.idVoiture==atoi(idVOITURE))
            {
                    f =1;
            }

     }
 fclose(fp);
if(f==1){
           GObject *win1;
           win1 =  gtk_builder_get_object (builder, "existid");
           gtk_widget_show(win1);
           closeWindow(window);

} else{
    fp=fopen("voiture.txt","a+");
        {
           v.idVoiture =atoi(idVOITURE);
           strcpy(v.nomVoiture, nameVoiture);
           strcpy(v.marque, mareque);
           v.nbplaces= atoi(nbplace);
           strcpy(v.couleur, couleur);
            v.prixJour = atoi(prixJour);
           strcpy(v.EnLocation, Elocation);
            fprintf(fp,"%d %s %s %d %s %d %s \n",v.idVoiture,v.nomVoiture,v.marque,v.nbplaces,v.couleur,v.prixJour,v.EnLocation);
            printf("\n\n\t\t\t\tRecord insert successful");
        }
       fclose(fp);
}

}

 void WindowAjoutVoiture(GtkWidget *widget, gpointer   data) {
     GObject *window;
     GObject *btnSave,*btnExest;
     GtkEntry **tabentry;
     tabentry = (GtkEntry*) malloc(7 * sizeof(GtkEntry));
     builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "ajoutvoiture");
     btnExest = gtk_builder_get_object(builder,"btnExest");
     btnSave = gtk_builder_get_object(builder,"btnSave");
     tabentry[0] =GTK_ENTRY(gtk_builder_get_object(builder, "EnameVoiture"));
     tabentry[1] = GTK_ENTRY(gtk_builder_get_object(builder,"Emareque"));
     tabentry[2] =GTK_ENTRY(gtk_builder_get_object(builder,"Ecouleur"));
     tabentry[3] = GTK_ENTRY(gtk_builder_get_object(builder,"Enbplace"));
     tabentry[4] = GTK_ENTRY(gtk_builder_get_object(builder,"EprixJour"));
     tabentry[5] = GTK_ENTRY(gtk_builder_get_object(builder,"EElocation"));
     tabentry[6] = GTK_ENTRY(gtk_builder_get_object(builder,"EidVoiture"));
     g_signal_connect (btnSave, "clicked",G_CALLBACK (btn_click), (GtkEntry*)tabentry);
     gtk_widget_show_all(window);
 }
 void btn_save_client(GtkButton *wboton, GtkEntry **wentrada){
 FILE *fcp;
 client c;
 GObject *window;
 window = gtk_builder_get_object (builder, "ajoutclien");
 const char  *nom,*prenom,*adress,*cin,*telephone,* idclient;
 idclient = gtk_entry_get_text (*(wentrada+0));
 nom  = gtk_entry_get_text (*(wentrada+1));
 prenom  =  gtk_entry_get_text (*(wentrada+2));
 cin  = gtk_entry_get_text (*(wentrada+3));
 adress  = gtk_entry_get_text (*(wentrada+4));
 telephone = gtk_entry_get_text (*(wentrada+5));
      fcp = fopen("client.txt","r");
     int f=0;
     while(fscanf(fcp,format_client,&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
     {
            if(c.idClient==atoi(idclient))
            {
                    f =1;
            }
     }
     if(f==0){
 fcp=fopen("client.txt","a+");
        {
           c.idClient =atoi(idclient);
           strcpy(c.nom, nom);
           strcpy(c.prenom, prenom);
           c.telephone= atoi(telephone);
            c.cin = atoi(cin);
           strcpy(c.adresse, adress);

            fprintf(fcp,"%d %s %s %d %s %d \n",c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
            printf("\n\n\t\t\t\tRecord insert successful");
        }
       fclose(fcp);
closeWindow(window);
}else{
 GObject *win1;
           win1 =  gtk_builder_get_object (builder, "existid");
           gtk_widget_show(win1);
}
 }
 void WindowAjoutClient (GtkWidget *widget, gpointer   data){
    GObject *window;
     GObject *btnSave,*btnExest;
     GtkEntry **tabentry;
     tabentry = (GtkEntry*) malloc(6 * sizeof(GtkEntry));
     builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "ajoutclien");
     btnExest = gtk_builder_get_object(builder,"btnExest2");
     btnSave = gtk_builder_get_object(builder,"btnSave1");
     tabentry[0] =GTK_ENTRY(gtk_builder_get_object(builder, "eidclient"));
     tabentry[1] = GTK_ENTRY(gtk_builder_get_object(builder,"enomc"));
     tabentry[2] =GTK_ENTRY(gtk_builder_get_object(builder,"eprenom"));
     tabentry[3] = GTK_ENTRY(gtk_builder_get_object(builder,"ecin"));
     tabentry[4] = GTK_ENTRY(gtk_builder_get_object(builder,"adress"));
     tabentry[5] = GTK_ENTRY(gtk_builder_get_object(builder,"telephone"));
     g_signal_connect (btnSave, "clicked",G_CALLBACK (btn_save_client), (GtkEntry*)tabentry);
     gtk_widget_show_all(window);
 }
 void btn_search(GtkButton *wboton, GtkEntry *wentrada){
   FILE *fp;
   voiture v;
   int f =0;
   char num[10],num2[10];
   const char *idvoiture,*tname,*tmarque,*tenlocation,*tnbplace,*tcoulour,*tprixj;
   GtkEntry *nameCar,*idcare,*marque,*enlocation,*nbplace,*coulour,*pjour;
     nameCar =GTK_ENTRY(gtk_builder_get_object(builder, "EnameVoiture1"));
     marque = GTK_ENTRY(gtk_builder_get_object(builder,"Emareque1"));
     coulour =GTK_ENTRY(gtk_builder_get_object(builder,"Ecouleur1"));
     nbplace = GTK_ENTRY(gtk_builder_get_object(builder,"Enbplace1"));
     pjour= GTK_ENTRY(gtk_builder_get_object(builder,"EprixJour1"));
     enlocation = GTK_ENTRY(gtk_builder_get_object(builder,"EElocation1"));
   idcare = GTK_ENTRY(gtk_builder_get_object(builder,"EidVoiture1"));
   idvoiture = gtk_entry_get_text (wentrada);
    fp = fopen("voiture.txt","r");

      if(fp == NULL)
    {
            printf("file does not found !");
            exit(1);
    }
     else{

        fp=fopen("voiture.txt","r");
        {
            while(fscanf(fp,"%d %s %s %d %s %d %s \n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
            {

                if(v.idVoiture==atoi(idvoiture))
                {
                    f=1;
                    tname =v.nomVoiture;
                     tmarque =v.marque;
                     tcoulour=v.couleur;
                     tenlocation =v.EnLocation;
                     itoa(v.nbplaces, num, 10);
                     tnbplace = num;
                     itoa(v.prixJour, num2, 10);
                     tprixj = num2;

                }

            }
        }
    }
    if(f==0){
            GObject *win1;
           win1 =  gtk_builder_get_object (builder, "exitspasid");
           gtk_widget_show(win1);
    }
    else{
         gtk_entry_set_text(nameCar,tname);
                    gtk_entry_set_text (enlocation,tenlocation);
                    gtk_entry_set_text (marque,tmarque);
                    gtk_entry_set_text (coulour,tcoulour);
                    gtk_entry_set_text (idcare,idvoiture);
                   gtk_entry_set_text (nbplace,tnbplace);
                  gtk_entry_set_text (pjour,tprixj);
    }
    fclose(fp);

  }
 void WindowGesVoiture (GtkWidget *widget,gpointer   data)
{
  GObject *window;
  GObject *btnAjouterVoiture,*modVoiture,*btnlistv,*btnsuppremerVoiture;
  builder = gtk_builder_new_from_file("mainUi.glade");
  window = gtk_builder_get_object (builder, "gestionVoiture");
  btnAjouterVoiture = gtk_builder_get_object(builder,"AjoutVoiture");
  btnlistv = gtk_builder_get_object(builder,"listvoiturbtn");
  modVoiture = gtk_builder_get_object(builder,"modvoiture");
  btnsuppremerVoiture= gtk_builder_get_object(builder,"btnsupp");
  g_signal_connect (btnAjouterVoiture, "clicked",G_CALLBACK (WindowAjoutVoiture), NULL);
  g_signal_connect (modVoiture, "clicked",G_CALLBACK (Windowmodvoiture), NULL);
  g_signal_connect (btnlistv, "clicked",G_CALLBACK (Windowlist), NULL);
   g_signal_connect (btnsuppremerVoiture, "clicked",G_CALLBACK (WindowSuprimerVoiture), NULL);
  gtk_widget_show_all(window);
}
void WindowGesClient (GtkWidget *widget,gpointer   data){
 GObject *window;
  GObject *btnAjouterClient,*modClient,*btnlistc,*btnsuppremerClient;
  builder = gtk_builder_new_from_file("mainUi.glade");
  window = gtk_builder_get_object (builder, "clien1");
  btnAjouterClient = gtk_builder_get_object(builder,"ajoutclient");
  btnlistc = gtk_builder_get_object(builder,"listclient");
  modClient = gtk_builder_get_object(builder,"modclient");
  btnsuppremerClient= gtk_builder_get_object(builder,"btnsuppclient");
  g_signal_connect (btnAjouterClient, "clicked",G_CALLBACK (WindowAjoutClient), NULL);
  g_signal_connect (modClient, "clicked",G_CALLBACK (WindowmodClient), NULL);
  g_signal_connect (btnlistc, "clicked",G_CALLBACK (Windowlistclient), NULL);
  g_signal_connect (btnsuppremerClient, "clicked",G_CALLBACK (WindowSuprimerCleint), NULL);
 gtk_widget_show_all(window);

}
void WindowmodClient (GtkWidget *widget,gpointer   data){

GObject *window;
GObject *btnsearch,*btnUpdate;
GtkEntry **tab;
     builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "updatclient");
     btnsearch= gtk_builder_get_object(builder,"btnsearch2");
     btnUpdate = gtk_builder_get_object(builder,"btnupdatc");
     tab = (GtkEntry*) malloc(6 * sizeof(GtkEntry));
     tab[0] =GTK_ENTRY(gtk_builder_get_object(builder, "idclient"));
     tab[1] = GTK_ENTRY(gtk_builder_get_object(builder,"Enom"));
     tab[2] =GTK_ENTRY(gtk_builder_get_object(builder,"Eprenom"));
     tab[3] = GTK_ENTRY(gtk_builder_get_object(builder,"Eadress"));
     tab[4] = GTK_ENTRY(gtk_builder_get_object(builder,"Ecin"));
     tab[5] = GTK_ENTRY(gtk_builder_get_object(builder,"Etele"));
     g_signal_connect (btnsearch, "clicked",G_CALLBACK (btn_search_client), (GtkEntry*)tab);
     g_signal_connect (btnUpdate, "clicked",G_CALLBACK (btn_update_client), (GtkEntry*)tab);
     gtk_widget_show_all(window);

}
 void Windowmodvoiture (GtkWidget *widget,gpointer   data){
      GObject *window;
     GObject *btnsearch,*btnUpdate;
     GtkEntry *entryid,**tab;
     tab = (GtkEntry*) malloc(7*sizeof(GtkEntry));
      builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "search");
     btnsearch= gtk_builder_get_object(builder,"btnsearch");
     btnUpdate = gtk_builder_get_object(builder,"btnupdat");
      tab[0] =GTK_ENTRY(gtk_builder_get_object(builder, "EnameVoiture1"));
     tab[1] = GTK_ENTRY(gtk_builder_get_object(builder,"Emareque1"));
     tab[2] =GTK_ENTRY(gtk_builder_get_object(builder,"Ecouleur1"));
     tab[3] = GTK_ENTRY(gtk_builder_get_object(builder,"Enbplace1"));
     tab[4] = GTK_ENTRY(gtk_builder_get_object(builder,"EprixJour1"));
     tab[5] = GTK_ENTRY(gtk_builder_get_object(builder,"EElocation1"));
     tab[6] = GTK_ENTRY(gtk_builder_get_object(builder,"EidVoiture1"));
     entryid =GTK_ENTRY(gtk_builder_get_object(builder, "sidcar"));
     g_signal_connect (btnsearch, "clicked",G_CALLBACK (btn_search), entryid);
     g_signal_connect (btnUpdate, "clicked",G_CALLBACK (btn_updat), (GtkEntry*)tab);
     gtk_widget_show_all(window);
 }

void Windowlist (GtkWidget *widget,gpointer   data){
    GtkWidget *window;
    GtkWidget *lable;
    GtkWidget *table;
    FILE *fp;
    voiture v;
    char num[5];
    int R=2,C=7,cp=0,rp=1;
    const char *str="nom voiture";
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Table");
    table = gtk_table_new (R, C, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    setlabelInTable(str,table,0,1,0,1);
    setlabelInTable(str="marqua",table,1,2,cp,rp);
    setlabelInTable(str="numbre de place",table,2,3,cp,rp);
    setlabelInTable(str="en location",table,3,4,cp,rp);
    setlabelInTable(str="prix jour",table,4,5,cp,rp);
    setlabelInTable(str="id voiture",table,5,6,cp,rp);
    setlabelInTable(str="coulour",table,6,7,cp,rp);

    //view all car
fp=fopen("voiture.txt","r");
    if(fp == NULL)
    {
        printf("file does not found !");
        exit(1);
    }
    else
    fp=fopen("voiture.txt","r");
    {
        while(fscanf(fp,"%d %s %s %d %s %d %s\n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
        {
           printf("is open");
           rp++;
           cp++;
           itoa(v.idVoiture, num, 10);
            setlabelInTable(str=num,table,5,6,cp,rp);
            setlabelInTable(str=v.nomVoiture,table,0,1,cp,rp);
            setlabelInTable(str=v.marque,table,1,2,cp,rp);
            itoa(v.nbplaces, num, 10);
            setlabelInTable(str=num,table,2,3,cp,rp);
            setlabelInTable(str=v.EnLocation,table,3,4,cp,rp);
            itoa(v.prixJour, num, 10);
            setlabelInTable(str=num,table,4,5,cp,rp);
            setlabelInTable(str=v.couleur,table,6,7,cp,rp);
            R++;
            gtk_table_resize (table,R,C);
        }
    }
   fclose(fp);
    gtk_widget_show(table);
    gtk_widget_show(window);
}
void setlabelInTable(const char *str,GtkWidget *table,int n,int m ,int k,int l){
    GtkWidget *lable;
    lable = gtk_label_new (NULL);
    gtk_label_set_text (lable,str);
    gtk_table_attach_defaults (GTK_TABLE (table), lable, n, m, k, l);
    gtk_widget_show (lable);
}

void WindowSuprimerVoiture (GtkWidget *widget,gpointer   data){
     GObject *window;
     GObject *btnsuppreme;
     GtkEntry *entry;
     builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "suppremerVoiture");
     entry = GTK_ENTRY(gtk_builder_get_object(builder, "idsuppremer"));
     btnsuppreme = gtk_builder_get_object(builder,"btnrecherche");
      g_signal_connect (btnsuppreme, "clicked",G_CALLBACK (btn_sup), entry);
     gtk_widget_show_all(window);
}
void btn_sup(GtkButton *wboton, GtkEntry *wentrada){
   FILE *fp,*fp1;
   voiture v;
   char num[5];
   GObject *window;
     builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "suppremerVoiture");
   const char *idvoiture;
     idvoiture = gtk_entry_get_text (wentrada);
    fp = fopen("voiture.txt","r");
     fp1 = fopen("tmp.txt","a");
     char number[100];
     char date[20];
     int f=0;
     while(fscanf(fp,"%d %s %s %d %s %d %s \n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
     {
            if(v.idVoiture==atoi(idvoiture))
            {
                    f =1;
                    printf("\n\n\n\t\t\t\tDelete successfull\n\n");
            }
            else
            {
                fprintf(fp1,"%d %s %s %d %s %d %s \n",v.idVoiture,v.nomVoiture,v.marque,v.nbplaces,v.couleur,v.prixJour,v.EnLocation);
            }

     }
     if(f==0)
     {
           GObject *win1;
           win1 =  gtk_builder_get_object (builder, "exitspasid");
           gtk_widget_show(win1);
     }
     fclose(fp);
     fclose(fp1);
     fp = fopen("voiture.txt","w");
    fclose(fp);
     fp = fopen("voiture.txt","a");
    fp1 = fopen("tmp.txt","r");
    while(fscanf(fp1,"%d %s %s %d %s %d %s \n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
    {
                fprintf(fp,"%d %s %s %d %s %d %s \n",v.idVoiture,v.nomVoiture,v.marque,v.nbplaces,v.couleur,v.prixJour,v.EnLocation);
    }
    fclose(fp);
    fclose(fp1);
    fp = fopen("tmp.txt","w");
    fclose(fp);
}
void btn_sup_client(GtkButton *wboton, GtkEntry *wentrada){
    FILE *fcp,*fp1;
    client c;
   char num[15];
   const char *idclient;
     idclient = gtk_entry_get_text (wentrada);
      fcp = fopen("client.txt","r");
     fp1 = fopen("tmp.txt","a");
     char number[100];
     char date[20];
     int f=0;
     while(fscanf(fcp,format_client,&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
     {
            if(c.idClient==atoi(idclient))
            {
                    f =1;
                    printf("\n\n\n\t\t\t\tDelete successfull\n\n");
            }
            else
            {
                fprintf(fp1,format_client,c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
            }

     }
     if(f==0)
     {
           GObject *win1;
           win1 =  gtk_builder_get_object (builder, "exitspasid");
           gtk_widget_show(win1);

     }
     fclose(fcp);
     fclose(fp1);
    fcp = fopen("client.txt","w");
    fclose(fcp);
     fcp = fopen("client.txt","a");
    fp1 = fopen("tmp.txt","r");
    while(fscanf(fp1,format_client,&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
    {
                fprintf(fcp,format_client,c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
    }
    fclose(fcp);
    fclose(fp1);
    fcp = fopen("tmp.txt","w");
    fclose(fcp);
}
void Windowlistclient (GtkWidget *widget,gpointer   data){
    GtkWidget *window;
    GtkWidget *lable;
    GtkWidget *table;
    FILE *fcp;
    client c;
    char num[15];
    int R=2,C=6,cp=0,rp=1;
    const char *str="id client";
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Table");
    table = gtk_table_new (R, C, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    setlabelInTable(str,table,0,1,0,1);
    setlabelInTable(str="nom",table,1,2,cp,rp);
    setlabelInTable(str="prenom",table,2,3,cp,rp);
    setlabelInTable(str="cin",table,3,4,cp,rp);
    setlabelInTable(str="adress",table,4,5,cp,rp);
    setlabelInTable(str="telphone",table,5,6,cp,rp);
    fcp=fopen("client.txt","r");
    if(fcp == NULL)
    {
        printf("file does not found !");
        exit(1);
    }
     else
    fcp=fopen("client.txt","r");
    {
        while(fscanf(fcp,"%d %s %s %d %s %d \n",&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
        {
           rp++;
           cp++;
           itoa(c.idClient, num, 10);
            setlabelInTable(str=num,table,0,1,cp,rp);
            setlabelInTable(str=c.nom,table,1,2,cp,rp);
            setlabelInTable(str=c.prenom,table,2,3,cp,rp);
            itoa(c.cin, num, 10);
            setlabelInTable(str=num,table,3,4,cp,rp);
            setlabelInTable(str=c.adresse,table,4,5,cp,rp);
            itoa(c.telephone, num, 10);
            setlabelInTable(str=num,table,5,6,cp,rp);
            R++;
            gtk_table_resize (table,R,C);
        }
    }
   fclose(fcp);
    gtk_widget_show(table);
    gtk_widget_show(window);
}
void WindowSuprimerCleint (GtkWidget *widget,gpointer   data){
    GObject *window;
     GObject *btnsuppreme;
     GtkEntry *entry;
     builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "supclient");
     entry = GTK_ENTRY(gtk_builder_get_object(builder, "idsuppremer1"));
     btnsuppreme = gtk_builder_get_object(builder,"btnrecherche1");
      g_signal_connect (btnsuppreme, "clicked",G_CALLBACK (btn_sup_client), entry);
     gtk_widget_show_all(window);

}
void btn_search_client(GtkButton *wboton, GtkEntry **wentrada){
   FILE *fp;
   client c;
   char num[10],num2[10];
   const char *idclient,*tnom,*tprenom,*tadress,*ttele,*tcin;
   int f =0;
   idclient = gtk_entry_get_text (*(wentrada));

    fp = fopen("client.txt","r");

      if(fp == NULL)
    {
            printf("file does not found !");
            exit(1);
    }
     else{

        fp=fopen("client.txt","r");

            while(fscanf(fp,format_client,&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
            { if(c.idClient==atoi(idclient))
                {
                    f=1;
                     tnom =c.nom;
                     tprenom =c.prenom;
                     tadress=c.adresse;
                     itoa(c.cin, num2, 10);
                     tcin = num2;
                     itoa(c.telephone, num, 10);
                     ttele = num;
                    gtk_entry_set_text(*(wentrada+1),tnom);
                    gtk_entry_set_text (*(wentrada+2),tprenom);
                    gtk_entry_set_text (*(wentrada+3),tadress);
                    gtk_entry_set_text (*(wentrada+4),tcin);
                    gtk_entry_set_text (*(wentrada+5),ttele);

                }

            }


    }
    if(f==0){
            GObject *win1;
           win1 =  gtk_builder_get_object (builder, "exitspasid");
           gtk_widget_show(win1);
    }
    fclose(fp);
}
void btn_update_client(GtkButton *wboton, GtkEntry **wentrada){
   FILE *fcp,*fp1;
   client c;
   char num[10],num2[10];
   const char *idclient,*tnom,*tprenom,*tadress,*ttele,*tcin,*tnnom,*tnprenom,*tnadress,*tntele,*tncin;
   int f=0;
   idclient = gtk_entry_get_text (*(wentrada));
    tnnom= gtk_entry_get_text(*(wentrada+1));
    tnprenom= gtk_entry_get_text(*(wentrada+2));
    tnadress= gtk_entry_get_text(*(wentrada+3));
    tncin= gtk_entry_get_text(*(wentrada+4));
    tntele= gtk_entry_get_text(*(wentrada+5));
     fcp = fopen("client.txt","r");
      if(fcp == NULL  )
    {printf("file does not found !");
            exit(1);}
     else{
     fcp = fopen("client.txt","r");
     fp1 = fopen("tmp.txt","a");
     int f=0;
     while(fscanf(fcp,format_client,&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
     {
            if(c.idClient==atoi(idclient))
            {
                  fprintf(fp1,format_client,c.idClient,tnnom,tnprenom,atoi(tncin),tnadress,atoi(tntele));
                    f =1;
                    printf("\n\n\n\t\t\t updat successfull\n\n");
            }
            else
            {
                fprintf(fp1,format_client,c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
            }

     }
     if(f==0)
     {
            printf("\n\n\t\t\tid not found");
     }
     fclose(fcp);
     fclose(fp1);
    fcp = fopen("client.txt","w");
    fclose(fcp);
     fcp = fopen("client.txt","a");
    fp1 = fopen("tmp.txt","r");
    while(fscanf(fp1,format_client,&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
    {
                fprintf(fcp,format_client,c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
    }
    fclose(fcp);
    fclose(fp1);
    fcp = fopen("tmp.txt","w");
    fclose(fcp);
            }
    }
void btn_updat (GtkButton *wboton, GtkEntry **wentrada){
   FILE *fp,*fp1;
   voiture v;
   char num[5];
   const char *idvoiture,*tname,*tmarque,*tenlocation,*tnbplace,*tcoulour,*tprixj;
     idvoiture= gtk_entry_get_text (*(wentrada+6));
     tname= gtk_entry_get_text (*(wentrada));
     tmarque= gtk_entry_get_text (*(wentrada+1));
     tenlocation= gtk_entry_get_text (*(wentrada+5));
     tnbplace= gtk_entry_get_text (*(wentrada+3));
     tcoulour= gtk_entry_get_text (*(wentrada+2));
     tprixj= gtk_entry_get_text (*(wentrada+4));
     fp = fopen("voiture.txt","r");
     fp1 = fopen("tmp.txt","a");
     char number[100];
     char date[20];
     int f=0;
     if(fp==NULL){

        printf("is error");
        exit(0);
     }else{
     while(fscanf(fp,"%d %s %s %d %s %d %s \n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
     {
            if(v.idVoiture==atoi(idvoiture))
            {
                    f =1;
                fprintf(fp1,"%d %s %s %d %s %d %s \n",v.idVoiture,tname,tmarque,atoi(tnbplace),tcoulour,atoi(tprixj),tenlocation);
            }
            else
            {
                fprintf(fp1,"%d %s %s %d %s %d %s \n",v.idVoiture,v.nomVoiture,v.marque,v.nbplaces,v.couleur,v.prixJour,v.EnLocation);
            }

     }
     if(f==0)
     {
            printf("\n\n\t\t\tid not found");
     }
     fclose(fp);
     fclose(fp1);
     fp = fopen("voiture.txt","w");
    fclose(fp);
     fp = fopen("voiture.txt","a");
    fp1 = fopen("tmp.txt","r");
    while(fscanf(fp1,"%d %s %s %d %s %d %s \n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
    {
                fprintf(fp,"%d %s %s %d %s %d %s \n",v.idVoiture,v.nomVoiture,v.marque,v.nbplaces,v.couleur,v.prixJour,v.EnLocation);
    }
    fclose(fp);
    fclose(fp1);
    fp = fopen("tmp.txt","w");
    fclose(fp);
    }
}





