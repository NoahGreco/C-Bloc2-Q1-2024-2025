#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"
#include <unistd.h> //fork & exec
#include <stdlib.h> //exit
#include <sys/types.h> //wait
#include <sys/wait.h> //wait
#include <fcntl.h>
#include  <sys/stat.h>
#include <stdio.h>


MainWindowEx3::MainWindowEx3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx3)
{
    ui->setupUi(this);
}

MainWindowEx3::~MainWindowEx3()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char* MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
  int trace = open("Trace.log", O_CREAT | O_WRONLY | O_APPEND, 0644);

    if (trace == -1)
    {
      perror("Erreur lors de l'ouverture de Trace.log"); //mettre ouverte ligne 14 et fermeture ligne 19
      exit(EXIT_FAILURE);
    }

    // Rediriger stderr vers le fichier log
    if (dup2(trace, STDERR_FILENO) == -1)
    {
      perror("Erreur lors de la redirection de stderr");
      ::close(trace);
      exit(EXIT_FAILURE);
    }
  fprintf(stderr,"Clic sur le bouton Lancer Recherche\n");
  pid_t idFils1,idFils2,idFils3,idPere;
  int status;
  if(recherche1Selectionnee())
  {
      if((idFils1=fork())==-1)
    {
      perror("Erreur de fork1");
      exit(1);
    }
    if(idFils1== 0){
        printf("Processus fils1 avec le pid %d", getpid());
        printf("Execution de Lecture en cours...");

        if(execl("./Lecture","Lecture",getGroupe1(), NULL) == -1){
          perror("Erreur execl");
          exit(1);
        }else {
          printf("Père : Mon PID est %d\n", getpid());
          printf("Père : J'attends la fin du fils...\n");

      }
    }
  }
  /////////////////////////
  if(recherche2Selectionnee()) 
    
  {
    if((idFils2=fork())==-1)
    {
      perror("Erreur de fork2");
      exit(1);
    }
    if(idFils2== 0){
        printf("Processus fils2 avec le pid %d", getpid());
        printf("Execution de Lecture en cours...");

        if(execl("./Lecture","Lecture",getGroupe2(), NULL) == -1){
          perror("Erreur execl");
          exit(1);
        }else {
          printf("Père : Mon PID est %d\n", getpid());
          printf("Père : J'attends la fin du fils...\n");

      }
    }
  }
  
    /////////////////////////
if(recherche3Selectionnee()){
  if((idFils3=fork())==-1)
    {
      perror("Erreur de fork");
      exit(1);
    }
    if(idFils3== 0){
      printf("Processus fils3 avec le pid %d", getpid());
      printf("Execution de Lecture en cours...");

      if(execl("./Lecture","Lecture",getGroupe3(), NULL) == -1){
        perror("Erreur execl");
        exit(1);
      }else {
        printf("Père : Mon PID est %d\n", getpid());
        printf("Père : J'attends la fin du fils...\n");

    }
  }
}
  
  
  // Attente de la fin du fils
       while((idPere = wait(&status))!=-1)
       {
         if (WIFEXITED(status)) // Vérifier si le fils s'est terminé normalement
        {
          fprintf(stderr, "Fils avec PID %d terminé avec le code : %d\n", idPere, WEXITSTATUS(status));

          // Associer le code de sortie au bon groupe
          if (idPere == idFils1)
              setResultat1(WEXITSTATUS(status));
          else if (idPere == idFils2)
              setResultat2(WEXITSTATUS(status));
          else if (idPere == idFils3)
              setResultat3(WEXITSTATUS(status));
        }
        else
        {
          fprintf(stderr, "Fils avec PID %d terminé de manière anormale\n", idPere);
        }
       }

    


}

void MainWindowEx3::on_pushButtonVider_clicked()
{
  
  fprintf(stderr,"Clic sur le bouton Vider\n");

  //Vider les champs de groupe
  ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();
  
  // Vider les champs de résultat
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();

  // Désélectionner les checkboxes
  ui->checkBoxRecherche1->setChecked(false);
  ui->checkBoxRecherche2->setChecked(false);
  ui->checkBoxRecherche3->setChecked(false);
  fprintf(stderr, "Tous les champs ont été vidés.\n");
}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");

  close();
}
