typedef struct Voiture
{
 int idVoiture;
 char marque[15];
 char nomVoiture[15];
 char couleur[7];
 int nbplaces;
 int prixJour;
 char EnLocation[4];
} voiture;
typedef struct Date{
int day;
int mounth;
int year;
}date;
typedef struct Client
{
 int idClient;
 char nom[20];
 char prenom[20];
 int cin;
 char adresse[15];
 int telephone;
}client;
typedef struct contratLocation
{
 int numContrat;
 int idVoiture;
 int idClient;
 date debut;
 date fin;
 int cout;
} contrat;
FILE *fvp,*fcp;
voiture v;
client c;

char  *format_voiture="%d %s %s %d %s %d %s \n";
const char *format_client="%d %s %s %d %s %d \n";
const char *format_contra ="numContrat : %d  idclient : %d idvoiture : %d date debut %d / %d / %d date fin %d / %d / %d cout %d \n";
char *enlocationYes ="oui";
//contra.txt
void louerVoiture(GtkWidget *widget,gpointer   data);
void windowSupContra (GtkWidget *widget,gpointer   data);
void windowmoddate (GtkWidget *widget,gpointer   data);
void cherche(GtkWidget *widget, GtkEntry **wentrada);
void closeWindow(GtkWindow *window);
void fun_btn_ok();
void btn_ret_voiture (GtkWidget *widget, GtkEntry *wentrada);
void sup_contra_n (GtkWidget *widget, GtkEntry *wentrada);
void windowviewContra (GtkWidget *widget,gpointer   data);
void info_contra(GtkWidget *widget, GtkEntry **wentrada);
void save_new_date (GtkWidget *widget, GtkEntry **wentrada);
void savecountra(GtkWidget *widget, GtkEntry **wentrada);
void changeLocation(int i,char *y);
void fun_btn_ok_click();
void sup_contra(int numcntra);
void returnerVoiture(GtkWidget *widget,gpointer   data);
void btn_ret_voiture (GtkWidget *widget, GtkEntry *wentrada){
   FILE *fcp;
   contrat co;
   GtkBuilder  *builder;
   builder = gtk_builder_new_from_file("mainUi.glade");
   GObject *window;
   int f=0;
   window = gtk_builder_get_object (builder, "winaddcontra");
   const char  *numcontra,*dday,*fday,*dmounth,*fmounth,*dyears,*fyears,*coutt,*idvoiture,*idclient;
   numcontra = gtk_entry_get_text (wentrada);

   fcp=fopen("contra.txt","a+");
        {

           co.numContrat= atoi(numcontra);
           while(fscanf(fcp,format_contra,&co.numContrat,&co.idClient,&co.idVoiture,&co.debut.day,&co.debut.mounth,&co.debut.year,&co.fin.day,&co.fin.mounth,&co.fin.year,&co.cout)!=EOF){
            if(atoi(numcontra)==co.numContrat){

               changeLocation(co.idVoiture,"non");
                sup_contra(co.numContrat);
                f=1;
            }
        }}
        if(f==0){
       GObject *win1;
       win1 =  gtk_builder_get_object (builder, "exitspasid");
       gtk_widget_show(win1);
       closeWindow(window);

        }

       fclose(fcp);
}
void Windowlocation (GtkWidget *widget,gpointer   data)
{
 GtkBuilder  *builder;
  builder = gtk_builder_new_from_file("mainUi.glade");
  GObject *window;
  GObject *lvoiture,*rernuvoiture,*btnsup,*btnmod,*btnallcontra;
  window = gtk_builder_get_object (builder, "location");
  lvoiture = gtk_builder_get_object(builder,"lvoiture");
  btnsup =  gtk_builder_get_object(builder,"supcontra");
  rernuvoiture = gtk_builder_get_object(builder,"retvoiture");
  btnmod = gtk_builder_get_object(builder,"mdcontra");
  btnallcontra= gtk_builder_get_object(builder,"vscontra");
  g_signal_connect (lvoiture, "clicked",G_CALLBACK (louerVoiture), NULL);
  g_signal_connect (rernuvoiture, "clicked",G_CALLBACK (returnerVoiture), NULL);
  g_signal_connect (btnsup, "clicked",G_CALLBACK (windowSupContra), NULL);
  g_signal_connect (btnmod, "clicked",G_CALLBACK (windowmoddate), NULL);
  g_signal_connect (btnallcontra, "clicked",G_CALLBACK (windowviewContra), NULL);
 gtk_widget_show_all(window);
}
void windowviewContra (GtkWidget *widget,gpointer   data){
GtkBuilder  *builder;
GtkEntry **tab;
 GObject *window,*btnsearch;
 builder = gtk_builder_new_from_file("mainUi.glade");
 window = gtk_builder_get_object (builder, "viewcontra");
 btnsearch = gtk_builder_get_object(builder,"chercherbtn");
  tab = (GtkEntry*)malloc(10*sizeof(GtkEntry));
 tab[0]=GTK_ENTRY(gtk_builder_get_object(builder, "numc"));
  tab[1] = GTK_ENTRY (gtk_builder_get_object(builder,"idvoitur"));
   tab[2]= GTK_ENTRY (gtk_builder_get_object(builder,"idclie"));
    tab[3] =GTK_ENTRY ( gtk_builder_get_object(builder,"coutid"));
    tab[4] = GTK_ENTRY (gtk_builder_get_object(builder,"fda"));
    tab[5] =GTK_ENTRY ( gtk_builder_get_object(builder,"fmount2"));
    tab[6] =GTK_ENTRY ( gtk_builder_get_object(builder,"fyea"));
    tab[7] = GTK_ENTRY (gtk_builder_get_object(builder,"dday1"));
    tab[8] =GTK_ENTRY (gtk_builder_get_object(builder,"dmount1"));
    tab[9] = GTK_ENTRY (gtk_builder_get_object(builder,"dyears1"));
g_signal_connect (btnsearch, "clicked",G_CALLBACK (info_contra), (GtkEntry*)tab);
 gtk_widget_show_all(window);
}
void info_contra(GtkWidget *widget, GtkEntry **wentrada){
    contrat co;
    GtkBuilder  *builder;
    GtkWindow *window;
    const char *idvoituret,*idclientt,*countt,fdayt[10],ddayt[10],dmountht[10],dyeart[10],fmountht[10],fyeart[5];
     builder = gtk_builder_new_from_file("mainUi.glade");
     window = gtk_builder_get_object (builder, "exitspasid");
    int f =0;
    char num[10],num2[10],num3[10];
    FILE *fcp;
    fcp = fopen("contra.txt","r");
  const char *numcontra = gtk_entry_get_text (*(wentrada+0));
  int numcontraInt = atoi(numcontra);
   while(fscanf(fcp,format_contra,&co.numContrat,&co.idClient,&co.idVoiture,&co.debut.day,&co.debut.mounth,&co.debut.year,&co.fin.day,&co.fin.mounth,&co.fin.year,&co.cout)!=EOF)
     {
            if(co.numContrat==numcontraInt)
            {
                itoa(co.idVoiture,num,10);
                idvoituret=num;
               itoa(co.idClient,num2,10);
               idclientt=num2;
                itoa(co.cout,num3,10);
                countt=num3;
                itoa(co.debut.day,ddayt,10);
                itoa(co.debut.mounth,dmountht,10);
                itoa(co.debut.year,dyeart,10);
                itoa(co.fin.day,fdayt,10);
                itoa(co.fin.year,fyeart,10);
                itoa(co.fin.mounth,fmountht,10);
                gtk_entry_set_text (*(wentrada+1),idvoituret);
                gtk_entry_set_text (*(wentrada+2),idclientt);
                gtk_entry_set_text (*(wentrada+7),ddayt);
                gtk_entry_set_text (*(wentrada+8),dmountht);
                gtk_entry_set_text (*(wentrada+9),dyeart);
                gtk_entry_set_text (*(wentrada+4),fdayt);
                gtk_entry_set_text (*(wentrada+5),fmountht);
                gtk_entry_set_text (*(wentrada+6),fyeart);
                gtk_entry_set_text (*(wentrada+3),countt);
                f =1;
            }

     }
     if(f==0){
       gtk_widget_show_all(window);
     }
    fclose(fcp);
}
void windowSupContra (GtkWidget *widget,gpointer   data){
GtkBuilder  *builder;
GtkEntry *tab;
 GObject *window,*btnsearch;
 builder = gtk_builder_new_from_file("mainUi.glade");
 tab=GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));
 window = gtk_builder_get_object (builder, "supcountra");
 btnsearch = gtk_builder_get_object(builder,"serch1");
 g_signal_connect (btnsearch, "clicked",G_CALLBACK (sup_contra_n), tab);
 gtk_widget_show_all(window);
}
void windowmoddate (GtkWidget *widget,gpointer   data){
    GtkBuilder  *builder;
    GtkEntry **tab;
    GObject *window,*btnsave;
    builder = gtk_builder_new_from_file("mainUi.glade");
    tab = (GtkEntry*)malloc(4*sizeof(GtkEntry));
    tab[0]=GTK_ENTRY(gtk_builder_get_object(builder, "mfday"));
    tab[1]=GTK_ENTRY(gtk_builder_get_object(builder, "mfmounth"));
    tab[2]=GTK_ENTRY(gtk_builder_get_object(builder, "mfyear"));
    tab[3]=GTK_ENTRY(gtk_builder_get_object(builder, "numctr"));
    window = gtk_builder_get_object (builder, "modifdatefin");
    btnsave =gtk_builder_get_object(builder,"btnsavenew");
    g_signal_connect (btnsave, "clicked",G_CALLBACK (save_new_date), tab);
    gtk_widget_show_all(window);
}
void save_new_date (GtkWidget *widget, GtkEntry **wentrada){
   FILE *fcp,*fp1;
   contrat co;
   GtkBuilder  *builder;
   builder = gtk_builder_new_from_file("mainUi.glade");
   GObject *window;
  // window = gtk_builder_get_object (builder, "winaddcontra");
   const char  *numcontra,*nfday,*nfmounth,*nfyears;
   numcontra = gtk_entry_get_text (*(wentrada+3));
   nfday = gtk_entry_get_text (*(wentrada+0));
   nfmounth    = gtk_entry_get_text (*(wentrada+1));
   nfyears = gtk_entry_get_text (*(wentrada+2));
   printf("\n%s\n",nfyears);
   fcp=fopen("contra.txt","r");
   fp1 = fopen("tmp.txt","a");
    int f=0;
    while(fscanf(fcp,format_contra,&co.numContrat,&co.idClient,&co.idVoiture,&co.debut.day,&co.debut.mounth,&co.debut.year,&co.fin.day,&co.fin.mounth,&co.fin.year,&co.cout)!=EOF)
    {
        if(co.numContrat==atoi(numcontra)){
                f=1;
            fprintf(fp1,format_contra,co.numContrat,co.idClient,co.idVoiture,co.debut.day,co.debut.mounth,co.debut.year,atoi(nfday),atoi(nfmounth),atoi(nfyears),co.cout);
        }
        else{
            fprintf(fp1,format_contra,co.numContrat,co.idClient,co.idVoiture,co.debut.day,co.debut.mounth,co.debut.year,co.fin.day,co.fin.mounth,co.fin.year,co.cout);
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
    fcp = fopen("contra.txt","w");
    fclose(fcp);
     fcp = fopen("contra.txt","a");
    fp1 = fopen("tmp.txt","r");
     while(fscanf(fp1,format_contra,&co.numContrat,&co.idClient,&co.idVoiture,&co.debut.day,&co.debut.mounth,&co.debut.year,&co.fin.day,&co.fin.mounth,&co.fin.year,&co.cout)!=EOF)
    {
            fprintf(fcp,format_contra,co.numContrat,co.idClient,co.idVoiture,co.debut.day,co.debut.mounth,co.debut.year,co.fin.day,co.fin.mounth,co.fin.year,co.cout);
    }
    fclose(fcp);
    fclose(fp1);
    fcp = fopen("tmp.txt","w");
    fclose(fcp);
}
void sup_contra_n (GtkWidget *widget, GtkEntry *wentrada){
    GtkBuilder  *builder;
    GObject *window;
  const char *numcontra = gtk_entry_get_text (wentrada);
  builder = gtk_builder_new_from_file("mainUi.glade");
   window = gtk_builder_get_object (builder, "supcountra");
  int numcontraInt = atoi(numcontra);
  sup_contra(numcontraInt);
  gtk_window_close (window);
}
void louerVoiture(GtkWidget *widget,gpointer   data){
GtkBuilder  *builder;
GtkEntry **tab;
 GObject *window,*btnsearch;
 builder = gtk_builder_new_from_file("mainUi.glade");
tab = (GtkEntry*)malloc(6*sizeof(GtkEntry));
tab[0]=GTK_ENTRY(gtk_builder_get_object(builder, "enom"));
tab[1]=GTK_ENTRY(gtk_builder_get_object(builder, "epreno"));
tab[2]=GTK_ENTRY(gtk_builder_get_object(builder, "enomvoiture"));
tab[3]=GTK_ENTRY(gtk_builder_get_object(builder, "emarque"));
tab[4]=GTK_ENTRY(gtk_builder_get_object(builder, "enbplace"));
tab[5]=GTK_ENTRY(gtk_builder_get_object(builder, "ecoulour"));
window = gtk_builder_get_object (builder, "windowlvoiture");
btnsearch = gtk_builder_get_object(builder,"btnchercher");
g_signal_connect (btnsearch, "clicked",G_CALLBACK (cherche), (GtkEntry*)tab);
 gtk_widget_show_all(window);
}
void returnerVoiture(GtkWidget *widget,gpointer   data){
GtkBuilder  *builder;
GtkEntry *tab;
 GObject *window,*btnsearch;
 builder = gtk_builder_new_from_file("mainUi.glade");
 window = gtk_builder_get_object (builder, "routurnevoiture");
 tab=GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
 btnsearch = gtk_builder_get_object(builder,"serch");
 g_signal_connect (btnsearch, "clicked",G_CALLBACK (btn_ret_voiture),tab);
 gtk_widget_show_all(window);
}
void cherche(GtkWidget *widget, GtkEntry **wentrada){
  GtkBuilder  *builder;
  GtkEntry **tab;
  int idvoiture,idclient;
  char snum[5],snum2[5];
  GObject *windowgesclient,*windowaddcountra,*btnsave;
 int findVoitire=0,findclient=0;
 const char *nom,*prenom,*nomvoiture,*marque,*nbplace,*coulour;
  builder = gtk_builder_new_from_file("mainUi.glade");
  windowgesclient = gtk_builder_get_object (builder, "clien1");
  windowaddcountra=  gtk_builder_get_object (builder, "winaddcontra");
  tab = (GtkEntry*)malloc(10*sizeof(GtkEntry));
tab[0]=GTK_ENTRY(gtk_builder_get_object(builder, "numcontra"));
tab[1]=GTK_ENTRY(gtk_builder_get_object(builder, "dday"));
tab[2]=GTK_ENTRY(gtk_builder_get_object(builder, "dmounth"));
tab[3]=GTK_ENTRY(gtk_builder_get_object(builder, "dyear"));
tab[4]=GTK_ENTRY(gtk_builder_get_object(builder, "fday"));
tab[5]=GTK_ENTRY(gtk_builder_get_object(builder, "fmounth"));
tab[6]=GTK_ENTRY(gtk_builder_get_object(builder, "fyear"));
tab[7]=GTK_ENTRY(gtk_builder_get_object(builder, "count"));
tab[8]=GTK_ENTRY(gtk_builder_get_object(builder, "idvoiture"));
tab[9]=GTK_ENTRY(gtk_builder_get_object(builder, "idclien"));
btnsave =gtk_builder_get_object(builder,"save");
 nom = gtk_entry_get_text (*(wentrada+0));
 prenom  = gtk_entry_get_text (*(wentrada+1));
 nomvoiture  =  gtk_entry_get_text (*(wentrada+2));
 marque  = gtk_entry_get_text (*(wentrada+3));
 nbplace  = gtk_entry_get_text (*(wentrada+4));
 coulour = gtk_entry_get_text (*(wentrada+5));

 fvp = fopen("voiture.txt","r");
 fcp = fopen("client.txt","r");
      if(fcp == NULL  )
    {printf("file does not found !");
            exit(1);}
     else{
     fcp = fopen("client.txt","r");
     while(fscanf(fcp,format_client,&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone)!=EOF)
     {
            if(strcmp(nom,c.nom)==0 && strcmp(prenom,c.prenom)==0 )
            {
                 findclient =1;
                 idclient =c.idClient;
            }
            }
            /******/
if(findclient==1){
        if(fvp==NULL){
        printf("is error");
        exit(0);
     }else{
     while(fscanf(fvp,format_voiture,&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
     {
            if(v.nbplaces==atoi(nbplace) && strcmp(coulour,v.couleur)==0  && strcmp(marque,v.marque)==0 && strcmp(nomvoiture,v.nomVoiture)==0 )
            {
                idvoiture=v.idVoiture;
                    findVoitire=1;
                    if(strcmp(enlocationYes,v.EnLocation)==0){
                        findVoitire=2;

                    }
            }


     }
if(findVoitire==2){

          GObject *win2;
win2 =  gtk_builder_get_object (builder, "vld");
gtk_widget_show(win2);
}
else if(findVoitire==0){
    GObject *win1;
win1 =  gtk_builder_get_object (builder, "nexitpasvoitire");
gtk_widget_show(win1);
}
 else{//go to to window contra
        gtk_widget_show_all(windowaddcountra);
        itoa(idvoiture, snum, 10);
        itoa(idclient, snum2, 10);
        gtk_entry_set_text (*(tab+8),snum);
        gtk_entry_set_text (*(tab+9),snum2);
         g_signal_connect (btnsave, "clicked",G_CALLBACK (savecountra), (GtkEntry*)tab);

    }

}
}else{
//show window a window ajout client
 gtk_widget_show_all(windowgesclient);
}


}}
void savecountra(GtkWidget *widget, GtkEntry **wentrada){
   FILE *fcp;
   contrat co;
   GtkBuilder  *builder;
   builder = gtk_builder_new_from_file("mainUi.glade");
   GObject *window;
   window = gtk_builder_get_object (builder, "winaddcontra");
   const char  *numcontra,*dday,*fday,*dmounth,*fmounth,*dyears,*fyears,*coutt,*idvoiture,*idclient;
   numcontra = gtk_entry_get_text (*(wentrada+0));
   dday = gtk_entry_get_text (*(wentrada+1));
   dmounth =  gtk_entry_get_text (*(wentrada+2));
   dyears = gtk_entry_get_text (*(wentrada+3));
   fday = gtk_entry_get_text (*(wentrada+4));
   fmounth    = gtk_entry_get_text (*(wentrada+5));
   fyears = gtk_entry_get_text (*(wentrada+6));
   coutt = gtk_entry_get_text (*(wentrada+7));
   idvoiture  = gtk_entry_get_text (*(wentrada+8));
   idclient  = gtk_entry_get_text (*(wentrada+9));
      fcp = fopen("contra.txt","r");
     int f=0;
     while(fscanf(fcp,format_contra,&co.numContrat,&co.idClient,&co.idVoiture,&co.debut.day,&co.debut.mounth,&co.debut.year,&co.fin.day,&co.fin.mounth,&co.fin.year,&co.cout)!=EOF)
     {
            if(co.numContrat==numcontra)
            {
                    f =1;
            }
     }
     if(f==1){
       GObject *win1;
       win1 =  gtk_builder_get_object (builder, "existid");
       gtk_widget_show(win1);
     }else{
     fclose(fcp);
   fcp=fopen("contra.txt","a+");
        {
           co.debut.day =atoi(dday);
           co.debut.mounth = atoi(dmounth);
           co.debut.year = atoi(dyears);
           co.fin.day=atoi(fday);
           co.fin.mounth=atoi(fmounth);
           co.fin.year=atoi(fyears);
           co.numContrat= atoi(numcontra);
           co.cout= atoi(coutt);
           co.idVoiture= atoi(idvoiture);
           co.idClient= atoi(idclient);
           fprintf(fcp,format_contra,co.numContrat,co.idClient,co.idVoiture,co.debut.day,co.debut.mounth,co.debut.year,co.fin.day,co.fin.mounth,co.fin.year,co.cout);
           changeLocation(co.idVoiture,"oui");
        }
       fclose(fcp);
       }
}
void changeLocation(int i,char *y){
    FILE *fp,*fp1;
     fp = fopen("voiture.txt","r");
     fp1 = fopen("tmp.txt","a");
     int f=0;
     if(fp==NULL){

        printf("is error");
        exit(0);
     }else{
     while(fscanf(fp,"%d %s %s %d %s %d %s \n",&v.idVoiture,v.nomVoiture,v.marque,&v.nbplaces,v.couleur,&v.prixJour,v.EnLocation)!=EOF)
     {
            if(v.idVoiture==i)
            {
                    f =1;
                fprintf(fp1,"%d %s %s %d %s %d %s \n",v.idVoiture,v.nomVoiture,v.marque,v.nbplaces,v.couleur,v.prixJour,y);
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
void sup_contra(int numcntra){
    FILE *fcp,*fp1;
    contrat co;
   char num[15];
      fcp = fopen("contra.txt","r");
     fp1 = fopen("tmp.txt","a");
     char number[100];
     char date[20];
     int f=0;
     while(fscanf(fcp,format_contra,&co.numContrat,&co.idClient,&co.idVoiture,&co.debut.day,&co.debut.mounth,&co.debut.year,&co.fin.day,&co.fin.mounth,&co.fin.year,&co.cout)!=EOF)
     {
            if(co.numContrat==numcntra)
            {
                    f =1;
                    printf("\n\n\n\t\t\t\tDelete successfull\n\n");
            }
            else
            {
                           fprintf(fp1,format_contra,co.numContrat,co.idClient,co.idVoiture,co.debut.day,co.debut.mounth,co.debut.year,co.fin.day,co.fin.mounth,co.fin.year,co.cout);

            }

     }
     if(f==0)
     {
          GtkBuilder  *builder;
           builder = gtk_builder_new_from_file("mainUi.glade");
           GObject *win1;
           win1 =  gtk_builder_get_object (builder, "exitspasid");
           gtk_widget_show(win1);
     }
     fclose(fcp);
     fclose(fp1);
    fcp = fopen("contra.txt","w");
    fclose(fcp);
     fcp = fopen("contra.txt","a");
    fp1 = fopen("tmp.txt","r");
    while(fscanf(fp1,format_contra,&co.numContrat,&co.idClient,&co.idVoiture,&co.debut.day,&co.debut.mounth,&co.debut.year,&co.fin.day,&co.fin.mounth,&co.fin.year,&co.cout)!=EOF)
    {
                           fprintf(fcp,format_contra,co.numContrat,co.idClient,co.idVoiture,co.debut.day,co.debut.mounth,co.debut.year,co.fin.day,co.fin.mounth,co.fin.year,co.cout);
    }
    fclose(fcp);
    fclose(fp1);
    fcp = fopen("tmp.txt","w");
    fclose(fcp);
}
void closeWindow(GtkWindow *window){
 gtk_window_close (window);
}
