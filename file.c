//---------------------------------------------------------------------
    void animation(char *mess)
{
	int i;
	for(i = 0; i < strlen(mess); i++)
	{
		printf("%c",mess[i]);
		fflush(stdout);
		usleep(50000);                             // Pause de 50 millisecondes entre chaque caractère
	}
}
//----------------------------------------------------------------
char *string(int nbr)
{
	char *tab=NULL;
	tab=(char*)malloc(nbr*sizeof(char));
	if(tab == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return (tab);
}
//----------------------------------------------------------------
void helpMe()
{
    printf("Your choice should be in 1 or 2 or 3 or 4  or 5\n");
    printf("You can't combine these options\n into different state like \n");
    printf("like 12 (or 21) for 1 and 2... ");
    printf("Please enter the number in menu \n");

}
//----------------------------------------------------------------
int  quit()
{
        
    printf("Thank you!!!\n");
    printf("See you soon ...\n");
    system("sleep 2");
    system("clear");
    

    return 0;
}
//----------------------------------------------------------------
    int getnb()
    {
        int n;
        int lim=0;
        char* input;
        input=string(50);
        while( lim<3)
        {
            printf("Your choice :\n");
            printf("=>");
            fgets(input,sizeof(input),stdin);
            char *endptr;
            n=strtol(input,&endptr,10);  
            if (endptr != input && *endptr =='\n' && n>0 && n<=6)
            {
                lim=2;
                return n;
            }
            else
            {
                helpMe();
                lim++;
            }
        } 
        free(input);
    }
//----------------------------------------------------------------
void creatFile()
{
    system("cut -d' ' -f2,3,4,5,6 listeL1.csv >ficfname ");
    system("cut -d' ' -f1 listeL1.csv >ficname ");
}
//----------------------------------------------------------------

void fstarthtml(FILE *file_liste,char *str)
{
    fprintf(file_liste,"<HTML>\n\
    <HEAD>\n\
        <title>Fichier Presence</title>\n\
    </HEAD>\n\
    <BODY>\n\
        <CENTER><h1><FONT color='blue'>%s</FONT> </h1></CENTER>\n\
        <h2>%s %s </h2>\n\
        <TABLE  border=3 > \
<TR> \n\
<TD><B><FONT color='blue'>N°]</FONT></B> </TD>\n\
<TD> <B><FONT color='blue'>Nom</FONT></B> </TD>\n\
 <TD><B><FONT color='blue'> Prenom</FONT></B></TD>\n\
</TR>\n\
   ",str,__DATE__,__TIME__);
    
}
//----------------------------------------------------------------
void fendhtml(FILE *file_liste)
{
    fprintf(file_liste,"</TABLE>\n\
    </BODY>\n\
    </HTML>");
}

//----------------------------------------------------------------
void fprintff(FILE *file, int number,char *name ,char *fname)
{
	fprintf(file,"<TR>\n\
	<TD>%d]</TD>\n\
	<TD>%s</TD>\n\
	<TD>%s</TD>\n\
	</TR>\n",number,name,fname);
}

//-------------------------------------------------------------------
void ff(FILE *file_liste,int number,char *name,char *fname,char *strOK,char *color,char *time)
{
	fprintf(file_liste,"<TR>\n\
	<TD>%d]</TD>\n\
	<TD>%s</TD>\n\
	<TD>%s</TD>\n\
	<TD><FONT COLOR=\"%s\">%s</FONT></TD>\n\
	<TD>[%s]</TD>\n\
	</TR>\n",number,name,fname,color,strOK,time);
}
//-------------------------------------------------------------------
void filename(char *output_filename)
{
        printf("please entry the file name: ");
        fgets(output_filename,sizeof(output_filename),stdin);
        output_filename[strcspn(output_filename ,"\n")]='\0';
        strcat(output_filename,".html");
}
//---------------------------------------------------------------
void getname(Student *std)
{
    int i=1;
    FILE *fnom;
    fnom=openr("ficname");
    char *ligne;
    ligne=(char*)malloc(256*sizeof(char));
    while(fgets(ligne,255,fnom)!=NULL)
    {
       ligne[strcspn(ligne, " \n")] = '\0';
       strcpy(std[i].name,ligne);
       i++;
    }
    fclose(fnom);
    remove ("ficname");

}

//----------------------------------------------------------------
void getfname(Student *std)
{
    int i=1;
    FILE *fnom;
    fnom=openr("ficfname");
    char *ligne;
    ligne=(char*)malloc(256*sizeof(char));
    while(fgets(ligne,256,fnom)!=NULL)
    {
       ligne[strcspn(ligne, "\n")] = '\0';
       strcpy(std[i].fname,ligne);
       std[i].number=i;
       std[i].OK=ABSENT;
       std[i].check=NO;
       i++;
    }
    fclose(fnom);
    remove ("ficfname");

}

//----------------------------------------------------------------
    int getNumero()
    {
        int n;
        int lim=0;
        char *input;
        input=string(50);
        while( lim<3)
        {
            printf("Your Number :\n");
            printf("=>");
            fgets(input,sizeof(input),stdin);
            char *endptr;
            n=strtol(input,&endptr,10);
            if(n<=0)  
            printf("Please enter a Positif number\n");
            if (endptr != input && *endptr =='\n' && n>0 && n<NB_MAX)
            {
                lim=2;
                return n;
            }
            else
            {
                
                lim++;
                if (lim==2)
                    printf("to much error \n The application quit with ERROR!!!!\n");

            }
        }  
        free(input); 
    }
 
//----------------------------------------------------------------
void stdOK(int std,char *str )
{
        if(std==YES)
            strcpy(str,"YES");
        else if(std==NO)
            strcpy(str,"NO");
        else if(std==PERSO)
            strcpy(str,"PERSO");
        else if(std==ABSENT)
            strcpy(str,"ABSENT");
        
}

//----------------------------------------------------------------
void fchoix()
{
    printf("If you want to use a panasonic machine enter %d\n",YES);
    printf("If you won't use  machine enter %d\n",NO);
    printf("If you want to use your personal machine enter %d\n",PERSO);
    printf("to cancel %d\n",ABSENT );
   animation("    ******************   \n\n");

}
//----------------------------------------------------------------
void fchoix1()
{
    printf("Use panasonic machine  : %d \nDont use machine:%d  \nUse personal machine  :%d \n",YES,NO,PERSO);
    printf("to cancel %d\n",ABSENT );
    animation("  ++++++++++++++++++++++++++++++  \n\n");
}

//----------------------------------------------------------------
 int  ByNumero(Student *std)
{  
   
    FILE *file_liste;
    file_liste=openw("presence.html");
    int n=getNumero();
    fprintf(file_liste,"<HTML>\n<HEAD>\n<title>Fichier Presence</title>\n<HEAD/>\n<BODY>\n<TABLE  border=3 >");
    char str[50];
    if(std[n].check==0)
    {
        stdOK(std[n].OK,str);
		printf("Sorry,It's Already Checked [%s] !!\n",str);
        interface(std);
    }
    else
    {
		printf("%d] %s %s",std[n].number,std[n].name,std[n].fname);
		std[n].OK=getnbOK();
					char str[50],str1[50];
					std[n].check=0;
					stdOK(std[n].OK,str);
					color(str,str1);
					ff(file_liste,std[n].number,std[n].name,std[n].fname,str,str1,__TIME__);
	}
    fprintf(file_liste,"</TABLE></BODY>\n</HTML>");
	fclose(file_liste);
    interface(std);
}
//----------------------------------------------------

void same_choice_different_number(Student *std)
{
	FILE *file_liste;
    file_liste=openw("presence.html");
	int i;
	int nbr;
	int *tab;
	int choice;
	char str[50];
	printf(" Your Total Student Number : ");
	scanf("%d",&nbr);
	tab=(int *)malloc(nbr*sizeof(int));
	while(getchar() != '\n');
	
    fprintf(file_liste,"<HTML>\n<HEAD>\n<title>CHECK PC</title>\n<HEAD/>\n<BODY>\n<TABLE border=3 >");
    for(int j=1 ;j<=nbr ;j++)
    {
		printf("your number: ");
		scanf("%d",&tab[j]);
    }
    choice=getnbOK();
    char strOK[50],color1[50];
            stdOK(choice,strOK);
            color(strOK,color1);
	for(i=1 ; i<=nbr ; i++)
	{
		if(std[tab[i]].check==YES)
		{
			printf("Sorry,It's Already Checked !!\n");
			i++;
		}
		else
		{
			std[tab[i]].OK=choice;
			std[tab[i]].check=YES;
		    ff(file_liste,std[tab[i]].number,std[tab[i]].name,std[tab[i]].fname,strOK,color1,__TIME__);
		 }		  
	  }
	 fprintf(file_liste,"</TABLE>\n</BODY>\n</HTML>");
	 fclose(file_liste);
	 interface(std);
}
	
//--------------------------------------------------------
void different_choice(Student *std)
{
	int i;
	int nbr;
	printf(" Your Total Student Number : ");
	scanf("%d",&nbr);
	while(getchar() != '\n');
	FILE *file_liste;
    file_liste=openw("presence.html");
    fprintf(file_liste,"<HTML>\n<HEAD>\n<title>CHECK PC</title>\n<HEAD/>\n<BODY>\n<TABLE border=3 >");

	for(i=1 ; i<=nbr ; i++)
	{
		int n=getNumero();

		if(std[n].check==YES)
		{
			printf("Sorry,It's Already Checked !!\n");
			i++;
		}
		else
		{
			printf("%d] %s %s",std[n].number,std[n].name,std[n].fname);
			std[n].OK=getnbOK();
			std[n].check=YES;
			char strOK[50],color1[50];
			stdOK(std[n].OK,strOK);
            color(strOK,color1);
            ff(file_liste,std[i].number,std[i].name,std[i].fname,strOK,color1,__TIME__);
		 }
		  
	  }
	 fprintf(file_liste,"</TABLE>\n</BODY>\n</HTML>");
     fclose(file_liste);
	 interface(std);
	  
	}
	
//-----------------------------------------------------------
void ByName(Student *std)
{
        
        FILE *file_liste;
		file_liste=openw("presence.html");
        char *ligne;
        int i;
        int ok=0;
        ligne=(char*)malloc(256*sizeof(char));

        printf("name (or firstname):");
        fgets(ligne,256,stdin);
        
       ligne[strcspn(ligne, "\n")] = '\0';
		for (int i=0;i<strlen(ligne);i++)
		{
			ligne[i]=toupper(ligne[i]);                  //on change sname en majuscule pour etre comparable
		}

        for(i=1;i<NB_MAX;i++)
        {
         
          for (int j=0;j<strlen(std[i].fname);j++)
			{
				std[i].fname[j]=toupper(std[i].fname[j]); //on change  en majuscule le prenom pour etre comparable
			}
          

            if( strcmp(ligne,std[i].name)==0 || 
                strcmp(ligne,std[i].fname)==0||
                strcasecmp(ligne,std[i].name)==0||
                strcasecmp(ligne,std[i].fname)==0||
                strstr(std[i].name,ligne)!=NULL|| 
                strstr(std[i].fname,ligne)!=NULL)  
                {   
                        for (int j=1;j<strlen(std[i].fname);j++)
                            std[i].fname[j]=tolower(std[i].fname[j]);
                    
                    int m;
                    char mm[10];
                    printf("%d]%s %s\n",std[i].number,std[i].name,std[i].fname);
                    printf(" Is that person that you need?(yes=0,no=1)");
                    char *input;
                    input=(char*)malloc(50*sizeof(char));
                    fgets(input,sizeof(input),stdin);
                    char *endptr;
                    m=strtol(input,&endptr,10);
                
                    if (endptr != input && *endptr =='\n' && m==YES)
                    {  
                        ok=1;
                        break;
                    }
                    else if (endptr != input && *endptr =='\n' && m==NO)
                        continue;
                    else
                    {
                        printf("\n------->>>>your choice should 0 or 1 respectively yes or no\n");
                        printf("%d]%s %s\n",std[i].number,std[i].name,std[i].fname);
                        printf("your choice\n");
                        printf("=>");
                        fgets(input,sizeof(input),stdin);
                        m=strtol(input,&endptr,10);
                        if (endptr != input && *endptr =='\n' && m==YES)
                    {  
                        ok=1;
                        break;
                    }
                    } 
                }

        }
    free(ligne);
    if (ok==1)
     {  
		 
    char strOK[50],color1[50];
		 fprintf(file_liste,"<HTML>\n<HEAD>\n<title>Fichier Presence</title>\n<HEAD/>\n<BODY>\n<TABLE  border=3 >");
		 if(std[i].check != 0)
		  {  
		
				fchoix1();
                printf("%d]%s %s\n",std[i].number,std[i].name,std[i].fname);
                std[i].OK=getnbOK();
                std[i].check=0;
                stdOK(std[i].OK,strOK);
                color(strOK,color1);
                ff(file_liste,std[i].number,std[i].name,std[i].fname,strOK,color1,__TIME__);

          } 
           else
           {  
			    char str[50];
                stdOK(std[i].OK,str);
			    printf("Sorry,It's Already Checked [%s] §§\n",str);
			    interface(std);
            }
            fprintf(file_liste,"</TABLE></BODY>\n</HTML>");

       } 
    else
    {
        printf("%s is not found\n",ligne);
	}
    fclose(file_liste);
    interface(std);
} 
//*-----------------------------------------------------***
void allnormal(Student *std)
{
    int i;
    int begin=1;
    int end=NB_MAX;
    FILE *file_liste;
    file_liste=openw("presence.html");
    printf("Start by the number :\n");
    begin=getNumero();
    printf("and End with the number :\n");
    end=getNumero(); 
    char *str;
    str=string(50);
    fprintf(file_liste,"%s\n",__DATE__);
    fprintf(file_liste, "<HTML>\n  <TITLE>\n </TITLE>\n <BODY>\n <TABLE border = 4>\n ");
    for (i=begin;i<=end;i++)
    {
    
        if(std[i].check==YES)
        {
            printf("%d] %s %s \n",std[i].number,std[i].name,std[i].fname);
            stdOK(std[i].OK,str);
			printf("Sorry,It's Already Checked [%s] §§\n",str);
            continue;
            if(std[end].check==YES)
            {
                interface(std);
			}
        }
		else
		{
            printf("%d] %s %s \n",std[i].number,std[i].name,std[i].fname);
		}
	}
	int n  = 0;
	fchoix();
	std -> OK = getnbOK();
	char strOK[50],color1[50];
	for (i=begin;i<=end;i++)
	{
	switch (std ->OK)
	{
		case PERSO: 
            std[i].OK=PERSO;
            stdOK(std[i].OK,strOK);
            color(strOK,color1);
            ff(file_liste,std[i].number,std[i].name,std[i].fname,strOK,color1,__TIME__);
			break;
		
		case YES:
            std[i].OK=YES;
            stdOK(std[i].OK,strOK);
            color(strOK,color1);
            ff(file_liste,std[i].number,std[i].name,std[i].fname,strOK,color1,__TIME__);
			break;
            
		 case NO:
			std[i].OK=NO;
            stdOK(std[i].OK,strOK);
            color(strOK,color1);
            ff(file_liste,std[i].number,std[i].name,std[i].fname,strOK,color1,__TIME__);
				break;
	}
		
		std[i].check=YES;
	
	}
	printf("done!!\n");
    fprintf(file_liste, "</TABLE></BODY>\n </HTML>\n");
    fclose(file_liste);
    free(str);
    interface(std);
}
//----------------------------------------------------------
void normal(Student *std)
{
    int i;
    int begin=1;
    int end=NB_MAX;
    FILE *file_liste;
    
    file_liste=openw("presence.html");
    printf("Start by the number :\n");
    begin=getNumero();
    printf("and End with the number :\n");
    end=getNumero(); 
    char *str;
    str=string(50);
    fprintf(file_liste,"<HTML>\n<HEAD>\n<title>Fichier Presence</title>\n<HEAD/>\n<BODY>\n<TABLE  border=3 >");

    fprintf(file_liste,"%s\n",__DATE__);

    for (i=begin;i<=end;i++)
    {
        if(std[i].check==YES)
        {
            printf("%d] %s %s \n",std[i].number,std[i].name,std[i].fname);
            stdOK(std[i].OK,str);
			printf("Sorry,It's Already Checked [%s] §§\n",str);
            continue;
            if(std[end].check==YES)
            {
                interface(std);
			}
		}
		else
		{
			char color1[20];
			printf("%d] %s %s \n",std[i].number,std[i].name,std[i].fname);
			std[i].OK=getnbOK();
			std[i].check=0;
			stdOK(std[i].OK,str);
			color(str,color1);
			ff(file_liste,std[i].number,std[i].name,std[i].fname,str,color1,__TIME__);
		}   
    
    }
    fprintf(file_liste,"</TABLE></BODY>\n</HTML>");
    fclose(file_liste);
    free(str);
    interface(std);
}

//----------------------------------------------------------------
void menu()
{
        
    printf("______________________________________\n");
    animation("    *** WELCOME TO THIS APP ***       \n");
    system("sleep 1");
    printf("______________________________________\n") ;
    animation(" +++ DEVELOPED BY Ikann  +++     \n");
    printf("______________________________________\n");
    system("sleep 1");
    system("clear");
}
//----------------------------------------------------------------
void menuUs(Student *std)
{
    printf("    ++++++++++++++++++++++++++++++++++\n");
    printf("|\tCheckPC v1.1                    \t|\n");
    printf("|\tBy Ikann            \t|\n");
    printf("|\tOur team members:               \t|\n");
    printf("|\t=>Nancia ,Karen,Mario,Nax,Isaia \t|\n");
    animation("|\temail us in:DieTechPro@gmail.com\t|\n");
    printf("|\t[4]:quit                         \t|\n");
    printf("|\t[5]:cancel                      \t|\n");
    printf("    ++++++++++++++++++++++++++++++++++\n");
    int n=getnb();
    int i=0;
    if(n==5)
    {
        interface(std);
	}
    else if(n==4)
    {
     
        quit();
	}
    else
    {
        animation("enter 4 (to Quit) or 5 (to cancel)\n");
        menuUs(std);
        i++;
        if (i==2)
        {
            quit();
		}
    }
    
}

//----------------------------------------------------------------
void allAbsent(Student *std)              
{
    animation("all ABSENT are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==ABSENT)
        printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
    } 
    interface(std);
}   

//----------------------------------------------------------------    
 void allPerso(Student *std)              
{
    animation("all PERSO are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==PERSO)
        {
           printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
	   }
    }
    interface(std);

}   

 //----------------------------------------------------------------  
void allYes(Student *std)
{
    animation("all YES are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==YES)
        {
           printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
	   }
    }
    interface(std);
}  

//----------------------------------------------------------------
void allNo(Student *std)
{
    animation("all NO are:\n");
    printf("N°]  Nom            Prenom\n\n");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==NO)
        {
          printf("%d] %s %s\n",std[i].number,std[i].name,std[i].fname);
		}
    }   
    interface(std);
}

//----------------------------------------------------------------

void menuEvaluation(Student *std)
{
    printf("    -------------------------\n");
animation("To display :\n");
    printf("|\t[1]:All Absent    \t|\n"); 
    printf("|\t[2]:All Perso     \t|\n");
    printf("|\t[3]:All Yes       \t|\n");
    printf("|\t[4]:All No        \t|\n");
    printf("|\t[5]:cancel        \t|\n");
animation( "|\t[6]:On a file:    \t|\n");
    printf("    -------------------------\n");
    int n=getnb();
        switch(n)
        {
            case ABSENT1:
                allAbsent(std);
                break;

            case PERSO1:   
                allPerso(std);
                break;

            case YES1:
                allYes(std);
                break;

             case NO1:
                allNo(std);
                break;

             case FIC:

                    printf("    -------------------------\n");
                    animation("To write :\n");
                        printf("|\t[1]:All Absent    \t|\n"); 
                        printf("|\t[2]:All Perso     \t|\n");
                        printf("|\t[3]:All Yes       \t|\n");
                        printf("|\t[4]:All No        \t|\n");
                        printf("|\t[5]:cancel        \t|\n");
                        printf("    -------------------------\n");
                        int m=getnb();
                            switch(m)
                            {
                                case ABSENT1:
                                    fallAbsent(std);
                                    break;

                                case PERSO1:
                                    fallPerso(std);
                                    break;

                                case YES1:
                                    fallYes(std);
                                    break;

                                case NO1:
                                    fallNo(std);
                                    break;
                                case CANCEL1: 
                                    menuEvaluation(std);
                                    break;  
                            }


            case CANCEL1: 
				interface(std);
				break;        
        } 
}

//----------------------------------------------------------------
void interface(Student *std)
{
       
    printf("    -------------------------\n");
    printf("|\t[1]: Normal Mode \t|\n"); 
    printf("|\t[2]: Searching   \t|\n");
    printf("|\t[3]: Evaluation  \t|\n");
    printf("|\t[4]: Quit        \t|\n");
    printf("|\t[5]: About Us..  \t|\n");
    printf("    -------------------------\n");
    int n=getnb();
        switch(n)
        {
            case NORMAL_MODE:
                fchoix();
                printf("    -------------------------\n");
                printf("|\t[1]: Normal Mode     \t|\n"); 
                printf("|\t[2]: All Normal Mode \t|\n");
                printf("    -------------------------\n");
                int m=getnb();
                switch(m)
                {
                    case NORMAL_MODE1:
                        normal(std);
                        break;
                    case NORMAL_MODE2:
                        allnormal(std);
                        break;
                    
                }
            case SEARCHING:
                menuSearching(std);
                break;

            case EVALUATION:
                menuEvaluation(std);
                break;
            case QUIT:
                quit();
                break;
            case ABOUT_US: 
                menuUs(std);
                break;
            
        }
        
}

//----------------------------------------------------------------
void fallAbsent(Student *std)              
{
    char *output_filename;
    output_filename=string(256);
    filename(output_filename);
    FILE *file = openw(output_filename);
    fstarthtml(file,"ALL ABSENT ARE :\n<BR>");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==ABSENT)
        {
           fprintff(file, std[i].number,std[i].name ,std[i].fname);
        }
    }  
    fendhtml(file);
    printf("A new evaluation file ALL ABSENT created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);
    
}   

//----------------------------------------------------------------    
 void fallPerso(Student *std)              
{
    char *output_filename;
    int i;
    output_filename=string(256);
    filename(output_filename);
    FILE *file = openw(output_filename);
    fstarthtml(file,"ALL PERSO ARE :\n<BR>");
    
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==PERSO)
        {
           fprintff(file, std[i].number,std[i].name ,std[i].fname);     
        }   
 }
    fendhtml(file);
    printf("A new evaluation file ALL PERSO created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);  
} 

//----------------------------------------------------------------     
void fallYes(Student *std)
{
    char *output_filename;
        output_filename=string(256);
    filename(output_filename);
    FILE *file = openw(output_filename);
    fstarthtml(file,"ALL YES ARE :\n<BR>");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==YES)
        {
           fprintff(file, std[i].number,std[i].name ,std[i].fname);     
        }    
    }
    fendhtml(file);
    printf("A new evaluation file ALL YES created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);   
} 

//----------------------------------------------------------------    
void fallNo(Student *std)
{ 
        char *output_filename;   
        output_filename=string(256);
       filename(output_filename);
    FILE *file = openw(output_filename);
    fstarthtml(file,"ALL NO ARE :\n<BR>");
    int i;
    for (i=1;i<NB_MAX;i++)
    {
        if (std[i].OK==NO)
        {
           fprintff(file, std[i].number,std[i].name ,std[i].fname);     
        }    
    }   
    fendhtml(file);
    printf("A new evaluation file ALL NO created <<%s>>\n", output_filename);
    free(output_filename);
    fclose(file);    
}
   
//-------------------------------------------------------------------------------------

void menuSearching(Student *std)
{
  
    printf(" \n   ----------------------------------\n");
    
    animation("Searching \n");
    printf("|\t[1]:student by numero          \t|\n"); 
    printf("|\t[2]:diffNum__DiffChoice        \t|\n");
    printf("|\t[3]:diffNum__OneChoice        \t|\n"); 
    printf("|\t[4]:By name  (or firstname)    \t|\n");
    printf("|\t[5]:cancel                     \t|\n");
    printf("|\t[6]:Quit                       \t|\n");
    printf("    ---------------------------------\n");
    int n=getnb();
    system("clear");
        switch(n)
        {
             case ONEBYNUMERO: 
              fchoix();
                ByNumero(std);
                
                break;
			case DIFF_NUM_DIFF_CHOICE:
				fchoix();
				different_choice(std);
				break;

            case DIFF_NUM_ONE_CHOICE:
				fchoix();
				same_choice_different_number(std); 
                  break; 

            case BYNAME:
                fchoix();
                ByName(std);
                break;
 
            case QUIT1:
                quit();
                break;

            case CANCEL: 
               interface(std);
                break;        
        }
        

}
//----------------------------------------------------------------
FILE*  openr(char *str)
{
    FILE *f;
    f=fopen(str,"r");
    if(f==NULL)
    {
        printf("opening file ERROR \n");
        exit(1);
    }
    else
    {
        return f;
	}
}
//---------------------------------------------------------------------------------

FILE*  openw(char *str)
{
    FILE *f;
    f=fopen(str,"a");
    if(f==NULL)
    {
        printf("opening file ERROR \n");
        exit(1);
    }
    else
    {
        return f;
	}
}


//----------------------------------------------------------------
int getnbOK()
{
        int n;
        Student *std;
        int lim=0;
        char *input;
        input=(char*)malloc(50*sizeof(char));
        while( lim<3 )
        {
            printf("Your choice :\n");
            printf("=>");
            fgets(input,sizeof(input),stdin);
           
            char *endptr;
            n=strtol(input,&endptr,10);
           
            if (endptr != input && *endptr =='\n' && n>=0 && n<4)
            {
                lim=2;
                if(n==3)
                    interface(std); 
                else
                    return n;
            }
            else
            {
                fchoix1();
                lim++;
                if(lim==2)
                    interface(std);
            }
        }  
        free(input);
    }

//----------------------------------------------------------------
char color(char *str1,char *str2)
{
	if(strcmp(str1,"YES") == 0)
	{
		strcpy(str2,"green" );
	}
	else if(strcmp(str1,"NO") == 0)
	{
		strcpy(str2,"blue");
	}
	else if(strcmp(str1,"PERSO") == 0)
	{
		strcpy(str2,"purple");
	}
	else if(strcmp(str1,"ABSENT") == 0)
	{
		strcpy(str2,"red");
	}
}
//--------------------------------------------------------------------------
void inserer_imageHTML(char *file_name)
{
	FILE* fichier=NULL;
	fichier=fopen(file_name,"a");
	if(fichier==NULL)
	 {
		printf("ERREUR");
		exit(1);
	 } 
    else
    {
		fprintf(fichier,
		"<HTML>\n"
			"<HEAD>\n"
			"<TITLE>CHECK PC</TITLE>");
		fprintf(fichier,"\n<STYLE>\n#monImage {\n width: 150px;\n margin: 10px;\nposition: relative;\ntop: 5px;\nleft: 1000px;\n}");
		fprintf(fichier, 
		"<STYLE>\n"   
		"    .Y { color: red; }\n"  
		"    .M { color: red; }\n"  
		"	 .I { color: red; }\n"  
		"    .T { color: red; }\n"  
		"</STYLE>\n"
		"</HEAD>\n"
		"<BODY>\n"
		"    <CENTER><B>\n"
		"        L1 <span class=\"M\">M</span>ention <span class=\"I\">I</span>nformatique et <span class=\"T\">T</span>echnologique\n"
		"    </B></CENTER>\n"
	);
		fprintf(fichier," <img src=\"./imgg.jpg\" id=\"monImage\">");
		fprintf(fichier,"\n</BODY>\n"
						"</HTML>");
	fclose(fichier);
	}
}
